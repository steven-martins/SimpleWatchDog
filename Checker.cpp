#include "Checker.h"
#include "time.h"

#ifdef _WIN32

int gettimeofday(struct timeval* p, struct timezone *tz) {
    ULARGE_INTEGER ul;
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ul.LowPart = ft.dwLowDateTime;
    ul.HighPart = ft.dwHighDateTime;
    ul.QuadPart /= 10ULL;
    ul.QuadPart -= 11644473600000000ULL;
    p->tv_usec = (long) (ul.QuadPart % 1000000LL);
    p->tv_sec = (long) (ul.QuadPart / 1000000LL);
    return 0;
}

#endif

Checker::Checker(const std::string &ip, short port, const std::string &action, int interval) :
	_ip(ip), _port(port), _action(action), _interval(interval), _lastStatus(true)
{
	updateDate();
}


Checker::~Checker(void)
{
}

bool Checker::timesUp() const
{
	t_tv current;
	t_tv res;

	gettimeofday(&current, NULL);
	tv_sub(current, _timestamp, &res);

	if (tvtoms(res) >= 0)
		return true;
	return false;
}

int Checker::getNextDateInMs() const
{
	t_tv current;
	t_tv res;

	gettimeofday(&current, NULL);
	tv_sub(_timestamp, current, &res);

	return tvtoms(res);
}

void Checker::start()
{
	std::cout << "Check: " << _ip << ":" << _port << std::endl;
	if (!check())
	{
		std::cout << "An error occured, action must be performed." << std::endl;
		doAction();
	}
	else
	{
		std::cout << "The service works fine" << std::endl;
	}
	updateDate();
}

bool Checker::doAction()
{
	if (system(_action.c_str()))
		onFailure();
	else
	{
		onSuccess();
		return true;
	}
	return false;
}

void Checker::onSuccess()
{
	_lastStatus = true;
	std::cout << "onSuccess" << std::endl;
}

void Checker::onFailure()
{
	_lastStatus = false;
	std::cout << "onFailure" << std::endl;
}

void Checker::updateDate()
{
	gettimeofday(&_timestamp, NULL);
	t_tv a;
	mstotv(_interval * 1000, &a);
	tv_add(_timestamp, a, &_timestamp);
	std::cout << "updateDate to: " << _timestamp.tv_sec << std::endl;
}

bool Checker::connect()
{
	try 
	{
		_socket.Connect(_ip, _port);
	}
	catch (const char *e)
	{
		std::cout << "[exception] " << e << std::endl;
		return false;
	}
	if (_socket.isValid())
		return true;
	return false;
}

bool Checker::check()
{
	return connect();
}

void Checker::disconnect()
{
	_socket.close();
}
