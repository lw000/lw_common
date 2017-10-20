#include "lock.h"

lw_lock_guard::lw_lock_guard(lw_lock_abstract* lock) : _lock(lock)
{
	this->_lock->lock();
}

lw_lock_guard::~lw_lock_guard(void)
{
	this->_lock->unlock();
}

lw_fast_lock::lw_fast_lock()
{
#if defined(_USE_SYS_LOCK)
	::InitializeCriticalSection(&this->_cs);
#elif defined(_USE_POSIX_LOCK)
	pthread_mutex_init(&_t, NULL);
#endif
}

lw_fast_lock::~lw_fast_lock(void)
{
#if defined(_USE_SYS_LOCK)
	::DeleteCriticalSection(&this->_cs);
#elif defined(_USE_POSIX_LOCK)
	pthread_mutex_destroy(&_t);
#endif
}

void lw_fast_lock::lock()
{
#if defined(_USE_SYS_LOCK)
	::EnterCriticalSection(&this->_cs);
#elif defined(_USE_POSIX_LOCK)
	pthread_mutex_lock(&_t);
#endif	
}

void lw_fast_lock::unlock()
{
#if defined(_USE_SYS_LOCK)
	::LeaveCriticalSection(&this->_cs);
#elif defined(_USE_POSIX_LOCK)
	pthread_mutex_unlock(&_t);
#else

#endif
}

//////////////////////////////////////////////////////////////////////////////////////////
lw_fast_cond::lw_fast_cond() {
	pthread_cond_init(&_t, nullptr);
}

lw_fast_cond::~lw_fast_cond() {
	pthread_cond_destroy(&_t);
}

void lw_fast_cond::wait(lw_fast_lock* lock) {
	pthread_cond_wait(&_t, &lock->_t);
}

void lw_fast_cond::signal() {
	pthread_cond_signal(&_t);
}

void lw_fast_cond::broadcast() {
	pthread_cond_broadcast(&_t);
}

