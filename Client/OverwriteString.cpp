#include <iostream>
#include <string>
#include <cstring>

void Overwrite(std::string& target, int index, const char* value)
{
    for(unsigned int i=0;i < strlen(value);i++)
        target[index+i] = value[i];
}
