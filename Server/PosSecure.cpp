#include "Point.h"

bool isPosHack(Point& situation, Point& users)
{
    // ���� Ŭ���̾�Ʈ�� ��ġ�� ���� ���� ��ġ�� ���� 1�̻� ���ٸ� ���̴�.
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
