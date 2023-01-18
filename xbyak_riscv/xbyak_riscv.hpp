#pragma once
/*!
	@file xbyak_riscv.hpp
	@brief Xbyak_riscv ; JIT assembler for RISC-V
	@author herumi
	@url https://github.com/herumi/xbyak_riscv
	@note modified new BSD license
	http://opensource.org/licenses/BSD-3-Clause
*/
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <windows.h>
	#include <malloc.h>
#elif defined(__GNUC__)
	#include <unistd.h>
	#include <sys/mman.h>
	#include <stdlib.h>
#endif
#if defined(__APPLE__)
	#define XBYAK_RISCV_USE_MAP_JIT
	#include <sys/sysctl.h>
	#ifndef MAP_JIT
		#define MAP_JIT 0x800
	#endif
#endif

#if defined(__GNUC__) && !defined(__MINGW32__)
	#define XBYAK_RISCV_USE_MMAP_ALLOCATOR
#endif

#ifdef NDEBUG
	#define XBYAK_RISCV_ASSERT(x)
#else
	#define XBYAK_RISCV_ASSERT(x) assert(x)
#endif

// MFD_CLOEXEC defined only linux 3.17 or later.
// Android wraps the memfd_create syscall from API version 30.
#if !defined(MFD_CLOEXEC) || (defined(__ANDROID__) && __ANDROID_API__ < 30)
	#undef XBYAK_RISCV_USE_MEMFD
#endif

#if defined(_WIN64) || defined(__MINGW64__) || (defined(__CYGWIN__) && defined(__x86_64__))
	#define XBYAK_RISCV64_WIN
#elif defined(__x86_64__)
	#define XBYAK_RISCV64_GCC
#endif
#if !defined(XBYAK_RISCV64) && !defined(XBYAK_RISCV32)
	#if defined(XBYAK_RISCV64_GCC) || defined(XBYAK_RISCV64_WIN)
		#define XBYAK_RISCV64
	#else
		#define XBYAK_RISCV32
	#endif
#endif

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4514) /* remove inline function */
	#pragma warning(disable : 4786) /* identifier is too long */
	#pragma warning(disable : 4503) /* name is too long */
	#pragma warning(disable : 4127) /* constant expresison */
#endif

