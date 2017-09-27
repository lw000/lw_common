#include "lock.h"

lw_auto_lock::lw_auto_lock(lw_lock_abstract* lock)
{
	this->_lock = lock;
	this->_lock->lock();
}

lw_auto_lock::~lw_auto_lock(void)
{
	this->_lock->unlock();
}

lw_fast_lock::lw_fast_lock()
{
#ifdef _WIN32
	::InitializeCriticalSection(&this->_cs);
#else

#endif
}


lw_fast_lock::~lw_fast_lock(void)
{
#ifdef _WIN32
	::DeleteCriticalSection(&this->_cs);
#else

#endif
}

void lw_fast_lock::lock()
{
#ifdef _WIN32
	::EnterCriticalSection(&this->_cs);
#else

#endif	
}

void lw_fast_lock::unlock()
{
#ifdef _WIN32
	::LeaveCriticalSection(&this->_cs);
#else

#endif	
}