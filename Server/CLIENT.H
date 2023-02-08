#ifndef CLIENT_H
#define CLIENT_H


#include "SOCKETS.h"

class Client{

public:
    char skin;
    short health_point;
    CON_SOCKETS socket;
};

#endif // CLIENT_H
