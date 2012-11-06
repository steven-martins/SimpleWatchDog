// ===================================
// File : CWAbsTcpSocket.h
// author : MARTINS Steven 
// mail : steven.martins@epitech.eu 
// created : jeudi 16 décembre 2010
// LastEdit : jeudi 16 décembre 2010
// ===================================

#ifndef _CWABSTCPSOCKET_H_
#define _CWABSTCPSOCKET_H_

#include "IAbsTcpSocket.h"

#ifdef _WIN32

class CWAbsTcpSocket : public IAbsTcpSocket
{
public:
	CWAbsTcpSocket(void);
	virtual ~CWAbsTcpSocket(void);

	void Listen(unsigned short port);
	void Connect(std::string ip, unsigned short port);
	SOCKET *getSocket();
	bool isValid() const;
	int Read(char *buf, int len);
	void Write(const char *buf, int len);
	IAbsTcpSocket *accept();
	void close();
	unsigned int getBytesAvailables();
	const std::string	&getIp() const;
	void			setIp(char *);

private:
	std::string		_ip;
	SOCKET		_socket;
	WSADATA		_wsadata;
	SOCKADDR_IN	_addr;
};

typedef CWAbsTcpSocket AbsTcpSocket;

#endif

#endif
