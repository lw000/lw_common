#ifndef __lock_h__

#ifdef _WIN32
#include <Windows.h>
#else

#endif

class lw_lock_abstract
{
public:
	virtual ~lw_lock_abstract(void) {}

public:
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

class lw_auto_lock
{
public:
	lw_auto_lock(lw_lock_abstract* lock);
	~lw_auto_lock(void);

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

#ifdef _WIN32
	CRITICAL_SECTION _cs;
#else

#endif

};


#endif	//__lock_h__