namespace Xbyak_riscv {

enum {
	DEFAULT_MAX_CODE_SIZE = 4096,
	VERSION = 0x0010 /* 0xABCD = A.BC.D */
};

inline uint32_t getVersion() { return VERSION; }

enum {
	ERR_NONE = 0,
	ERR_OFFSET_IS_TOO_BIG,
	ERR_CODE_IS_TOO_BIG,
	ERR_IMM_IS_TOO_BIG,
	ERR_INVALID_IMM_OF_JAL,
	ERR_INVALID_IMM_OF_BTYPE,
	ERR_LABEL_IS_NOT_FOUND,
	ERR_LABEL_IS_REDEFINED,
	ERR_LABEL_IS_TOO_FAR,
	ERR_LABEL_IS_NOT_SET_BY_L,
	ERR_LABEL_IS_ALREADY_SET_BY_L,
	ERR_CANT_PROTECT,
	ERR_CANT_ALLOC,
	ERR_BAD_PARAMETER,
	ERR_MUNMAP,
	ERR_INTERNAL // Put it at last.
};

inline const char *ConvertErrorToString(int err)
{
	static const char *errTbl[] = {
		"none",
		"offset is too big",
		"code is too big",
		"imm is too big",
		"invliad imm of jal",
		"invliad imm of Btye",
		"label is not found",
		"label is redefined",
		"label is too far",
		"label is not set by L",
		"label is already set by L",
		"can't protect",
		"can't alloc",
		"bad parameter",
		"munmap",
	};
	assert(ERR_INTERNAL == sizeof(errTbl) / sizeof(*errTbl));
	return err <= ERR_INTERNAL ? errTbl[err] : "unknown err";
}

#ifdef XBYAK_RISCV_NO_EXCEPTION
namespace local {

inline int& GetErrorRef() {
	static thread_local int err = 0;
	return err;
}

inline void SetError(int err) {
	if (local::GetErrorRef()) return; // keep the first err code
	local::GetErrorRef() = err;
}

} // local

inline void ClearError() {
	local::GetErrorRef() = 0;
}
inline int GetError() { return Xbyak::local::GetErrorRef(); }

#define XBYAK_RISCV_THROW(err) { Xbyak::local::SetError(err); return; }
#define XBYAK_RISCV_THROW_RET(err, r) { Xbyak::local::SetError(err); return r; }

#else
class Error : public std::exception {
	int err_;
public:
	explicit Error(int err) : err_(err)
	{
		if (err_ < 0 || err_ > ERR_INTERNAL) {
			err_ = ERR_INTERNAL;
		}
	}
	operator int() const { return err_; }
	const char *what() const noexcept
	{
		return ConvertErrorToString(err_);
	}
};

// dummy functions
inline void ClearError() { }
inline int GetError() { return 0; }

inline const char *ConvertErrorToString(const Error& err)
{
	return err.what();
}

#define XBYAK_RISCV_THROW(err) { throw Error(err); }
#define XBYAK_RISCV_THROW_RET(err, r) { throw Error(err); }

#endif

inline void *AlignedMalloc(size_t size, size_t alignment)
{
#ifdef __MINGW32__
	return __mingw_aligned_malloc(size, alignment);
#elif defined(_WIN32)
	return _aligned_malloc(size, alignment);
#else
	void *p;
	int ret = posix_memalign(&p, alignment, size);
	return (ret == 0) ? p : 0;
#endif
}

inline void AlignedFree(void *p)
{
#ifdef __MINGW32__
	__mingw_aligned_free(p);
#elif defined(_MSC_VER)
	_aligned_free(p);
#else
	free(p);
#endif
}

namespace local {

static const size_t ALIGN_PAGE_SIZE = 4096;

inline constexpr uint32_t mask(size_t n)
{
	XBYAK_RISCV_ASSERT(n <= 32);
	return n == 32 ? 0xffffffff : (1u << n) - 1;
}
// is x <= mask(n) ?
inline constexpr bool inBit(uint32_t x, size_t n)
{
	return x <= mask(n);
}

// is x is signed n-bit integer?
inline constexpr bool inSBit(int x, int n)
{
	return -(1 << (n-1)) <= x && x < (1 << (n-1));
}

} // local

/*
	custom allocator
*/
struct Allocator {
	explicit Allocator(const std::string& = "") {} // same interface with MmapAllocator
	virtual uint8_t *alloc(size_t size) { return reinterpret_cast<uint8_t*>(AlignedMalloc(size, local::ALIGN_PAGE_SIZE)); }
	virtual void free(uint8_t *p) { AlignedFree(p); }
	virtual ~Allocator() {}
	/* override to return false if you call protect() manually */
	virtual bool useProtect() const { return true; }
};

#ifdef XBYAK_RISCV_USE_MMAP_ALLOCATOR
#ifdef XBYAK_RISCV_USE_MAP_JIT
namespace local {

inline int getMacOsVersionPure()
{
	char buf[64];
	size_t size = sizeof(buf);
	int err = sysctlbyname("kern.osrelease", buf, &size, NULL, 0);
	if (err != 0) return 0;
	char *endp;
	int major = strtol(buf, &endp, 10);
	if (*endp != '.') return 0;
	return major;
}

inline int getMacOsVersion()
{
	static const int version = getMacOsVersionPure();
	return version;
}

} // local
#endif
class MmapAllocator : public Allocator {
	struct Allocation {
		size_t size;
#if defined(XBYAK_RISCV_USE_MEMFD)
		// fd_ is only used with XBYAK_RISCV_USE_MEMFD. We keep the file open
		// during the lifetime of each allocation in order to support
		// checkpoint/restore by unprivileged users.
		int fd;
#endif
	};
	const std::string name_; // only used with XBYAK_RISCV_USE_MEMFD
	typedef std::unordered_map<uintptr_t, Allocation> AllocationList;
	AllocationList allocList_;
public:
	explicit MmapAllocator(const std::string& name = "xbyak") : name_(name) {}
	uint8_t *alloc(size_t size)
	{
		const size_t alignedSizeM1 = local::ALIGN_PAGE_SIZE - 1;
		size = (size + alignedSizeM1) & ~alignedSizeM1;
#if defined(MAP_ANONYMOUS)
		int mode = MAP_PRIVATE | MAP_ANONYMOUS;
#elif defined(MAP_ANON)
		int mode = MAP_PRIVATE | MAP_ANON;
#else
		#error "not supported"
#endif
#if defined(XBYAK_RISCV_USE_MAP_JIT)
		const int mojaveVersion = 18;
		if (local::getMacOsVersion() >= mojaveVersion) mode |= MAP_JIT;
#endif
		int fd = -1;
#if defined(XBYAK_RISCV_USE_MEMFD)
		fd = memfd_create(name_.c_str(), MFD_CLOEXEC);
		if (fd != -1) {
			mode = MAP_SHARED;
			if (ftruncate(fd, size) != 0) {
				close(fd);
				XBYAK_RISCV_THROW_RET(ERR_CANT_ALLOC, 0)
			}
		}
#endif
		void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, mode, fd, 0);
		if (p == MAP_FAILED) {
			if (fd != -1) close(fd);
			XBYAK_RISCV_THROW_RET(ERR_CANT_ALLOC, 0)
		}
		assert(p);
		Allocation &alloc = allocList_[(uintptr_t)p];
		alloc.size = size;
#if defined(XBYAK_RISCV_USE_MEMFD)
		alloc.fd = fd;
#endif
		return (uint8_t*)p;
	}
	void free(uint8_t *p)
	{
		if (p == 0) return;
		AllocationList::iterator i = allocList_.find((uintptr_t)p);
		if (i == allocList_.end()) XBYAK_RISCV_THROW(ERR_BAD_PARAMETER)
		if (munmap((void*)i->first, i->second.size) < 0) XBYAK_RISCV_THROW(ERR_MUNMAP)
#if defined(XBYAK_RISCV_USE_MEMFD)
		if (i->second.fd != -1) close(i->second.fd);
#endif
		allocList_.erase(i);
	}
};
#endif

