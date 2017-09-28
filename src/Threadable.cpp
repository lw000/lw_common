#include "Threadable.h"

#ifdef WIN32
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#include <stddef.h>
#include <iostream>

typedef unsigned int(__stdcall *ThreadFun) (void *);

class CoreThread
{
public:
	static int __start(ThreadFun func, void *args)
	{
#ifndef WIN32
		int hThread;
		pthread_t recvthread;

		hThread = pthread_create(&recvthread, NULL, func, args);
		if (hThread != 0)
		{
			return -1;
		}
		else
		{
			pthread_detach(recvthread);
		}

		return recvthread;
#else
		unsigned int threadHandler;
		unsigned int  threadId;
		threadHandler = (int)_beginthreadex(NULL, 0, func, args, 0, &threadId);
		if (threadHandler == -1) {
			return -1;
		}
		::SetThreadPriority((HANDLE)threadHandler, THREAD_PRIORITY_NORMAL);

		return threadHandler;
#endif
	}

	static unsigned int __stdcall __thread_run(void *userdata)
	{
		Threadable *self = (Threadable *)userdata;

		self->onStart();
		self->onRun();
		self->onEnd();

#ifdef WIN32
		::_endthreadex(0);
#endif

		return 0;
	}
};

Threadable::Threadable(void) : _threadId(-1)
{
}

Threadable::~Threadable(void)
{
}

int Threadable::yield()
{
#ifdef WIN32
	return ::SwitchToThread();
#else	
	return sched_yield();
#endif
}

void Threadable::start()
{
	_threadId = CoreThread::__start(CoreThread::__thread_run, this);
}

void Threadable::join()
{
#ifdef WIN32
	DWORD d = ::WaitForSingleObject((HANDLE)_threadId, INFINITE);
	if (d == WAIT_FAILED) {
		DWORD derror = GetLastError();
		printf("WaitForSingleObject error. [%d]", derror);
	}
	else {
		if (d == WAIT_OBJECT_0) {

		}
		else if (d == WAIT_TIMEOUT) {

		}
		else if (d == WAIT_ABANDONED) {

		}
		else {

		}
	}

#else

	if (_threadId > 0)
	{
		pthread_join(_threadId, NULL);
	}

#endif
}

void Threadable::milliSleep(unsigned long milli)
{
#ifdef WIN32
	::Sleep(milli);
#else
	usleep(milli * 1000);
#endif
}