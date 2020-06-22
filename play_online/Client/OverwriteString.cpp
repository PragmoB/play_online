#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void Overwrite(string& target, int index, const char* value)
{
    for(int i=0;i < strlen(value);i++)
        target[index+i] = value[i];
}
