#ifndef ATTACK_EFFECT_H
#define ATTACK_EFFECT_H

#include <string>

class Att_Param
{
public:
    void* value;
    std::string* target;
};

unsigned int WINAPI E_Attack(void* param);
unsigned int WINAPI F_Attack(void* param);

#endif // ATTACK_EFFECT_H
