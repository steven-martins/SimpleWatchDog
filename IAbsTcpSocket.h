#ifndef _IABSTCPSOCKET_H_
#define _IABSTCPSOCKET_H_

#include <iostream>
#include <string>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <WinSock2.h>
	#pragma comment(lib, "ws2_32.lib")
#else
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	#define SOCKET_ERROR -1
#endif

class IAbsTcpSocket
{
public:
	virtual void Listen(unsigned short port) = 0;
	virtual void Connect(std::string ip, unsigned short port) = 0;
	virtual SOCKET *getSocket() = 0;
	virtual bool isValid() const = 0;
	virtual int Read(char *buf, int len) = 0;
	virtual void Write(const char *buf, int len) = 0;
	virtual IAbsTcpSocket *accept() = 0;
	virtual void close() = 0;
	virtual unsigned int getBytesAvailables() = 0;
	virtual	const std::string	&getIp() const = 0;
	virtual void			setIp(char *) = 0;
	//virtual ~IAbsTcpSocket();
};

#endif