class Reg {
	uint32_t idx_;
public:
	constexpr Reg(uint32_t idx = 0)
		: idx_(idx)
	{
		XBYAK_RISCV_ASSERT(local::inBit(idx, 5));
	}
	constexpr int getIdx() const { return idx_; }
	const char *toString() const
	{
		static const char tbl[][4] = {
			"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
			"x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15",
			"x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
			"x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31",
		};
		return tbl[idx_];
	}
	bool operator==(const Reg& rhs) const
	{
		return idx_ == rhs.idx_;
	}
	bool operator!=(const Reg& rhs) const { return !operator==(rhs); }
};

static const constexpr Reg x0(0), x1(1), x2(2), x3(3), x4(4), x5(5), x6(6), x7(7);
static const constexpr Reg x8(8), x9(9), x10(10), x11(11), x12(12), x13(13), x14(14), x15(15);
static const constexpr Reg x16(16), x17(17), x18(18), x19(19), x20(20), x21(21), x22(22), x23(23);
static const constexpr Reg x24(24), x25(25), x26(26), x27(27), x28(28), x29(29), x30(30), x31(31);

static const constexpr Reg zero(x0);
static const constexpr Reg ra(x1);
static const constexpr Reg sp(x2);
static const constexpr Reg gp(x3);
static const constexpr Reg tp(x4);
static const constexpr Reg t0(x5);
static const constexpr Reg t1(x6);
static const constexpr Reg t2(x7);
static const constexpr Reg fp(x8);
static const constexpr Reg s0(x8);
static const constexpr Reg s1(x9);
static const constexpr Reg a0(x10), a1(x11), a2(x12), a3(x13), a4(x14), a5(x15), a6(x16), a7(x17);
static const constexpr Reg s2(x18), s3(x19), s4(x20), s5(x21), s6(x22), s7(x23), s8(x24), s9(x25);
static const constexpr Reg s10(x26), s11(x27);
static const constexpr Reg t3(x28), t4(x29), t5(x30), t6(x31);

// 2nd parameter for constructor of CodeArray(maxSize, userPtr, alloc)
void *const DontSetProtectRWE = (void*)2; //-V566

class CodeArray {
	enum Type {
		USER_BUF = 1, // use userPtr(non alignment, non protect)
		ALLOC_BUF // use new(alignment, protect)
	};
	CodeArray(const CodeArray& rhs);
	void operator=(const CodeArray&);
	bool isAllocType() const { return type_ == ALLOC_BUF; }
	const Type type_;
#ifdef XBYAK_RISCV_USE_MMAP_ALLOCATOR
	MmapAllocator defaultAllocator_;
#else
	Allocator defaultAllocator_;
#endif
	Allocator *alloc_;
protected:
	size_t maxSize_;
	uint8_t *top_;
	size_t size_;

