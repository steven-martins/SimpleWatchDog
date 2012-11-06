// ===================================
// File : CWAbsTcpSocket.cpp
// author : MARTINS Steven 
// mail : steven.martins@epitech.eu 
// created : jeudi 16 décembre 2010
// LastEdit : jeudi 16 décembre 2010
// ===================================

#include "CWAbsTcpSocket.h"
#include <iostream>

#ifdef _WIN32

CWAbsTcpSocket::CWAbsTcpSocket(void) : _socket(-1)
{
}


CWAbsTcpSocket::~CWAbsTcpSocket(void)
{
}

void CWAbsTcpSocket::Connect(std::string ip, unsigned short port)
{
	if (WSAStartup(MAKEWORD(2, 0), &_wsadata) != NO_ERROR)
		throw "Probleme avec WSAStartup";
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (_socket == INVALID_SOCKET)
		throw "Impossible de creer une socket";
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (connect(_socket, (SOCKADDR *)&sin, sizeof(sin))  == SOCKET_ERROR)
	{
		std::cout << "connect :" << WSAGetLastError() << std::endl;
		throw "Probleme avec Connect";
	}
}

void CWAbsTcpSocket::Listen(unsigned short port)
{
	if (WSAStartup(MAKEWORD(2, 0), &_wsadata) != NO_ERROR)
		throw "Probleme avec WSAStartup";
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (_socket == INVALID_SOCKET)
		throw "Impossible de creer une socket";
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (bind(_socket, (SOCKADDR *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		std::cout << "bind :" << WSAGetLastError() << std::endl;
		throw "Probleme avec Bind";
	}
	if (listen(_socket, 10) == SOCKET_ERROR)
	{
		std::cout << "listen :" << WSAGetLastError() << std::endl;
		throw "Probleme avec listen";
	}


	std::cout << "Socket val : " << _socket << std::endl;
}

SOCKET *CWAbsTcpSocket::getSocket()
{
	return &_socket;
}

bool CWAbsTcpSocket::isValid() const
{
	if (_socket > 0)
		return true;
	return false;
}

int CWAbsTcpSocket::Read(char *buf, int len)
{
	if (_socket < 0)
		return -1;
	return recv(_socket, buf, len, 0);
}

void CWAbsTcpSocket::Write(const char *buf, int len)
{
	if (_socket < 0)
		return ;
	if (send(_socket, buf, len, 0) < 0)
		_socket = -1;
}

IAbsTcpSocket *CWAbsTcpSocket::accept()
{
	int len = sizeof(_addr);

	if (_socket < 0)
		return NULL;
	SOCKET soock = ::accept(_socket, (sockaddr *)&_addr, &len);
	if (soock < 0)
	{
		OutputDebugString(TEXT("Problem with accept"));
		return NULL;
	}
	std::cout << "Accept from :" << inet_ntoa(_addr.sin_addr)  << std::endl;

	CWAbsTcpSocket *sock = new CWAbsTcpSocket();
	sock->_socket = soock;
	sock->setIp(inet_ntoa(_addr.sin_addr));

	//SO_NOSIGPIPE
	return sock;
}

void CWAbsTcpSocket::close()
{
	if (_socket < 0)
		return ;
	//shutdown(_socket, SD_BOTH);
	closesocket(_socket);
	_socket = -1;
	// WSACleanup();
}

unsigned int CWAbsTcpSocket::getBytesAvailables()
{
	u_long avail = -1;

	if (_socket < 0)
		return 0;
	ioctlsocket(_socket, FIONREAD, &avail);

	return (unsigned int)avail;
}

const std::string	&CWAbsTcpSocket::getIp() const
{
	return (_ip);
}

void			CWAbsTcpSocket::setIp(char *ip)
{
	_ip.clear();
	_ip.assign(ip);
}

#endif
