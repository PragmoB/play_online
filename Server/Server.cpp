#include <iostream>

#include <conio.h>
#include <vector>
#include <map>
#include <process.h>

#include "json/json.h"

#include "Client.H"
#include "Point.h"
#include "PosSecure.h"
#include "judg-Skills.h"
#include "param.h"
#include "Protocol_Types.h"
#include "client_func.h"

#include <windows.h>

#define BUFF_SIZE 200
#define HEALTH_POINT 8;

using namespace std;
unsigned int WINAPI active(void* arg);

vector<Client*> Clients;
map<Client*, Point> Situation;

const int FOOT_SIZE=9;
const int RESISTANCE=100;

void closeclient(vector<Client*>& Clients, map<Client*, Point>& Situation, Client* client);
void eraseimage(map<Client*, Point>& Situation, vector<Client*>& Clients, Client* client);
void ReadJson(char* data, Json::Value* root);

int main()
{
    WSADATA wsa;
    SOCKET binding_socket;
    struct sockaddr_in server, client_addr;
    int client_addr_size;

    HANDLE hThread = NULL;
    DWORD dwThreadID = NULL;


    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cerr << " 초기화 실패. 에러코드: " << WSAGetLastError();
        return 1;
    }
    cout << " 초기화 성공" << endl;

    if((binding_socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        cerr << " 소켓 생성 실패. 에러코드: " << WSAGetLastError();
        WSACleanup();
        _getch();
        return 1;
    }
    cout << " 소켓 생성 성공" << endl;

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( 4570 );

    int nSockOpt = 1;
    setsockopt(binding_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&nSockOpt, sizeof(nSockOpt));
    if (-1 == bind (binding_socket, (struct sockaddr *) &server, sizeof (server)))
    {
        cerr << " bind()실행 에러";
        WSACleanup();
        closesocket(binding_socket);
        _getch();
        exit (1);
    }
    cout << " bind()실행 성공" << endl;

    if (-1 == listen (binding_socket, 5))
    {
        cerr << " 대기상태 모드 설정 실패.";
        WSACleanup();
        closesocket(binding_socket);
        _getch();
        exit (1);
    }
    cout << " 대기상태 모드 설정 성공" << endl;
    cout << endl;

    IP_Break:
    while(1)
    {
        Client* client = new Client();
        client_addr_size = sizeof (client_addr);

        if ( (client->socket.write_socket = accept (binding_socket, (struct sockaddr *) &client_addr, &client_addr_size)) == -1)
        {
            cerr << " 클라이언트 연결 수락 실패.";
        }
        if ( (client->socket.read_socket = accept (binding_socket, (struct sockaddr *) &client_addr, &client_addr_size)) == -1)
        {
            cerr << " 클라이언트 연결 수락 실패.";
        }

        strcpy_s(client->socket.IP, inet_ntoa(client_addr.sin_addr));

        /* 중복 IP접속 차단

        for(int i=0;i < Clients.size();i++)
        {
            if(!strcmp(client->socket.IP, Clients.at(i)->socket.IP)) // 같은 IP로 접속한 사람이라면
            {
                if(!strcmp(client->socket.IP, "127.0.0.1")) // 관리자는 중복 접속 허용
                    break;

                Json::Value data;

                data["status"] = SERVER_MSG;
                data["title"] = " IP중복 접속 차단";
                data["message"] = "같은 IP로는 접속이 불가능합니다.";

                send(client->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);

                closesocket(client->socket.write_socket);
                closesocket(client->socket.read_socket);

                delete client;
                goto IP_Break;
            }
        }
        /* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ*/

        Clients.push_back(client);

        cout << endl << endl;
        cout << " 클라이언트 접속.  소켓번호 : " << client->socket.write_socket
        << ' ' << client->socket.read_socket << endl;
        cout << " IP주소: " << inet_ntoa(client_addr.sin_addr) << endl << endl;


        hThread = (HANDLE)_beginthreadex(NULL,0, active ,(void*)client,0,(unsigned*)&dwThreadID);
        if(hThread == 0)
            cerr << "_beginthreadex Error";
    }
    return 0;
}

