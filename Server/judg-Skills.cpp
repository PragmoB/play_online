#include "json/json.h"

#include <cstring>

#include "param.h"
#include "Protocol_Types.h"

#include <windows.h>

using namespace std;

void eraseimage(std::map<Client*, Point>& Situation, std::vector<Client*>& Clients, Client* client);

unsigned int toUINT(int num)
{
    if(num < 0)
        return num * -1;

    return num;
}

unsigned WINAPI judgE(void* value)
{
    map<Client*, Point>& Situation = *((param*)value)->Situation;
    vector<Client*>& Clients = *((param*)value)->Clients;
    Client* client = ((param*)value)->client;

    Point myLoc = Situation[client];
    Json::Value data;


    for(UINT i=0;i < Clients.size();i++)
    {
        if(Clients.at(i) == client)
            continue;
        Point Loc = Situation[Clients.at(i)];

        // 스킬범위에 들었다면
        if(toUINT(myLoc.xpos + 2 - Loc.xpos) <= 3)
            if(toUINT(myLoc.ypos - Loc.ypos) <= 1)
            {
                data["status"] = HURT_E; // hurt, 체력이
                data["health_point"] = --Clients.at(i)->health_point;
                data["xpos"] = Loc.xpos;
                data["ypos"] = Loc.ypos;

                for(UINT j=0;j < Clients.size();j++) // 클아이언트가 다쳤다는걸 다른 클라이언트들에게 다 보냄
                {
                    send(Clients.at(j)->socket.write_socket, data.toStyledString().c_str(),
                     strlen(data.toStyledString().c_str()), 0);
                }
                if(Clients.at(i)->health_point <= 0) // 체력을 깎고 체력이 다 딸면 게임 오버인거임~
                {
                    data["status"] = DIE; // die 죽음
                    send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str(),
                         strlen(data.toStyledString().c_str()), 0);

                    data.clear();

                    // 다른 클아이언트를 죽임으로써 체력을 회복한다.
                    data["status"] = RECOVERY;
                    data["health_point"] = ++client->health_point;
                    data["xpos"] = Situation[client].xpos;
                    data["ypos"] = Situation[client].ypos;

                    send(client->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);

                    data.clear();

                    closesocket(Clients.at(i)->socket.read_socket);
                    continue;
                }
            }
    }
    Sleep(125);

    for(UINT i=0;i < Clients.size();i++)
    {
        if(Clients.at(i) == client)
            continue;
        Point Loc = Situation[Clients.at(i)];

        // 스킬범위에 들었다면
        if(toUINT(myLoc.xpos + 2 - Loc.xpos) <= 5)
            if(toUINT(myLoc.ypos - Loc.ypos) <= 2)
            {
                data["status"] = HURT_E; // hurt, 스킬에 맞음
                data["health_point"] = --Clients.at(i)->health_point;
                data["xpos"] = Loc.xpos;
                data["ypos"] = Loc.ypos;

                for(UINT j=0;j < Clients.size();j++) // 클아이언트가 다쳤다는걸 다른 클라이언트들에게 다 보냄
                {
                    send(Clients.at(j)->socket.write_socket, data.toStyledString().c_str(),
                     strlen(data.toStyledString().c_str()), 0);
                }
                if(Clients.at(i)->health_point <= 0) // 체력을 깎고 체력이 다 딸면 게임 오버인거임~
                {
                    data["status"] = DIE; // die 죽음
                    send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str(),
                         strlen(data.toStyledString().c_str()), 0);

                    data.clear();

                    // 다른 클아이언트를 죽임으로써 체력을 회복한다.
                    data["status"] = RECOVERY;
                    data["health_point"] = ++client->health_point;
                    data["xpos"] = Situation[client].xpos;
                    data["ypos"] = Situation[client].ypos;

                    send(client->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);

                    data.clear();

                    eraseimage(Situation, Clients, client);
                    closesocket(Clients.at(i)->socket.read_socket);
                    continue;
                }
            }
    }
    Sleep(125);

    for(int a=0;a < 3;a++)
    {

        for(UINT i=0;i < Clients.size();i++)
        {
            if(Clients.at(i) == client)
                continue;
            Point Loc = Situation[Clients.at(i)];

            // 스킬범위에 들었다면
            if(toUINT(myLoc.xpos + 2 - Loc.xpos) <= 7)
                if(toUINT(myLoc.ypos - Loc.ypos) <= 3)
                {
                    data["status"] = HURT_E; // health, 체력 값에 변동이 있음
                    data["health_point"] = --Clients.at(i)->health_point;
                    data["xpos"] = Loc.xpos;
                    data["ypos"] = Loc.ypos;

                    for(UINT j=0;j < Clients.size();j++) // 클아이언트가 다쳤다는걸 다른 클라이언트들에게 다 보냄
                    {
                        send(Clients.at(j)->socket.write_socket, data.toStyledString().c_str(),
                        strlen(data.toStyledString().c_str()), 0);
                    }
                    if(Clients.at(i)->health_point <= 0) // 체력을 깎고 체력이 다 딸면 게임 오버인거임~
                    {
                        data["status"] = DIE; // die 죽음
                        send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str(),
                            strlen(data.toStyledString().c_str()), 0);

                        data.clear();

                        // 다른 클아이언트를 죽임으로써 체력을 회복한다.
                        data["status"] = RECOVERY;
                        data["health_point"] = ++client->health_point;
                        data["xpos"] = Situation[client].xpos;
                        data["ypos"] = Situation[client].ypos;

                        send(client->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);

                        data.clear();

                        closesocket(Clients.at(i)->socket.read_socket);
                        continue;
                    }
                }
        }
        Sleep(125);
    }
    return 0;
}
