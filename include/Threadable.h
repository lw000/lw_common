#ifndef __Threadable_h__
#define __Threadable_h__

#include <functional>

typedef std::function<void()> ThreadHandler;

class Threadable
{
	friend class CoreThread;

public:
	static void milliSleep(unsigned long milli);

public:
	Threadable();
	virtual ~Threadable();

public:
	void start();
	void join();
	int yield();

protected:
	virtual int onStart() = 0;
	virtual int onRun() = 0;
	virtual int onEnd() = 0;

private:
	int _threadId;
};

class ThreadableC11 : public Threadable
{
public:
	ThreadableC11();
	virtual ~ThreadableC11();

public:
	void start(const ThreadHandler& run);

protected:
	virtual int onStart() override;
	virtual int onRun() override;
	virtual int onEnd() override;

private:
	ThreadHandler _on_run;
};

#endif	// !__Threadable_h__

