#include <winsock2.h>

#include "Point.h"
#include "Client.h"
#include "Protocol_Types.h"

#include <map>
#include <vector>

#include "json/json.h"

void eraseimage(std::map<Client*, Point>& Situation, std::vector<Client*>& Clients, Client* client)
{
    Json::Value data;
    Client* other;

    data["status"] = IMAGE;
    data["xpos"] = Situation[client].xpos;
    data["ypos"] = Situation[client].ypos;
    data["health_point"] = client->health_point;

    // 지울 잔상을 다른 클라이언트들에게 다 보냄.
    for(int i=0;i < Clients.size();i++)
    {
        // 잔상을 보냄
        other = Clients.at(i);
        send(other->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);
    }
}
