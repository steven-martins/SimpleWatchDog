#include "Checker.h"

#include "Scheduler.h"
#include <iostream>
#include <string>

Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

void Scheduler::pushChecker(const Checker &c)
{
	_list.push_back(c);
}

int Scheduler::getNextEvent() const
{
	int min = INT_MAX;
	for (std::list<Checker>::const_iterator it = _list.begin(); it != _list.end(); it++)
	{
		int diff = it->getNextDateInMs();
		if (diff < min)
			min = diff;
	}
	std::cout << "getNextEvent: " << min << std::endl;
	if (min > 3600000)
		min = 3600000;
	if (min < 0)
		return 0;
	return min;
}

void Scheduler::run()
{
	for (;;)
	{
		for(std::list<Checker>::iterator it = _list.begin(); it != _list.end(); it++)
		{
			if (it->timesUp())
				it->start();
		}
		Sleep(getNextEvent());
	}
}