	bool useProtect() const { return alloc_->useProtect(); }
public:
	enum ProtectMode {
		PROTECT_RW = 0, // read/write
		PROTECT_RWE = 1, // read/write/exec
		PROTECT_RE = 2 // read/exec
	};
	explicit CodeArray(size_t maxSize, void *userPtr = 0, Allocator *allocator = 0)
		: type_((userPtr == 0 || userPtr == DontSetProtectRWE) ? ALLOC_BUF : USER_BUF)
		, alloc_(allocator ? allocator : (Allocator*)&defaultAllocator_)
		, maxSize_(maxSize)
		, top_(type_ == USER_BUF ? reinterpret_cast<uint8_t*>(userPtr) : alloc_->alloc((std::max<size_t>)(maxSize, 1)))
		, size_(0)
	{
		if (maxSize_ > 0 && top_ == 0) XBYAK_RISCV_THROW(ERR_CANT_ALLOC)
		if ((type_ == ALLOC_BUF && userPtr != DontSetProtectRWE && useProtect()) && !setProtectMode(PROTECT_RWE, false)) {
			alloc_->free(top_);
			XBYAK_RISCV_THROW(ERR_CANT_PROTECT)
		}
	}
	virtual ~CodeArray()
	{
		if (isAllocType()) {
			if (useProtect()) setProtectModeRW(false);
			alloc_->free(top_);
		}
	}
	bool setProtectMode(ProtectMode mode, bool throwException = true)
	{
		bool isOK = protect(top_, maxSize_, mode);
		if (isOK) return true;
		if (throwException) XBYAK_RISCV_THROW_RET(ERR_CANT_PROTECT, false)
		return false;
	}
	bool setProtectModeRE(bool throwException = true) { return setProtectMode(PROTECT_RE, throwException); }
	bool setProtectModeRW(bool throwException = true) { return setProtectMode(PROTECT_RW, throwException); }
	void resetSize()
	{
		size_ = 0;
	}
	void writeBytes(size_t offset, uint64_t v, size_t n)
	{
		if (n > 8) XBYAK_RISCV_THROW(ERR_BAD_PARAMETER)
		if (offset + n > maxSize_) XBYAK_RISCV_THROW(ERR_CODE_IS_TOO_BIG)
		uint8_t *const p = top_ + offset;
		for (size_t i = 0; i < n; i++) {
			p[i] = static_cast<uint8_t>(v >> (i * 8));
		}
	}
	void writeBytes(const uint8_t *addr, uint64_t v, size_t n)
	{
		writeBytes(addr - top_, v, n);
	}
	void appendBytes(uint64_t v, size_t n)
	{
		writeBytes(size_, v, n);
		size_ += n;
	}
	void append4B(uint32_t code) { appendBytes(code, 4); }
	void append2B(uint32_t code) { appendBytes(code, 2); }
	void append1B(uint32_t code) { appendBytes(code, 1); }
	void write4B(size_t offset, uint32_t v) { writeBytes(offset, v, 4); }
	void dump(bool separate = false) const
	{
		const uint8_t *p = getCode();
		const size_t bufSize = getSize();
		if (separate) {
			size_t pos = 0;
			while (pos < bufSize) {
				uint32_t v = p[pos];
				size_t n = (v & 3) == 3 ? 4 : 2;
				if (pos + n <= bufSize) {
					for (size_t i = 0; i < n; i++) {
						printf("%02x", p[pos + n - 1 - i]);
					}
					printf("\n");
					pos += n;
				} else {
					printf("%02x error\n", v);
					return;
				}
			}
			return;
		}
		size_t remain = bufSize;
		for (int i = 0; i < 4; i++) {
			size_t disp = 16;
			if (remain < 16) {
				disp = remain;
			}
			for (size_t j = 0; j < 16; j++) {
				if (j < disp) {
					printf("%02x", p[i * 16 + j]);
				}
			}
			putchar('\n');
			remain -= disp;
			if (remain == 0) {
				break;
			}
		}
	}
	const uint8_t *getCode() const { return top_; }
	template<class F>
	const F getCode() const { return reinterpret_cast<F>(top_); }
	const uint8_t *getCurr() const { return &top_[size_]; }
	template<class F>
	const F getCurr() const { return reinterpret_cast<F>(&top_[size_]); }
	size_t getSize() const { return size_; }
	void setSize(size_t size)
	{
		if (size > maxSize_) XBYAK_RISCV_THROW(ERR_OFFSET_IS_TOO_BIG)
		size_ = size;
	}
	/**
		change exec permission of memory
		@param addr [in] buffer address
		@param size [in] buffer size
		@param protectMode [in] mode(RW/RWE/RE)
		@return true(success), false(failure)
	*/
	static inline bool protect(const void *addr, size_t size, int protectMode)
	{
#if defined(_WIN32)
		const DWORD c_rw = PAGE_READWRITE;
		const DWORD c_rwe = PAGE_EXECUTE_READWRITE;
		const DWORD c_re = PAGE_EXECUTE_READ;
		DWORD mode;
#else
		const int c_rw = PROT_READ | PROT_WRITE;
		const int c_rwe = PROT_READ | PROT_WRITE | PROT_EXEC;
		const int c_re = PROT_READ | PROT_EXEC;
		int mode;
#endif
		switch (protectMode) {
		case PROTECT_RW: mode = c_rw; break;
		case PROTECT_RWE: mode = c_rwe; break;
		case PROTECT_RE: mode = c_re; break;
		default:
			return false;
		}
#if defined(_WIN32)
		DWORD oldProtect;
		return VirtualProtect(const_cast<void*>(addr), size, mode, &oldProtect) != 0;
#elif defined(__GNUC__)
		size_t pageSize = sysconf(_SC_PAGESIZE);
		size_t iaddr = reinterpret_cast<size_t>(addr);
		size_t roundAddr = iaddr & ~(pageSize - static_cast<size_t>(1));
		return mprotect(reinterpret_cast<void*>(roundAddr), size + (iaddr - roundAddr), mode) == 0;
#else
		return true;
#endif
	}
	/**
		get aligned memory pointer
		@param addr [in] address
		@param alignedSize [in] power of two
		@return aligned addr by alingedSize
	*/
	static inline uint8_t *getAlignedAddress(uint8_t *addr, size_t alignedSize = 16)
	{
		return reinterpret_cast<uint8_t*>((reinterpret_cast<size_t>(addr) + alignedSize - 1) & ~(alignedSize - static_cast<size_t>(1)));
	}
};

