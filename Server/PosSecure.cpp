#include "Point.h"

bool isPosHack(Point& situation, Point& users)
{
    // 원래 클라이언트의 위치와 새로 받은 위치의 차가 1이상 난다면 핵이다.
    if(situation.xpos - users.xpos > 1 || situation.xpos - users.xpos < -1)
    {
        return true;
    }
    if(situation.ypos - users.ypos > 1 || situation.ypos - users.ypos < -1)
    {
        return true;
    }
    return false;
}
