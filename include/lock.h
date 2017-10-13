#ifndef __lock_h__
#define __lock_h__

//#define _USE_SYS_LOCK
#define _USE_POSIX_LOCK

#if defined(_WIN32) || defined(WIN32)

//#	if _MSC_VER <= 1600
#		if defined(_USE_SYS_LOCK)
			#include <Windows.h>
#		elif defined(_USE_POSIX_LOCK)
			#include <pthread.h>
#		else
			#include <Windows.h>
#		endif

//#	endif

#else

#	if defined(_USE_POSIX_LOCK)
#		include <pthread.h>
#	endif

#endif

#ifdef _USE_STDCPP_LOCK
#endif

class lw_lock_abstract
{
public:
	lw_lock_abstract() {}
	virtual ~lw_lock_abstract(void) {}

private:
	lw_lock_abstract(const lw_lock_abstract&);
	lw_lock_abstract& operator=(const lw_lock_abstract&);

public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

class lw_lock_guard
{
public:
	lw_lock_guard(lw_lock_abstract* lock);
	~lw_lock_guard(void);

private:
	lw_lock_abstract* _lock;
};


class lw_fast_lock : public lw_lock_abstract
{
public:
	lw_fast_lock();
	virtual ~lw_fast_lock(void);

public:
	virtual void lock();
	virtual void unlock();

private:

#if defined(_USE_SYS_LOCK)
	CRITICAL_SECTION _cs;
#elif defined(_USE_POSIX_LOCK)
	pthread_mutex_t _t;
#elif defined(_USE_STDCPP_LOCK)
	std::mutex _t;
#else
	CRITICAL_SECTION _cs;
#endif

};


#endif	//__lock_h__
