#include "client_func.h"

unsigned int WINAPI ClientMov(void* value)
{
    map<Client*, Point>& Situation = *((Mv_Param*)value)->Situation;
    Client* client = ((Mv_Param*)value)->client;
    Json::Value data;
    ReadJson(((Mv_Param*)value)->Mv_Buff, &data);

    if(data["xpos"].asInt() > data["before_x"].asInt()) // 왼쪽에서 오른쪽으로 이동했다면
    {
        for(int i=data["before_x"].asInt()+1;i <= data["xpos"].asInt();i++)
        {
            Sleep(RESISTANCE);
            Situation[client].xpos = i;
        }
    }
    else if(data["xpos"].asInt() < data["before_x"].asInt()) // 오른쪽에서 왼쪽으로 이동했다면
    {
        for(int i=data["before_x"].asInt()-1;i >= data["xpos"].asInt();i--)
        {
            Sleep(RESISTANCE);
            Situation[client].xpos = i;
        }
    }

    if(data["ypos"].asInt() > data["before_y"].asInt()) // 위쪽에서 아래쪽으로 이동했다면
    {
        for(int i=data["before_y"].asInt()+1;i <= data["ypos"].asInt();i++)
        {
            Sleep(RESISTANCE);
            Situation[client].ypos = i;
        }
    }
    else if(data["ypos"].asInt() < data["before_y"].asInt()) // 아래쪽에서 위쪽으로 이동했다면
    {
        for(int i=data["before_y"].asInt()-1;i >= data["ypos"].asInt();i--)
        {
            Sleep(RESISTANCE);
            Situation[client].ypos = i;
        }
    }
}
