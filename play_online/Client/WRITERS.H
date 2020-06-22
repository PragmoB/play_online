#ifndef WRITERS_H
#define WRITERS_H

#include <string>

#include "json/json.h"

#include "Point.h"

extern const int MIN_X;
extern const int MAX_X;

extern const int MIN_Y;
extern const int MAX_Y;

class Mv_Param
{
public:
    std::string* target;
    char* data;
    Point myLoc;
};

void gotoxy(int x, int y);
void DrawInterface(std::string* target, const int max_x=MAX_X, const int min_x=MIN_X, const int max_y=MAX_Y, const int min_y=MIN_Y);
void WINAPI printFrame(std::string* target);
unsigned int WINAPI writeMoving(void* value);

#endif // WRITERS_H
