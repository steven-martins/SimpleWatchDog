#ifndef _CUABSTCPSOCKET_H_
# define _CUABSTCPSOCKET_H_

# include "IAbsTcpSocket.h"

#ifndef _WIN32
#  include <sys/ioctl.h>
#  include <unistd.h>

class CUAbsTcpSocket : public IAbsTcpSocket
{
 public:
  CUAbsTcpSocket(void);
  virtual ~CUAbsTcpSocket(void);

  void Listen(unsigned short port);
  void Connect(std::string ip, unsigned short port);
  SOCKET *getSocket();
  bool isValid() const;
  int Read(char *buf, int len);
  void Write(const char *buf, int len);
  IAbsTcpSocket *accept();
  void close();
  unsigned int getBytesAvailables();
  SOCKADDR_IN	getSockAddr() const;
  const std::string	&getIp() const;
  void		setIp(char *);

 private:
  SOCKET _socket;
  unsigned short _port;
  SOCKADDR_IN	_addr;
  std::string	_ip;
};

typedef CUAbsTcpSocket AbsTcpSocket;

# endif

#endif
