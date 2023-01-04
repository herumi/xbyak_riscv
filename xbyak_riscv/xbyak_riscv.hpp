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


namespace local {

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

namespace inner {

static const size_t ALIGN_PAGE_SIZE = 4096;

inline bool IsInDisp8(uint32_t x) { return 0xFFFFFF80 <= x || x <= 0x7F; }
inline bool IsInInt32(uint64_t x) { return ~uint64_t(0x7fffffffu) <= x || x <= 0x7FFFFFFFU; }

inline uint32_t VerifyInInt32(uint64_t x)
{
#if defined(XBYAK_RISCV64) && !defined(__ILP32__)
	if (!IsInInt32(x)) XBYAK_RISCV_THROW_RET(ERR_OFFSET_IS_TOO_BIG, 0)
#endif
	return static_cast<uint32_t>(x);
}

enum LabelMode {
	LasIs, // as is
	Labs, // absolute
	LaddTop // (addr + top) for mov(reg, label) with AutoGrow
};

} // inner

/*
	custom allocator
*/
struct Allocator {
	explicit Allocator(const std::string& = "") {} // same interface with MmapAllocator
	virtual uint8_t *alloc(size_t size) { return reinterpret_cast<uint8_t*>(AlignedMalloc(size, inner::ALIGN_PAGE_SIZE)); }
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
		const size_t alignedSizeM1 = inner::ALIGN_PAGE_SIZE - 1;
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
void *const AutoGrow = (void*)1; //-V566
void *const DontSetProtectRWE = (void*)2; //-V566

class CodeArray {
	enum Type {
		USER_BUF = 1, // use userPtr(non alignment, non protect)
		ALLOC_BUF, // use new(alignment, protect)
		AUTO_GROW // automatically move and grow memory if necessary
	};
	CodeArray(const CodeArray& rhs);
	void operator=(const CodeArray&);
	bool isAllocType() const { return type_ == ALLOC_BUF || type_ == AUTO_GROW; }
	struct AddrInfo {
		size_t codeOffset; // position to write
		size_t jmpAddr; // value to write
		int jmpSize; // size of jmpAddr
		inner::LabelMode mode;
		AddrInfo(size_t _codeOffset, size_t _jmpAddr, int _jmpSize, inner::LabelMode _mode)
			: codeOffset(_codeOffset), jmpAddr(_jmpAddr), jmpSize(_jmpSize), mode(_mode) {}
		uint64_t getVal(const uint8_t *top) const
		{
			uint64_t disp = (mode == inner::LaddTop) ? jmpAddr + size_t(top) : (mode == inner::LasIs) ? jmpAddr : jmpAddr - size_t(top);
			if (jmpSize == 4) disp = inner::VerifyInInt32(disp);
			return disp;
		}
	};
	typedef std::list<AddrInfo> AddrInfoList;
	AddrInfoList addrInfoList_;
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
	bool isCalledCalcJmpAddress_;

