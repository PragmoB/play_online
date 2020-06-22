#include "json.h"
#include <cstring>

void ReadJson(char* data, Json::Value* root)
{
 	Json::Reader reader;

 	if(data[0] != '{')
    {
        (*root)["status"] = '0';
        return;
    }

 	reader.parse(std::string(data), *root);
}