struct Jmp {
	enum Type {
		tJal,
		tBtype,
		tRawAddress,
	} type;
	const uint8_t* from; /* address of the jmp mnemonic */
	uint32_t encoded;
	size_t encSize() const
	{
		if (type == tRawAddress) return sizeof(size_t);
		return 4;
	}
	// jal
	Jmp(const uint8_t *from, uint32_t opcode, const Reg& rd)
		: type(tJal)
		, from(from)
		, encoded((rd.getIdx() << 7) | opcode)
	{
	}
	// B-type
	Jmp(const uint8_t* from, uint32_t opcode, uint32_t funct3, const Reg& src1, const Reg& src2)
		: type(tBtype)
		, from(from)
		, encoded((src2.getIdx() << 20) | (src1.getIdx() << 15) | (funct3 << 12) | opcode)
	{
	}
	// raw address
	explicit Jmp(const uint8_t* from)
		: type(tRawAddress)
		, from(from)
		, encoded(0)
	{
	}
	static inline bool isValidImm(size_t imm, size_t maskBit)
	{
		const size_t M = local::mask(maskBit);
		return (imm < M || ~M <= imm) && (imm & 1) == 0;
	}
	static inline uint32_t encodeImmJal(uint32_t imm)
	{
		//      1   10  1     8
		// imm[20|10:1|11|19:12]
		return ((imm >> 20) << 31) | (((imm >> 1) & local::mask(10)) << 21) | (((imm >> 11) & 1) << 20) | (imm & (local::mask(8) << 12));
	}
	static inline uint32_t encodeImmBtype(uint32_t imm)
	{
		//          25            7
		// imm[12|10:5]  imm[4:1|11]
		return ((imm >> 12) << 31) | (((imm >> 5) & local::mask(6)) << 25) | (((imm >> 1) & local::mask(4)) << 8) | (((imm >> 11) & 1) << 7);
	}
	size_t encode(const uint8_t* addr) const
	{
		if (type == tRawAddress) return size_t(addr);
		const size_t imm = addr - from;
		if (type == tJal) {
			if (!isValidImm(imm, 20)) XBYAK_RISCV_THROW(ERR_INVALID_IMM_OF_JAL)
			return encodeImmJal(imm) | encoded;
		} else {
			if (!isValidImm(imm, 12)) XBYAK_RISCV_THROW(ERR_INVALID_IMM_OF_JAL)
			return encodeImmBtype(imm) | encoded;
		}
	}
};

class LabelManager;

