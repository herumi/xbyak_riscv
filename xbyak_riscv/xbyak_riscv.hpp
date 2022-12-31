#pragma once
/*!
	@file xbyak_riscv.hpp
	@brief Xbyak_riscv ; JIT assembler for RISC-V
	@author herumi
	@url https://github.com/herumi/xbyak_riscv
	@note modified new BSD license
	http://opensource.org/licenses/BSD-3-Clause
*/
#include <stdint.h>
#include <assert.h>
#include <list>
#include <string>
#include <algorithm>
#ifndef NDEBUG
#include <iostream>
#endif

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
	VERSION = 0x1000 /* 0xABCD = A.BC.D */
};

inline uint32_t getVersion() const { return VERSION; }

enum {
	ERR_NONE = 0,
	ERR_BAD_ADDRESSING,
	ERR_INTERNAL // Put it at last.
};

inline const char *ConvertErrorToString(int err)
{
	static const char *errTbl[] = {
		"none",
		"bad addressing",
	};
	assert(ERR_INTERNAL + 1 == sizeof(errTbl) / sizeof(*errTbl));
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

#ifdef XBYAK_RISCV_USE_MAP_JIT
namespace util {

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

} // util
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
		if (util::getMacOsVersion() >= mojaveVersion) mode |= MAP_JIT;
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

class Address;

class Reg {
	int idx_;
public:
	constexpr Reg(int idx = 0)
		: idx_(idx)
	{
	}
	constexpr int getIdx() const { return idx_; }
	const char *toString() const
	{
		static const char *tbl[4] = {
			"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
			"x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15",
			"x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
			"x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31",
		};
		return tbl[idx_];
	}
	bool operator==(const Operand& rhs) const
	{
		return idx_ == rhs.idx_;
	}
	bool operator!=(const Operand& rhs) const { return !operator==(rhs); }
};

static const constexpr Reg x0(0), x1(1), x2(2), x3(3), x4(4), x5(5), x6(6), x7(7);
static const constexpr Reg x8(8), x9(9), x10(10), x11(11), x12(12), x13(13), x14(14), x15(15);
static const constexpr Reg x16(16), x17(17), x18(18), x19(19), x20(20), x21(21), x22(22), x23(23);
static const constexpr Reg x24(24), x25(25), x26(26), x27(27), x28(28), x29(29), x30(30), x31(31);

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
	MmapAllocator defaultAllocator_;
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
	void db(int code)
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
	void db(const uint8_t *code, size_t codeSize)
	{
		for (size_t i = 0; i < codeSize; i++) db(code[i]);
	}
	void db(uint64_t code, size_t codeSize)
	{
		if (codeSize > 8) XBYAK_RISCV_THROW(ERR_BAD_PARAMETER)
		for (size_t i = 0; i < codeSize; i++) db(static_cast<uint8_t>(code >> (i * 8)));
	}
	void dw(uint32_t code) { db(code, 2); }
	void dd(uint32_t code) { db(code, 4); }
	void dq(uint64_t code) { db(code, 8); }
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
	// global : stateList_.front(), local : stateList_.back()
	StateList stateList_;
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
#ifndef NDEBUG
		for (typename T::const_iterator i = list.begin(); i != list.end(); ++i) {
			std::cerr << "undefined label:" << i->first << std::endl;
		}
#endif
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
		stateList_.clear();
		stateList_.push_back(SlabelState());
		stateList_.push_back(SlabelState());
		clabelDefList_.clear();
		clabelUndefList_.clear();
		resetLabelPtrList();
	}
	void enterLocal()
	{
		stateList_.push_back(SlabelState());
	}
	void leaveLocal()
	{
		if (stateList_.size() <= 2) XBYAK_RISCV_THROW(ERR_UNDER_LOCAL_LABEL)
		if (hasUndefinedLabel_inner(stateList_.back().undefList)) XBYAK_RISCV_THROW(ERR_LABEL_IS_NOT_FOUND)
		stateList_.pop_back();
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
		if (i == clabelDefList_.end()) XBYAK_RISCV_THROW(ERR_LABEL_ISNOT_SET_BY_L)
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
	bool hasUndefSlabel() const
	{
		for (StateList::const_iterator i = stateList_.begin(), ie = stateList_.end(); i != ie; ++i) {
			if (hasUndefinedLabel_inner(i->undefList)) return true;
		}
		return false;
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

typedef enum {
	DefaultEncoding,
	VexEncoding,
	EvexEncoding
} PreferredEncoding;

class CodeGenerator : public CodeArray {
public:
	enum LabelType {
		T_SHORT,
		T_NEAR,
		T_FAR, // far jump
		T_AUTO // T_SHORT if possible
	};
private:
	CodeGenerator operator=(const CodeGenerator&) = delete;
	LabelManager labelMgr_;
public:
	using CodeArray::db;
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
	bool hasUndefinedLabel() const { return labelMgr_.hasUndefSlabel() || labelMgr_.hasUndefClabel(); }
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

#ifndef XBYAK_RISCV_DONT_READ_LIST
//#include "xbyak_mnemonic.h"
#endif
};

namespace util {
static const constexpr Mmx mm0(0), mm1(1), mm2(2), mm3(3), mm4(4), mm5(5), mm6(6), mm7(7);
static const constexpr Xmm xmm0(0), xmm1(1), xmm2(2), xmm3(3), xmm4(4), xmm5(5), xmm6(6), xmm7(7);
static const constexpr Ymm ymm0(0), ymm1(1), ymm2(2), ymm3(3), ymm4(4), ymm5(5), ymm6(6), ymm7(7);
static const constexpr Zmm zmm0(0), zmm1(1), zmm2(2), zmm3(3), zmm4(4), zmm5(5), zmm6(6), zmm7(7);
static const constexpr Reg32 eax(Operand::EAX), ecx(Operand::ECX), edx(Operand::EDX), ebx(Operand::EBX), esp(Operand::ESP), ebp(Operand::EBP), esi(Operand::ESI), edi(Operand::EDI);
static const constexpr Reg16 ax(Operand::AX), cx(Operand::CX), dx(Operand::DX), bx(Operand::BX), sp(Operand::SP), bp(Operand::BP), si(Operand::SI), di(Operand::DI);
static const constexpr Reg8 al(Operand::AL), cl(Operand::CL), dl(Operand::DL), bl(Operand::BL), ah(Operand::AH), ch(Operand::CH), dh(Operand::DH), bh(Operand::BH);
static const constexpr AddressFrame ptr(0), byte(8), word(16), dword(32), qword(64), xword(128), yword(256), zword(512);
static const constexpr AddressFrame ptr_b(0, true), xword_b(128, true), yword_b(256, true), zword_b(512, true);
static const constexpr Fpu st0(0), st1(1), st2(2), st3(3), st4(4), st5(5), st6(6), st7(7);
static const constexpr Opmask k0(0), k1(1), k2(2), k3(3), k4(4), k5(5), k6(6), k7(7);
static const constexpr BoundsReg bnd0(0), bnd1(1), bnd2(2), bnd3(3);
static const constexpr EvexModifierRounding T_sae(EvexModifierRounding::T_SAE), T_rn_sae(EvexModifierRounding::T_RN_SAE), T_rd_sae(EvexModifierRounding::T_RD_SAE), T_ru_sae(EvexModifierRounding::T_RU_SAE), T_rz_sae(EvexModifierRounding::T_RZ_SAE);
static const constexpr EvexModifierZero T_z;
#ifdef XBYAK_RISCV64
static const constexpr Reg64 rax(Operand::RAX), rcx(Operand::RCX), rdx(Operand::RDX), rbx(Operand::RBX), rsp(Operand::RSP), rbp(Operand::RBP), rsi(Operand::RSI), rdi(Operand::RDI), r8(Operand::R8), r9(Operand::R9), r10(Operand::R10), r11(Operand::R11), r12(Operand::R12), r13(Operand::R13), r14(Operand::R14), r15(Operand::R15);
static const constexpr Reg32 r8d(8), r9d(9), r10d(10), r11d(11), r12d(12), r13d(13), r14d(14), r15d(15);
static const constexpr Reg16 r8w(8), r9w(9), r10w(10), r11w(11), r12w(12), r13w(13), r14w(14), r15w(15);
static const constexpr Reg8 r8b(8), r9b(9), r10b(10), r11b(11), r12b(12), r13b(13), r14b(14), r15b(15), spl(Operand::SPL, true), bpl(Operand::BPL, true), sil(Operand::SIL, true), dil(Operand::DIL, true);
static const constexpr Xmm xmm8(8), xmm9(9), xmm10(10), xmm11(11), xmm12(12), xmm13(13), xmm14(14), xmm15(15);
static const constexpr Xmm xmm16(16), xmm17(17), xmm18(18), xmm19(19), xmm20(20), xmm21(21), xmm22(22), xmm23(23);
static const constexpr Xmm xmm24(24), xmm25(25), xmm26(26), xmm27(27), xmm28(28), xmm29(29), xmm30(30), xmm31(31);
static const constexpr Ymm ymm8(8), ymm9(9), ymm10(10), ymm11(11), ymm12(12), ymm13(13), ymm14(14), ymm15(15);
static const constexpr Ymm ymm16(16), ymm17(17), ymm18(18), ymm19(19), ymm20(20), ymm21(21), ymm22(22), ymm23(23);
static const constexpr Ymm ymm24(24), ymm25(25), ymm26(26), ymm27(27), ymm28(28), ymm29(29), ymm30(30), ymm31(31);
static const constexpr Zmm zmm8(8), zmm9(9), zmm10(10), zmm11(11), zmm12(12), zmm13(13), zmm14(14), zmm15(15);
static const constexpr Zmm zmm16(16), zmm17(17), zmm18(18), zmm19(19), zmm20(20), zmm21(21), zmm22(22), zmm23(23);
static const constexpr Zmm zmm24(24), zmm25(25), zmm26(26), zmm27(27), zmm28(28), zmm29(29), zmm30(30), zmm31(31);
static const constexpr Zmm tmm0(0), tmm1(1), tmm2(2), tmm3(3), tmm4(4), tmm5(5), tmm6(6), tmm7(7);
static const constexpr RegRip rip;
#endif
} // util

#ifdef _MSC_VER
	#pragma warning(pop)
#endif
} // Xbyak_riscv

