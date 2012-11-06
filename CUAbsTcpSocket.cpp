#include "CUAbsTcpSocket.h"

#ifndef _WIN32

CUAbsTcpSocket::CUAbsTcpSocket(void) : _socket(-1), _port(0)
{}


CUAbsTcpSocket::~CUAbsTcpSocket(void)
{}

void CUAbsTcpSocket::Connect(std::string s, unsigned short port)
{
  struct protoent *pe;

  pe = getprotobyname("tcp");
  if ((_socket = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    throw "Impossible de creer une socket";
  SOCKADDR_IN sin;
  sin.sin_addr.s_addr = inet_addr(s.c_str());
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  _port = port;
  if ((connect(_socket, (struct sockaddr *)&sin, sizeof(SOCKADDR_IN))) < 0)
    throw "Probleme avec connect";
}

void CUAbsTcpSocket::Listen(unsigned short port)
{
  struct protoent *pe;

  pe = getprotobyname("tcp");
  if ((_socket = socket(PF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    throw "Impossible de creer une socket";
  SOCKADDR_IN sin;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if ((bind(_socket, (struct sockaddr *)&sin, sizeof(SOCKADDR_IN))) < 0)
    throw "Probleme avec Bind";
  if ((listen(_socket, 10)) < 0)
    throw "Probleme avec listen";
  std::cout << "Socket val : " << _socket << std::endl;
}

SOCKET *CUAbsTcpSocket::getSocket()
{
  return &_socket;
}

bool CUAbsTcpSocket::isValid() const
{
  if (_socket > 0)
    return true;
  return false;
}

int CUAbsTcpSocket::Read(char *buf, int len)
{
  if (_socket < 0)
    return -1;
  return recv(_socket, buf, len, 0);
}

void CUAbsTcpSocket::Write(const char *buf, int len)
{
  if (_socket < 0)
    return ;
  if (send(_socket, buf, len, 0) < 0)
    _socket = -1;
}

IAbsTcpSocket *CUAbsTcpSocket::accept()
{
  socklen_t len = sizeof(SOCKADDR_IN);

  if (_socket < 0)
    return NULL;
  SOCKET soock = ::accept(_socket, (struct sockaddr *)&_addr, &len);
  if (soock < 0)
    return NULL;
  std::cout << "Accept from :" << inet_ntoa(_addr.sin_addr)  << std::endl;

  CUAbsTcpSocket *sock = new CUAbsTcpSocket();
  sock->_socket = soock;
  sock->_ip.clear();
  sock->_ip.assign(inet_ntoa(_addr.sin_addr));
  return (sock);
}

void CUAbsTcpSocket::close()
{
  if (_socket < 0)
    return ;
  ::close(_socket);
  _socket = -1;
}

unsigned int CUAbsTcpSocket::getBytesAvailables()
{
  unsigned long int  avail = 0;

  if (_socket < 0)
    return (0);
  ioctl(_socket, FIONREAD, &avail);
  return ((unsigned int)avail);
}

SOCKADDR_IN	CUAbsTcpSocket::getSockAddr() const
{
  return (_addr);
}

const std::string	&CUAbsTcpSocket::getIp() const
{
  return (_ip);
}

void		CUAbsTcpSocket::setIp(char * s)
{
  _ip.clear();
  _ip.assign(s);
}

#endif
