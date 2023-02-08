#ifndef CLIENT_FUNC_H
#define CLIENT_FUNC_H

#include <map>

#include "json/json.h"

#include "CLIENT.H"
#include "POINT.H"

using namespace std;

extern const int FOOT_SIZE;
extern const int RESISTANCE;

void ReadJson(char* data, Json::Value* root);

class Mv_Param
{
public:
    map<Client*, Point>* Situation;
    Client* client;
    char* Mv_Buff;
};

unsigned int WINAPI ClientMov(void* value);

#endif // CLIENT_FUNC_H