class Label {
	mutable LabelManager *mgr;
	mutable int id;
	friend class LabelManager;
public:
	Label() : mgr(0), id(0) {}
	Label(const Label& rhs);
	Label& operator=(const Label& rhs);
	~Label();
	void clear() { mgr = 0; id = 0; }
	int getId() const { return id; }
	const uint8_t *getAddress() const;
};

class LabelManager {
	// for Label class
	struct ClabelVal {
		ClabelVal(const uint8_t* addr = 0) : addr(addr), refCount(1) {}
		const uint8_t* addr;
		int refCount;
	};
	typedef std::unordered_map<int, ClabelVal> ClabelDefList;
	typedef std::unordered_multimap<int, Jmp> ClabelUndefList;
	typedef std::unordered_set<Label*> LabelPtrList;

	CodeArray *base_;
	mutable int labelId_;
	ClabelDefList clabelDefList_;
	ClabelUndefList clabelUndefList_;
	LabelPtrList labelPtrList_;

	int getId(const Label& label) const
	{
		if (label.id == 0) label.id = labelId_++;
		return label.id;
	}
	template<class DefList, class UndefList, class T>
	void define_inner(DefList& defList, UndefList& undefList, const T& labelId, const uint8_t* addr)
	{
		// add label
		typename DefList::value_type item(labelId, addr);
		std::pair<typename DefList::iterator, bool> ret = defList.insert(item);
		if (!ret.second) XBYAK_RISCV_THROW(ERR_LABEL_IS_REDEFINED)
		// search undefined label
		for (;;) {
			typename UndefList::iterator itr = undefList.find(labelId);
			if (itr == undefList.end()) break;
			const Jmp *jmp = &itr->second;
			if (jmp->type == Jmp::tRawAddress) {
				base_->writeBytes(jmp->from, jmp->encode(base_->getCurr()), jmp->encSize());
			} else {
				base_->writeBytes(jmp->from, jmp->encode(base_->getCurr()), jmp->encSize());
			}
			undefList.erase(itr);
		}
	}
	friend class Label;
	void incRefCount(int id, Label *label)
	{
		clabelDefList_[id].refCount++;
		labelPtrList_.insert(label);
	}
	void decRefCount(int id, Label *label)
	{
		labelPtrList_.erase(label);
		ClabelDefList::iterator i = clabelDefList_.find(id);
		if (i == clabelDefList_.end()) return;
		if (i->second.refCount == 1) {
			clabelDefList_.erase(id);
		} else {
			--i->second.refCount;
		}
	}
	template<class T>
	bool hasUndefinedLabel_inner(const T& list) const
	{
		return !list.empty();
	}
	// detach all labels linked to LabelManager
	void resetLabelPtrList()
	{
		for (LabelPtrList::iterator i = labelPtrList_.begin(), ie = labelPtrList_.end(); i != ie; ++i) {
			(*i)->clear();
		}
		labelPtrList_.clear();
	}
public:
	LabelManager()
	{
		reset();
	}
	~LabelManager()
	{
		resetLabelPtrList();
	}
	void reset()
	{
		base_ = 0;
		labelId_ = 1;
		clabelDefList_.clear();
		clabelUndefList_.clear();
		resetLabelPtrList();
	}
	void set(CodeArray *base) { base_ = base; }
	void defineClabel(Label& label)
	{
		define_inner(clabelDefList_, clabelUndefList_, getId(label), base_->getCurr());
		label.mgr = this;
		labelPtrList_.insert(&label);
	}
	void assign(Label& dst, const Label& src)
	{
		ClabelDefList::const_iterator i = clabelDefList_.find(src.id);
		if (i == clabelDefList_.end()) XBYAK_RISCV_THROW(ERR_LABEL_IS_NOT_SET_BY_L)
		define_inner(clabelDefList_, clabelUndefList_, dst.id, i->second.addr);
		dst.mgr = this;
		labelPtrList_.insert(&dst);
	}
	bool getAddr(const uint8_t** addr, const Label& label) const
	{
		ClabelDefList::const_iterator i = clabelDefList_.find(getId(label));
		if (i == clabelDefList_.end()) return false;
		*addr = i->second.addr;
		return true;
	}
	void addUndefinedLabel(const Label& label, const Jmp& jmp)
	{
		clabelUndefList_.insert(ClabelUndefList::value_type(label.id, jmp));
	}
	bool hasUndefClabel() const { return hasUndefinedLabel_inner(clabelUndefList_); }
	const uint8_t *getCode() const { return base_->getCode(); }
};

