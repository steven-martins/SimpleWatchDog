#pragma once

#include <string>
#include <iostream>
#include <time.h>
#include "AbsTcpSocket.h"

#ifndef _WIN32
#include <sys/time.h>
#include <stdlib.h>
#endif

class Checker
{
public:
	Checker(const std::string &ip, short port, const std::string &action, int interval);
	void start();
	bool timesUp() const;
	int getNextDateInMs() const;

	~Checker(void);
private:
	bool doAction();
	void onSuccess();
	void onFailure();
	void updateDate();

	bool connect();
	bool check();
	void disconnect();

	bool _lastStatus;
	std::string _ip;
	short _port;
	int _interval;
	std::string _action;
	struct timeval _timestamp;
	AbsTcpSocket _socket;
};

