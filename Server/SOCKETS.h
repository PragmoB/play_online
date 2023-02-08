#ifndef SOCKETS_H
#define SOCKETS_H

#include <winsock2.h>

class CON_SOCKETS
{
public:
    SOCKET read_socket;
    SOCKET write_socket;
    char IP[15];
};

#endif // SOCKETS_H