unsigned int WINAPI active(void* arg)
{
    Client* client = (Client*)arg;
    char buff[BUFF_SIZE];
    Json::Value data;
    Point point;
    DWORD dwThreadID = NULL;

    char Mv_Buff[200];

    // 나의 연결을 받음.
    if(recv(client->socket.read_socket, buff, BUFF_SIZE, 0) < 0)
    {
        cout << " 클라이언트 " << client->socket.write_socket << ' ' << client->socket.read_socket << " 번 연결 종료" << endl;
        closeclient(Clients, Situation, client);

        return 1;
    }
    ReadJson(buff, &data);
    data["health_point"] = HEALTH_POINT;

    // 나의 연결을 다른 클라이언트들에게 다 보냄.
    for(UINT i=0;i < Clients.size();i++)
    {
        // 연결을 보냄
        send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str()
             , strlen(data.toStyledString().c_str()), 0);
    }
    client->skin = (char)data["skin"].asInt();
    client->health_point = HEALTH_POINT;

    point.xpos = data["xpos"].asInt();
    point.ypos = data["ypos"].asInt();

   //     MessageBox(NULL, data.toStyledString().c_str(), "JSON_DATA", MB_ICONWARNING | MB_OK);


    Situation[client] = point;

    // 딴사람의 연결을 나에게 다 보냄.
    data.clear();
    data["status"] = CONNECT;
    for(UINT i=0;i < Clients.size();i++)
    {
        if(Clients.at(i) == client)
            break;

        Sleep(45);

        // 연결을 보냄
        data["skin"] = Clients.at(i)->skin;
        data["xpos"] = Situation[Clients.at(i)].xpos;
        data["ypos"] = Situation[Clients.at(i)].ypos;
        data["health_point"] = Clients.at(i)->health_point;

        send(client->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);
    }
    ReadJson(buff, &data);

    memset(buff, 0, BUFF_SIZE);
    while(1)
    {
        ignore:

        // 나의 무빙을 받음.
        if(recv(client->socket.read_socket, buff, BUFF_SIZE, 0) < 0)
        {
            cout << " 클라이언트 " << client->socket.write_socket << ' ' << client->socket.read_socket << " 번 연결 종료" << endl;
            eraseimage(Situation, Clients, client);
            closeclient(Clients, Situation, client);

            return 1;
        }
        data.clear();
        ReadJson(buff, &data);

        switch((char)data["status"].asInt())
        {
        case MOVE:
            strcpy_s(Mv_Buff, data.toStyledString().c_str());

            Mv_Param mv_param;
            mv_param.Situation = &Situation;
            mv_param.client = client;
            mv_param.Mv_Buff = Mv_Buff;

            if((HANDLE)_beginthreadex(NULL,0, ClientMov ,(void*)&mv_param,0,(unsigned*)&dwThreadID) == 0)
                cerr << "_beginthreadex Error";

            point.xpos = data["xpos"].asInt();
            point.ypos = data["ypos"].asInt();
            data["skin"] = client->skin;
            data["health_point"] = client->health_point;

            // 나의 무빙을 다른 클라이언트들에게 다 보냄.
            for(UINT i=0;i < Clients.size();i++)
            {
                // 무빙을 보냄
                send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

            }
            // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
            Situation[client] = point;
            memset(Mv_Buff, 0, 200);
            break;
        case E_ATTACK:

            data["skin"] = client->skin;
            data["xpos"] = Situation[client].xpos;
            data["ypos"] = Situation[client].ypos;

            // 나의 광역공격(E)를 다른 클라이언트들에게 다 보냄.
            for(UINT i=0;i < Clients.size();i++)
            {
                // 광역공격을 보냄
                send(Clients.at(i)->socket.write_socket, data.toStyledString().c_str(), strlen(data.toStyledString().c_str()), 0);
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

            }
            // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

            // 스킬 판정을 쓰레드로 구현
            param judgParam(&Situation, &Clients, client);
            if((HANDLE)_beginthreadex(NULL,0, judgE ,(void*)&judgParam,0,(unsigned*)&dwThreadID) == 0)
                cerr << "_beginthreadex Error";

            break;
        }
        memset(buff, 0, BUFF_SIZE);
    }
}
