#ifndef PARAM_H
#define PARAM_H

#include <map>
#include <vector>

#include "Client.h"
#include "Point.h"

class param
{
public:
    std::map<Client*, Point>* Situation;
    std::vector<Client*>* Clients;
    Client* client;

    param(
    std::map<Client*, Point>* Situation,
    std::vector<Client*>* Clients,
    Client* client)
    {
        this->Situation = Situation;
        this->Clients = Clients;
        this->client = client;
    }
};

#endif // PARAM_H