inline Label::Label(const Label& rhs)
{
	id = rhs.id;
	mgr = rhs.mgr;
	if (mgr) mgr->incRefCount(id, this);
}
inline Label& Label::operator=(const Label& rhs)
{
	if (id) XBYAK_RISCV_THROW_RET(ERR_LABEL_IS_ALREADY_SET_BY_L, *this)
	id = rhs.id;
	mgr = rhs.mgr;
	if (mgr) mgr->incRefCount(id, this);
	return *this;
}
inline Label::~Label()
{
	if (id && mgr) mgr->decRefCount(id, this);
}
inline const uint8_t* Label::getAddress() const
{
	if (mgr == 0) return 0;
	const uint8_t* addr;
	if (!mgr->getAddr(&addr, *this)) return 0;
	return addr;
}

namespace local {

template<size_t n>
struct Bit {
	uint32_t v;
	Bit(uint32_t v)
		: v(v)
	{
		XBYAK_RISCV_ASSERT(inBit(v, n));
	}
	Bit(const Reg& r)
		: v(r.getIdx())
	{
	}
};

} // local

class CodeGenerator : public CodeArray {
public:
	enum LabelType {
		T_jal,
		T_SHORT,
		T_NEAR,
		T_FAR, // far jump
		T_AUTO // T_SHORT if possible
	};
	enum AqRlType {
		T_aq = 2,
		T_rl = 1,
		T_aqrl = 3,
	};
	typedef local::Bit<3> Bit3;
	typedef local::Bit<5> Bit5;
	typedef local::Bit<7> Bit7;
	typedef local::Bit<12> Bit12;
private:
	CodeGenerator operator=(const CodeGenerator&) = delete;
	LabelManager labelMgr_;
	int XLEN_;
	bool isRV32_;
	bool supportRVC_;
	void opJmp(const Label& label, const Jmp& jmp)
	{
		const uint8_t* addr = 0;
		if (labelMgr_.getAddr(&addr, label)) { /* label exists */
			appendBytes(jmp.encode(addr), jmp.encSize());
			return;
		}
		appendBytes(0, jmp.encSize());
		labelMgr_.addUndefinedLabel(label, jmp);
	}
	uint32_t enc2(uint32_t a, uint32_t b) const { return (a<<7) | (b<<15); }
	uint32_t enc3(uint32_t a, uint32_t b, uint32_t c) const { return enc2(a, b) | (c<<20); }
	void Rtype(Bit7 opcode, Bit3 funct3, Bit7 funct7, Bit5 rd, Bit5 rs1, Bit5 rs2)
	{
		uint32_t v = (funct7.v<<25) | (funct3.v<<12) | opcode.v | enc3(rd.v, rs1.v, rs2.v);
		append4B(v);
	}
	void Itype(Bit7 opcode, Bit3 funct3, Bit5 rd, Bit5 rs1, int imm)
	{
		if (!local::inSBit(imm, 12)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (imm<<20) | (funct3.v<<12) | opcode.v | enc2(rd.v, rs1.v);
		append4B(v);
	}
	void Stype(Bit7 opcode, Bit3 funct3, Bit5 rs1, Bit5 rs2, int imm)
	{
		if (!local::inSBit(imm, 12)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = ((imm>>5)<<25) | (funct3.v<<12) | opcode.v | enc3(imm & local::mask(5), rs1.v, rs2.v);
		append4B(v);
	}
	void Utype(Bit7 opcode, Bit5 rd, uint32_t imm)
	{
		if (imm >= (1u << 20)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (imm<<12) | opcode.v | (rd.v<<7);
		append4B(v);
	}
	void opShift(Bit7 pre, Bit3 funct3, Bit7 opcode, Bit5 rd, Bit5 rs1, uint32_t shamt, int range = 0)
	{
		if (range == 0) range = isRV32_ ? 5 : 6;
		if (shamt >= (1u << range)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (pre.v<<25) | (funct3.v<<12) | opcode.v | enc3(rd.v, rs1.v, shamt);
		append4B(v);
	}
	void opAtomic(Bit5 rd, Bit5 rs2, Bit5 addr, Bit5 funct5, Bit3 funct3, uint32_t flag)
	{
		assert(flag <= 3);
		Rtype(0x2f, funct3.v, (funct5.v << 2) | flag, rd, addr, rs2);
	}
	bool isValiCidx(uint32_t idx) const { return 8 <= idx && idx < 16; }
	// c.addi4spn(rd, imm) = c.addi(rd, x2, imm)
	bool c_addi(const Reg& rd, const Reg& rs, uint32_t imm)
	{
		if (rs != sp) return false;
		uint32_t idx = rd.getIdx();
		if (!isValiCidx(idx) || imm == 0 || (imm % 4) != 0 || imm >= 1024) return false;
		uint32_t v = ((idx-8)<<2) | get5to4_9to6_2_3_z5(imm);
		append2B(v);
		return true;
	}
	bool c_lw(const Reg& rd, const Reg& rs, int imm)
	{
		uint32_t dIdx = rd.getIdx();
		uint32_t sIdx = rs.getIdx();
		if (!isValiCidx(dIdx) || !isValiCidx(sIdx) || (imm % 4) != 0 || imm < 0 || imm >= (1 << 7)) return false;
		uint32_t v = (2<<13) | ((sIdx-8)<<7) | ((dIdx-8)<<2) | get5to3_z3_2_6_z5(imm);
		append2B(v);
		return true;
	}
	bool c_ld(const Reg& rd, const Reg& rs, int imm)
	{
		uint32_t dIdx = rd.getIdx();
		uint32_t sIdx = rs.getIdx();
		if (!isValiCidx(dIdx) || !isValiCidx(sIdx) || (imm % 8) != 0 || imm < 0 || imm >= (1 << 8)) return false;
		uint32_t v = (3<<13) | ((sIdx-8)<<7) | ((dIdx-8)<<2) | get5to3_z3_7_6_z5(imm);
		append2B(v);
		return true;
	}
public:
	void L(Label& label) { labelMgr_.defineClabel(label); }
	Label L() { Label label; L(label); return label; }
	/*
		assign src to dst
		require
		dst : does not used by L()
		src : used by L()
	*/
	void assignL(Label& dst, const Label& src) { labelMgr_.assign(dst, src); }
	/*
		put address of label to buffer
		@note the put size is 4(32-bit), 8(64-bit)
	*/
	void putL(const Label &label)
	{
		Jmp jmp(getCurr());
		const uint8_t* addr = 0;
		if (labelMgr_.getAddr(&addr, label)) {
			appendBytes(size_t(addr), jmp.encSize());
			return;
		}
		appendBytes(0, jmp.encSize());
		labelMgr_.addUndefinedLabel(label, jmp);
	}

	// constructor
	CodeGenerator(size_t maxSize = DEFAULT_MAX_CODE_SIZE, void *userPtr = DontSetProtectRWE, Allocator *allocator = 0)
		: CodeArray(maxSize, userPtr, allocator)
		, XLEN_(64)
		, isRV32_(false)
		, supportRVC_(false)
	{
		labelMgr_.set(this);
	}
	void reset()
	{
		ClearError();
		resetSize();
		labelMgr_.reset();
		labelMgr_.set(this);
		XLEN_ = 64;
		isRV32_ = false;
		supportRVC_ = false;
	}
	void setRV32(bool on = true)
	{
		isRV32_ = on;
		XLEN_ = on ? 32 : 64;
	}
	void supportRVC(bool on = true)
	{
		supportRVC_ = on;
	}
	bool hasUndefinedLabel() const { return labelMgr_.hasUndefClabel(); }
	static inline void clearCache(void *p, size_t n)
	{
#ifdef _WIN32
		FlushInstructionCache(GetCurrentProcess(), begin, n);
#elif defined(__APPLE__)
		sys_icache_invalidate(begin, n);
#else
		__builtin___clear_cache((char *)p, (char *)p + n);
#endif
	}
	/*
		MUST call ready() to complete generating code if you use AutoGrow mode.
		It is not necessary for the other mode if hasUndefinedLabel() is true.
	*/
	void ready(ProtectMode mode = PROTECT_RWE)
	{
		if (hasUndefinedLabel()) XBYAK_RISCV_THROW(ERR_LABEL_IS_NOT_FOUND)
		if (useProtect()) setProtectMode(mode);
		clearCache(top_, size_);
	}
	// set read/exec
	void readyRE() { return ready(PROTECT_RE); }

#ifndef XBYAK_RISCV_DONT_READ_LIST
#include "xbyak_riscv_mnemonic.hpp"
#endif
};

#ifdef _MSC_VER
	#pragma warning(pop)
#endif
} // Xbyak_riscv

