#ifndef __ABSTCPSOCKET_H__
# define __ABSTCPSOCKET_H__

# ifdef _WIN32
#  include "CWAbsTcpSocket.h"
typedef CWAbsTcpSocket AbsTcpSocket;
# else
#  include "CUAbsTcpSocket.h"
typedef CUAbsTcpSocket AbsTcpSocket;
# endif

#endif
