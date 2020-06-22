#include <iostream>
#include <winsock2.h>
#include <conio.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "json/json.h"

#include <mmsystem.h>

#include "Point.h"
#include "textcolor.h"
#include "AttackEffect.h"
#include "Writers.h"
#include "Protocol_Types.h"

#define BUFF_SIZE 200

const int MIN_X=10;
const int MAX_X=150;
const int MIN_Y=6;
const int MAX_Y=30;

const int FOOT_SIZE=9;
const int RESISTANCE=100;

using namespace std;

unsigned int WINAPI readAs(void* readSock);

void textcolor(int foreground, int background);
void ReadJson(char* data, Json::Value* root);

char* my_itoa( int value, char* result, int base );
void Overwrite(string& target, int index, const char* value);
Point health_var(int xpos, int ypos, int health_point);

char buff_recv[BUFF_SIZE] = "";
char buff_send[BUFF_SIZE] = "";

Point myLoc;
char skin=0;

int main()
{
    HANDLE hThread = NULL;
    DWORD dwThreadID = NULL;

    myLoc.xpos = MIN_X;
    myLoc.ypos = MIN_Y;

    char input_var=0;

    Json::Value data;
    data["xpos"] = MIN_X;
    data["ypos"] = MIN_Y;

    cout << data["status"].asInt() << endl;

    WSADATA wsa;
    SOCKET readS;
    SOCKET writeS;
    struct sockaddr_in server;


    system("chcp 949");
    system("title play_online");
    system("COLOR 0F");
    system("mode con cols=170 lines=40");

    cout << " ĳ���͸� �����ϼ���." << endl;
    while(input_var < 33 || input_var > 126)
    {
        input_var = getch();
    }

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        cerr << " �ʱ�ȭ ����. �����ڵ�: %d" << WSAGetLastError();
        getch();
        return 1;
    }

    if((readS = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        cerr << " ���� ���� ���� : " << WSAGetLastError();
        WSACleanup();
        getch();
        return 1;
    }
    if((writeS = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        cerr << " ���� ���� ���� : " << WSAGetLastError();
        WSACleanup();
        getch();
        return 1;
    }

    cout << endl;
    cout << " ������ IP�� �����ּ���." << endl;
    cin >> buff_send;

    server.sin_addr.s_addr = inet_addr(buff_send);
    server.sin_family = AF_INET;
    server.sin_port = htons( 4570 );

    memset(buff_send, 0, BUFF_SIZE);

    if (connect(readS , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cerr << " ���� ����.";

        switch(WSAGetLastError())
        {
        case 2:
            cout << " ���� � �ð��� �ƴմϴ�. ������ ã�ƿ� �ּ���." << endl;
            break;

        case 10060:
            cout << " ���� ������ �ʹ� ������� ������ �ߴ��߽��ϴ�." << endl;
            break;

        default:
            cout << " �����ڵ�: " << WSAGetLastError() << endl;
        }
        closesocket(readS);
        WSACleanup();
        getch();
        return 1;
    }
    if (connect(writeS , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cerr << " ���� ����.";

        switch(WSAGetLastError())
        {
        case 2:
            cout << " ���� � �ð��� �ƴմϴ�. ������ ã�ƿ� �ּ���." << endl;
            break;

        case 10060:
            cout << " ���� ������ �ʹ� ������� ������ �ߴ��߽��ϴ�." << endl;
            break;


        default:
            cout << " �����ڵ�: " << WSAGetLastError() << endl;
        }
        closesocket(readS);
        WSACleanup();
        getch();
        return 1;
    }

    system("cls");

    data["status"] = CONNECT;
    data["xpos"] = MIN_X;
    data["ypos"] = MIN_Y;
    data["skin"] = skin = input_var;
    strcpy(buff_send, data.toStyledString().c_str());

    system("cls");
        hThread = (HANDLE)_beginthreadex(NULL,0, readAs ,(void*)&readS,0,(unsigned*)&dwThreadID);
        if(hThread == 0)
            cerr << "_beginthreadex Error";
    if(send(writeS, (char*)&buff_send, BUFF_SIZE, 0) < 0)
    {
        system("cls");
        cerr << " �������� ������ ���������ϴ�." << endl;

        closesocket(writeS);
        closesocket(readS);

        getch();
        exit(1);
    }


    while(1)
    {

        invalid_input:

        while(kbhit())
            getch();

        data["before_x"] = myLoc.xpos;
        data["before_y"] = myLoc.ypos;

        // ����Ű(W, A, S, D)�� �Է¹޴´�.
        input_var = getch();

        // ����� ��ǥ�� �����Ѵ�.
        switch(input_var)
        {
        case 'D' : case 'd':
            myLoc.xpos += FOOT_SIZE;

            data["status"] = MOVE;
            data["skin"] = skin;
            data["xpos"] = myLoc.xpos;
            data["ypos"] = myLoc.ypos;
            break;

        case 'A': case 'a':
            myLoc.xpos -= FOOT_SIZE;

            data["status"] = MOVE;
            data["skin"] = skin;
            data["xpos"] = myLoc.xpos;
            data["ypos"] = myLoc.ypos;
            break;

        case 'S': case 's':
            myLoc.ypos += FOOT_SIZE * 3 / 4;

            data["status"] = MOVE;
            data["skin"] = skin;
            data["xpos"] = myLoc.xpos;
            data["ypos"] = myLoc.ypos;
            break;

        case 'W': case 'w':
            myLoc.ypos -= FOOT_SIZE * 3 / 4;

            data["status"] = MOVE;
            data["skin"] = skin;
            data["xpos"] = myLoc.xpos;
            data["ypos"] = myLoc.ypos;
            break;

       case 'E': case 'e':
            data["status"] = E_ATTACK;
            data["skin"] = skin;
            data["xpos"] = myLoc.xpos;
            data["ypos"] = myLoc.ypos;
            break;

       case 'F': case 'f':
           data["status"] = 'f';
           break;

        default:
            goto invalid_input;
        }

        // ����� ���� �������� �˻��ϰ� �������� ����� �� ������ �������� ���� �����Ѵ�.
        myLoc.ypos < MIN_Y ? data["ypos"] = myLoc.ypos = MIN_Y : 1;
        myLoc.ypos > MAX_Y ? data["ypos"] = myLoc.ypos = MAX_Y : 1;
        myLoc.xpos < MIN_X ? data["xpos"] = myLoc.xpos = MIN_X : 1;
        myLoc.xpos > MAX_X ? data["xpos"] = myLoc.xpos = MAX_X : 1;

        strcpy(buff_send, data.toStyledString().c_str());

        if(send(writeS, (char*)&buff_send, strlen(buff_send), 0) < 0)
        {
            system("cls");
            cerr << " �������� ������ ���������ϴ�." << endl;

            closesocket(writeS);
            closesocket(readS);

            getch();
            exit(1);
        }
        memset(buff_send, 0, BUFF_SIZE);
        data.clear();

        // �Է� ���� �̵����� ���ڶ��
        if(input_var == 'D' ||
           input_var == 'd' ||
           input_var == 'A' ||
           input_var == 'a' ||
           input_var == 'S' ||
           input_var == 's' ||
           input_var == 'W' ||
           input_var == 'w')
        {
            Sleep(FOOT_SIZE * RESISTANCE + 10);
        }
        // ��ų�� �����߿� ������ �� ����.
        if(input_var == 'E' || input_var == 'e')
        {
            Sleep(870);
        }
    }
    return 0;
}

unsigned int WINAPI readAs(void* readSock)
{
 	Json::Value data;

    SOCKET sock = *(int*)readSock;

    DWORD dwThreadID = NULL;

    Point health_pos;
    string frame[MAX_Y+4];

    char E_Buff[200]="";
    char mv_Buff[200]="";

    for(int i=0;i < MAX_Y+4;i++)
        frame[i] = "                                                                                                                                                            ";

    textcolor(LIGHTCYAN, BLACK);

    DrawInterface(frame, MAX_X, MIN_X, MAX_Y, MIN_Y);
    printFrame(frame);


    memset(buff_recv, 0, BUFF_SIZE);


    Mv_Param mv_param;
    while(1)
    {
        if(recv(sock, (char*)&buff_recv, BUFF_SIZE, 0) < 0)
        {
            system("cls");
            cerr << " �������� ������ ���������ϴ�." << endl;
            getch();
            closesocket(sock);
            exit(1);
        }

        ReadJson(buff_recv, &data);
        memset(buff_recv, 0, BUFF_SIZE);

       // MessageBox(NULL, data.toStyledString().c_str(), "JSON_DATA", MB_ICONWARNING | MB_OK);

        switch((char)data["status"].asInt())
        {
        case MOVE:


            memset(mv_Buff, 0, 200);
            strcpy(mv_Buff, data.toStyledString().c_str());

            mv_param.target = frame;
            mv_param.data = mv_Buff;
            mv_param.myLoc = myLoc;

            _beginthreadex(NULL,0, writeMoving ,(void*)&mv_param, 0,(unsigned*)&dwThreadID);
            break;


        case E_ATTACK:


            memset(E_Buff, 0, 200);
            strcpy(E_Buff, data.toStyledString().c_str());

            Att_Param E_param;
            E_param.value = E_Buff;
            E_param.target = frame;

            _beginthreadex(NULL,0, E_Attack ,(void*)&E_param,0,(unsigned*)&dwThreadID);

            break;
        case HURT_E:

            if(data["xpos"].asInt() == myLoc.xpos && data["ypos"].asInt() == myLoc.ypos)
            {
                char tmp[10];
                my_itoa(data["health_point"].asInt(), tmp, 10);
               // frame[0]  = string(" ü�� ") + string(tmp) +  string(" ����");
            }
           // frame[data["ypos"].asInt()][data["xpos"].asInt()] = '*';
            //printFrame(frame);
            PlaySound(TEXT(".\\Sounds\\E_Hurt.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
            break;

        case CONNECT:
            frame[data["ypos"].asInt()][data["xpos"].asInt()] = data["skin"].asInt();

            health_pos = health_var(data["xpos"].asInt(), data["ypos"].asInt(), data["health_point"].asInt());
            for(int i=0;i < data["health_point"].asInt();i++)
                frame[health_pos.ypos][health_pos.xpos+i] = '';

            if(data["xpos"].asInt() == myLoc.xpos && data["ypos"].asInt() == myLoc.ypos)
            {
                char tmp[10];
                my_itoa(data["health_point"].asInt(), tmp, 10);
                frame[0]  = string(" ü�� ") + string(tmp) +  string(" ����");
            }

            printFrame(frame);
            break;

        case IMAGE:
            frame[data["ypos"].asInt()][data["xpos"].asInt()] = ' ';
            health_pos = health_var(data["xpos"].asInt(), data["ypos"].asInt(), data["health_point"].asInt());
            for(int i=0;i < data["health_point"].asInt();i++)
                frame[health_pos.ypos][health_pos.xpos+i] = ' ';

            printFrame(frame);
            break;
        case DIE:

            Sleep(900);
            system("cls");

            cout << " ü���� �� ���� �׾����ϴ� ����������";
            Sleep(7000);

            exit(1);
            break;

        case RECOVERY:

            PlaySound(TEXT(".\\Sounds\\Recovery.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);

            {
                char tmp[10];
                my_itoa(data["health_point"].asInt(), tmp, 10);
                Overwrite(frame[0], 0, (string(" ü�� ") + string(tmp) +  string(" ����")).c_str());
            }
            break;
        case SERVER_MSG:

            MessageBox(NULL, data["message"].asString().c_str(), data["title"].asString().c_str(), MB_ICONWARNING | MB_OK);
            break;
        }
        data.clear();
    }
}

char* my_itoa( int value, char* result, int base ) {
// check that the base if valid
if (base < 2 || base > 16) { *result = 0; return result; }

char* out = result;
int quotient = value;

do {
*out = "0123456789abcdef"[ std::abs( quotient % base ) ];
++out;
quotient /= base;
} while ( quotient );

// Only apply negative sign for base 10
if ( value < 0 && base == 10) *out++ = '-';

std::reverse( result, out );
*out = 0;
return result;
}
