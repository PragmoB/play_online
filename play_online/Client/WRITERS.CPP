#include <iostream>
#include <windows.h>
#include <cstring>
#include <string>
#include <cstdio>

#include "json/json.h"

#include "POINT.H"
#include "textcolor.h"

#include "WRITERS.H"

extern const int MIN_X;
extern const int MAX_X;
extern const int MIN_Y;
extern const int MAX_Y;

extern const int FOOT_SIZE=9;
extern const int RESISTANCE=100;

using namespace std;

void textcolor(int foreground, int background);
char* my_itoa( int value, char* result, int base );
void gotoxy(int x, int y);
void Overwrite(string& target, int index, const char* value);
void WINAPI printFrame(string* target);
void ReadJson(char* data, Json::Value* root);


void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }
void DrawInterface(string* target, const int max_x, const int min_x, const int max_y, const int min_y)
{
    gotoxy(min_x-1, min_y-1);

    target[min_y-1][min_x-1] = '';
    for(int i=min_x-1;i < max_x;i++)
    {
        target[min_y-1][i+1] = '';
    }
    target[min_y-1][max_x+1] = '';

    for(int i=min_y;i < max_y+1;i++)
    {
        target[i][min_x-1] = '';
        target[i][max_x + 1] = '';
    }
    target[max_y + 1][min_x-1] = '';
    for(int i=min_x-1;i < max_x;i++)
    {
        target[max_y + 1][i+1] = '';
    }
    target[max_y + 1][max_x+1] = '';

    for(int i=0;i < strlen("Made With Jiwonjae, Rohyoungrae. Copyright (c) All rights reserved.");i++)
        target[min_y - 1][min_x + 3 + i] = ((char*)"Made With Jiwonjae, Rohyoungrae. Copyright (c) All rights reserved.")[i];
}

    Point health_var(int xpos, int ypos, int health_point)
    {
        Point health_graph;

        health_graph.xpos = xpos - health_point / 2;
        health_graph.ypos = ypos + 1;
        // 체력바를 표시할때 벽문자를 덮어씌우는지 판단
        // 내가 왼쪽 벽에 붙어있다면
        if(xpos - MIN_X <= health_point / 2)
        {
            health_graph.xpos = MIN_X;
        }
        else if(MAX_X - xpos <= health_point / 2) // 오른쪽 벽에 붙어있다면
            health_graph.xpos = MAX_X - health_point + 1;

        if(MAX_Y - ypos <= 0) // 내가 아래쪽 벽에 붙어있다면
            health_graph.ypos = MAX_Y - 1;

        return health_graph;
    }
unsigned int WINAPI writeMoving(void* value)
{
    string* target = ((Mv_Param*)value)->target;
    Json::Value data;
    Point myLoc = ((Mv_Param*)value)->myLoc;

    ReadJson(((Mv_Param*)value)->data, &data);

    if(data["xpos"].asInt() == myLoc.xpos && data["ypos"].asInt() == myLoc.ypos)
    {
        char tmp[10];
        my_itoa(data["health_point"].asInt(), tmp, 10);
        target[0]  = string(" 체력 ") + string(tmp) +  string(" 남음");

        printFrame(target);
    }

    if(data["xpos"].asInt() > data["before_x"].asInt()) // 왼쪽에서 오른쪽으로 이동했다면
    {
        Point health_pos;
        for(int i=data["before_x"].asInt()+1;i <= data["xpos"].asInt();i++)
        {
            Sleep(RESISTANCE);
            health_pos = health_var(i-1, data["ypos"].asInt(), data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = ' ';

            target[data["ypos"].asInt()][i-1] = ' ';


            target[data["ypos"].asInt()][i] = (char)data["skin"].asInt();

            health_pos = health_var(i, data["ypos"].asInt(), data["health_point"].asInt());

            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = '';

            printFrame(target);
        }
        target[data["before_y"].asInt()][data["before_x"].asInt()] = ' ';
        health_pos = health_var(data["before_x"].asInt(), data["before_y"].asInt(), data["health_point"].asInt());
        for(int i=0;i < data["health_point"].asInt();i++)
            target[health_pos.ypos][health_pos.xpos+i] = ' ';

        printFrame(target);
    }
    else if(data["xpos"].asInt() < data["before_x"].asInt()) // 오른쪽에서 왼쪽으로 이동했다면
    {
        Point health_pos;
        for(int i=data["before_x"].asInt()-1;i >= data["xpos"].asInt();i--)
        {
            Sleep(RESISTANCE);
            health_pos = health_var(i+1, data["ypos"].asInt(), data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = ' ';

            target[data["ypos"].asInt()][i+1] = ' ';


            target[data["ypos"].asInt()][i] = (char)data["skin"].asInt();

            health_pos = health_var(i, data["ypos"].asInt(), data["health_point"].asInt());

            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = '';

            printFrame(target);
        }
        target[data["before_y"].asInt()][data["before_x"].asInt()] = ' ';
        health_pos = health_var(data["before_x"].asInt(), data["before_y"].asInt(), data["health_point"].asInt());
        for(int i=0;i < data["health_point"].asInt();i++)
            target[health_pos.ypos][health_pos.xpos+i] = ' ';

        printFrame(target);
    }

    if(data["ypos"].asInt() > data["before_y"].asInt()) // 위쪽에서 아래쪽으로 이동했다면
    {
        Point health_pos;
        for(int i=data["before_y"].asInt()+1;i <= data["ypos"].asInt();i++)
        {
            Sleep(RESISTANCE);

            health_pos = health_var(data["xpos"].asInt(), i-1, data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = ' ';
            target[i-1][data["xpos"].asInt()] = ' ';

            health_pos = health_var(data["xpos"].asInt(), i, data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = '';
            target[i][data["xpos"].asInt()] = data["skin"].asInt();

            printFrame(target);
        }
        target[data["before_y"].asInt()][data["before_x"].asInt()] = ' ';
        health_pos = health_var(data["before_x"].asInt(), data["before_y"].asInt(), data["health_point"].asInt());
        for(int i=0;i < data["health_point"].asInt();i++)
            target[health_pos.ypos][health_pos.xpos+i] = ' ';

        printFrame(target);
    }
    else if(data["ypos"].asInt() < data["before_y"].asInt()) // 아래쪽에서 위쪽으로 이동했다면
    {
        Point health_pos;
        for(int i=data["before_y"].asInt()-1;i >= data["ypos"].asInt();i--)
        {
            Sleep(RESISTANCE);

            health_pos = health_var(data["xpos"].asInt(), i+1, data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = ' ';
            target[i+1][data["xpos"].asInt()] = ' ';

            health_pos = health_var(data["xpos"].asInt(), i, data["health_point"].asInt());
            for(int j=0;j < data["health_point"].asInt();j++)
                target[health_pos.ypos][health_pos.xpos+j] = '';
            target[i][data["xpos"].asInt()] = data["skin"].asInt();

            printFrame(target);
        }
        target[data["before_y"].asInt()][data["before_x"].asInt()] = ' ';
        health_pos = health_var(data["before_x"].asInt(), data["before_y"].asInt(), data["health_point"].asInt());
        for(int i=0;i < data["health_point"].asInt();i++)
            target[health_pos.ypos][health_pos.xpos+i] = ' ';

        printFrame(target);
    }
}
void WINAPI printFrame(string* target)
{
    static bool isRunning=false;

    // 동시 호출을 방지하기 위함
    if(isRunning)
        return;

    else
        isRunning = true;

    gotoxy(0, 0);
    for(int i=0;i < MAX_Y + 2;i++)
        cout << target[i] << endl;

    isRunning = false;
}