	bool useProtect() const { return alloc_->useProtect(); }
	/*
		allocate new memory and copy old data to the new area
	*/
	void growMemory()
	{
		const size_t newSize = (std::max<size_t>)(DEFAULT_MAX_CODE_SIZE, maxSize_ * 2);
		uint8_t *newTop = alloc_->alloc(newSize);
		if (newTop == 0) XBYAK_RISCV_THROW(ERR_CANT_ALLOC)
		for (size_t i = 0; i < size_; i++) newTop[i] = top_[i];
		alloc_->free(top_);
		top_ = newTop;
		maxSize_ = newSize;
	}
	/*
		calc jmp address for AutoGrow mode
	*/
	void calcJmpAddress()
	{
		if (isCalledCalcJmpAddress_) return;
		for (AddrInfoList::const_iterator i = addrInfoList_.begin(), ie = addrInfoList_.end(); i != ie; ++i) {
			uint64_t disp = i->getVal(top_);
			rewrite(i->codeOffset, disp, i->jmpSize);
		}
		isCalledCalcJmpAddress_ = true;
	}
public:
	enum ProtectMode {
		PROTECT_RW = 0, // read/write
		PROTECT_RWE = 1, // read/write/exec
		PROTECT_RE = 2 // read/exec
	};
	explicit CodeArray(size_t maxSize, void *userPtr = 0, Allocator *allocator = 0)
		: type_(userPtr == AutoGrow ? AUTO_GROW : (userPtr == 0 || userPtr == DontSetProtectRWE) ? ALLOC_BUF : USER_BUF)
		, alloc_(allocator ? allocator : (Allocator*)&defaultAllocator_)
		, maxSize_(maxSize)
		, top_(type_ == USER_BUF ? reinterpret_cast<uint8_t*>(userPtr) : alloc_->alloc((std::max<size_t>)(maxSize, 1)))
		, size_(0)
		, isCalledCalcJmpAddress_(false)
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
		addrInfoList_.clear();
		isCalledCalcJmpAddress_ = false;
	}
	void write1byte(int code)
	{
		if (size_ >= maxSize_) {
			if (type_ == AUTO_GROW) {
				growMemory();
			} else {
				XBYAK_RISCV_THROW(ERR_CODE_IS_TOO_BIG)
			}
		}
		top_[size_++] = static_cast<uint8_t>(code);
	}
	void write1byte(const uint8_t *code, size_t codeSize)
	{
		for (size_t i = 0; i < codeSize; i++) write1byte(code[i]);
	}
	void write1byte(uint64_t code, size_t codeSize)
	{
		if (codeSize > 8) XBYAK_RISCV_THROW(ERR_BAD_PARAMETER)
		for (size_t i = 0; i < codeSize; i++) write1byte(static_cast<uint8_t>(code >> (i * 8)));
	}
	void write4byte(uint32_t code) { write1byte(code, 4); }
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
	void dump() const
	{
		const uint8_t *p = getCode();
		size_t bufSize = getSize();
		size_t remain = bufSize;
		for (int i = 0; i < 4; i++) {
			size_t disp = 16;
			if (remain < 16) {
				disp = remain;
			}
			for (size_t j = 0; j < 16; j++) {
				if (j < disp) {
					printf("%02X", p[i * 16 + j]);
				}
			}
			putchar('\n');
			remain -= disp;
			if (remain == 0) {
				break;
			}
		}
	}
	/*
		@param offset [in] offset from top
		@param disp [in] offset from the next of jmp
		@param size [in] write size(1, 2, 4, 8)
	*/
	void rewrite(size_t offset, uint64_t disp, size_t size)
	{
		assert(offset < maxSize_);
		if (size != 1 && size != 2 && size != 4 && size != 8) XBYAK_RISCV_THROW(ERR_BAD_PARAMETER)
		uint8_t *const data = top_ + offset;
		for (size_t i = 0; i < size; i++) {
			data[i] = static_cast<uint8_t>(disp >> (i * 8));
		}
	}
	void save(size_t offset, size_t val, int size, inner::LabelMode mode)
	{
		addrInfoList_.push_back(AddrInfo(offset, val, size, mode));
	}
	bool isAutoGrow() const { return type_ == AUTO_GROW; }
	bool isCalledCalcJmpAddress() const { return isCalledCalcJmpAddress_; }
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

struct JmpLabel {
	size_t endOfJmp; /* offset from top to the end address of jmp */
	int jmpSize;
	inner::LabelMode mode;
	size_t disp; // disp for [rip + disp]
	explicit JmpLabel(size_t endOfJmp = 0, int jmpSize = 0, inner::LabelMode mode = inner::LasIs, size_t disp = 0)
		: endOfJmp(endOfJmp), jmpSize(jmpSize), mode(mode), disp(disp)
	{
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
		ClabelVal(size_t offset = 0) : offset(offset), refCount(1) {}
		size_t offset;
		int refCount;
	};
	typedef std::unordered_map<int, ClabelVal> ClabelDefList;
	typedef std::unordered_multimap<int, const JmpLabel> ClabelUndefList;
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
	void define_inner(DefList& defList, UndefList& undefList, const T& labelId, size_t addrOffset)
	{
		// add label
		typename DefList::value_type item(labelId, addrOffset);
		std::pair<typename DefList::iterator, bool> ret = defList.insert(item);
		if (!ret.second) XBYAK_RISCV_THROW(ERR_LABEL_IS_REDEFINED)
		// search undefined label
		for (;;) {
			typename UndefList::iterator itr = undefList.find(labelId);
			if (itr == undefList.end()) break;
			const JmpLabel *jmp = &itr->second;
			const size_t offset = jmp->endOfJmp - jmp->jmpSize;
			size_t disp;
			if (jmp->mode == inner::LaddTop) {
				disp = addrOffset;
			} else if (jmp->mode == inner::Labs) {
				disp = size_t(base_->getCurr());
			} else {
				disp = addrOffset - jmp->endOfJmp + jmp->disp;
#ifdef XBYAK_RISCV64
				if (jmp->jmpSize <= 4 && !inner::IsInInt32(disp)) XBYAK_RISCV_THROW(ERR_OFFSET_IS_TOO_BIG)
#endif
				if (jmp->jmpSize == 1 && !inner::IsInDisp8((uint32_t)disp)) XBYAK_RISCV_THROW(ERR_LABEL_IS_TOO_FAR)
			}
			if (base_->isAutoGrow()) {
				base_->save(offset, disp, jmp->jmpSize, jmp->mode);
			} else {
				base_->rewrite(offset, disp, jmp->jmpSize);
			}
			undefList.erase(itr);
		}
	}
	template<class DefList, class T>
	bool getOffset_inner(const DefList& defList, size_t *offset, const T& label) const
	{
		typename DefList::const_iterator i = defList.find(label);
		if (i == defList.end()) return false;
		*offset = i->second.offset;
		return true;
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
		define_inner(clabelDefList_, clabelUndefList_, getId(label), base_->getSize());
		label.mgr = this;
		labelPtrList_.insert(&label);
	}
	void assign(Label& dst, const Label& src)
	{
		ClabelDefList::const_iterator i = clabelDefList_.find(src.id);
		if (i == clabelDefList_.end()) XBYAK_RISCV_THROW(ERR_LABEL_IS_NOT_SET_BY_L)
		define_inner(clabelDefList_, clabelUndefList_, dst.id, i->second.offset);
		dst.mgr = this;
		labelPtrList_.insert(&dst);
	}
	bool getOffset(size_t *offset, const Label& label) const
	{
		return getOffset_inner(clabelDefList_, offset, getId(label));
	}
	void addUndefinedLabel(const Label& label, const JmpLabel& jmp)
	{
		clabelUndefList_.insert(ClabelUndefList::value_type(label.id, jmp));
	}
	bool hasUndefClabel() const { return hasUndefinedLabel_inner(clabelUndefList_); }
	const uint8_t *getCode() const { return base_->getCode(); }
	bool isReady() const { return !base_->isAutoGrow() || base_->isCalledCalcJmpAddress(); }
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
	if (mgr == 0 || !mgr->isReady()) return 0;
	size_t offset;
	if (!mgr->getOffset(&offset, *this)) return 0;
	return mgr->getCode() + offset;
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
		T_SHORT,
		T_NEAR,
		T_FAR, // far jump
		T_AUTO // T_SHORT if possible
	};
	typedef local::Bit<3> Bit3;
	typedef local::Bit<5> Bit5;
	typedef local::Bit<7> Bit7;
	typedef local::Bit<12> Bit12;
private:
	CodeGenerator operator=(const CodeGenerator&) = delete;
	LabelManager labelMgr_;
	bool isRV32_;
	template<class T>
	void putL_inner(T& label, bool relative = false, size_t disp = 0)
	{
		const int jmpSize = relative ? 4 : (int)sizeof(size_t);
		if (isAutoGrow() && size_ + 16 >= maxSize_) growMemory();
		size_t offset = 0;
		if (labelMgr_.getOffset(&offset, label)) {
			if (relative) {
				write1byte(inner::VerifyInInt32(offset + disp - size_ - jmpSize), jmpSize);
			} else if (isAutoGrow()) {
				write1byte(uint64_t(0), jmpSize);
				save(size_ - jmpSize, offset, jmpSize, inner::LaddTop);
			} else {
				write1byte(size_t(top_) + offset, jmpSize);
			}
			return;
		}
		write1byte(uint64_t(0), jmpSize);
		JmpLabel jmp(size_, jmpSize, (relative ? inner::LasIs : isAutoGrow() ? inner::LaddTop : inner::Labs), disp);
		labelMgr_.addUndefinedLabel(label, jmp);
	}
	void Rtype(Bit7 opcode, Bit3 funct3, Bit7 funct7, Bit5 rd, Bit5 rs1, Bit5 rs2)
	{
		uint32_t v = (funct7.v << 25) | (rs2.v << 20) | (rs1.v << 15) | (funct3.v << 12) | (rd.v << 7) | opcode.v;
		write4byte(v);
	}
	void Itype(Bit7 opcode, Bit3 funct3, Bit5 rd, Bit5 rs1, int imm)
	{
		if (!local::inSBit(imm, 12)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (imm << 20) | (rs1.v << 15) | (funct3.v << 12) | (rd.v << 7) | opcode.v;
		write4byte(v);
	}
	void Stype(Bit7 opcode, Bit3 funct3, Bit5 rs1, Bit5 rs2, int imm)
	{
		if (!local::inSBit(imm, 12)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = ((imm >> 5) << 25) | (rs2.v << 20) | (rs1.v << 15) | (funct3.v << 12) | ((imm & local::mask(5)) << 7) | opcode.v;
		write4byte(v);
	}
	void Utype(Bit7 opcode, Bit5 rd, uint32_t imm)
	{
		if (imm >= (1u << 20)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (imm << 12) | (rd.v << 7) | opcode.v;
		write4byte(v);
	}
	void opShift(Bit7 pre, Bit3 funct3, Bit7 opcode, Bit5 rd, Bit5 rs1, uint32_t shamt)
	{
		int range = isRV32_ ? 5 : 6;
		if (shamt >= (1u << range)) XBYAK_RISCV_THROW(ERR_IMM_IS_TOO_BIG)
		uint32_t v = (pre.v << 25) | (shamt << 20) | (rs1.v << 15) | (funct3.v << 12) | (rd.v << 7) | opcode.v;
		write4byte(v);
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
	void putL(const Label& label) { putL_inner(label); }

	// call(function pointer)
//	template<class Ret, class... Params>
//	void call(Ret(*func)(Params...)) { call(reinterpret_cast<const void*>(func)); }
//	void call(const void *addr) { opJmpAbs(addr, T_NEAR, 0, 0xE8); }


	enum { NONE = 256 };
	// constructor
	CodeGenerator(size_t maxSize = DEFAULT_MAX_CODE_SIZE, void *userPtr = 0, Allocator *allocator = 0)
		: CodeArray(maxSize, userPtr, allocator)
		, isRV32_(false)
	{
		labelMgr_.set(this);
	}
	void reset()
	{
		ClearError();
		resetSize();
		labelMgr_.reset();
		labelMgr_.set(this);
	}
	bool hasUndefinedLabel() const { return labelMgr_.hasUndefClabel(); }
	/*
		MUST call ready() to complete generating code if you use AutoGrow mode.
		It is not necessary for the other mode if hasUndefinedLabel() is true.
	*/
	void ready(ProtectMode mode = PROTECT_RWE)
	{
		if (hasUndefinedLabel()) XBYAK_RISCV_THROW(ERR_LABEL_IS_NOT_FOUND)
		if (isAutoGrow()) {
			calcJmpAddress();
			if (useProtect()) setProtectMode(mode);
		}
	}
	// set read/exec
	void readyRE() { return ready(PROTECT_RE); }
#ifdef XBYAK_RISCV_TEST
	void dump1()
	{
		for (size_t i = 0; i < size_; i++) printf("%02x", top_[size_ - 1 - i]);
		printf("\n");
		size_ = 0;
	}
#endif

#ifndef XBYAK_RISCV_DONT_READ_LIST
#include "xbyak_riscv_mnemonic.hpp"
#endif
};

#ifdef _MSC_VER
	#pragma warning(pop)
#endif
} // Xbyak_riscv

