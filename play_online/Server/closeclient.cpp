#include <vector>
#include <map>

#include <winsock2.h>

#include "Client.h"
#include "Point.h"

void closeclient(std::vector<Client*>& Clients, std::map<Client*, Point>& Situation, Client* client)
{

    /* 클라이언트 리스트에서 client를 지움. */
    for(std::vector<Client*>::iterator it = Clients.begin();it != Clients.end();it++)
    {
        if(client->socket.read_socket == (*it)->socket.read_socket && client->socket.write_socket == (*it)->socket.write_socket) // 지울 대상이 맞는지 판단
        {
            Clients.erase(it);
            closesocket(client->socket.write_socket);
            closesocket(client->socket.read_socket);
            break;
        }
    }
    for(std::map<Client*, Point>::iterator it = Situation.begin();it != Situation.end();it++)
    {
        if(it->first == client) // 지울 대상을 찾으면
        {
            Situation.erase(it);
            closesocket(client->socket.write_socket);
            closesocket(client->socket.read_socket);
            break;
        }
    }

    delete client;
}
