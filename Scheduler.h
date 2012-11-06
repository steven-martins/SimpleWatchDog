#pragma once

#include <string>
#include <list>

#include "time.h"

#ifndef _WIN32
#define Sleep(value) usleep((value) * 1000)
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

class Checker;

class Scheduler
{
public:
	Scheduler(void);
	void pushChecker(const Checker &c);
	void run();
	~Scheduler(void);
private:
	int getNextEvent() const;

	std::list<Checker> _list;
};

