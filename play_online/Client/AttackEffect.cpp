#include <cstdio>
#include "json/json.h"
#include <windows.h>

#include "AttackEffect.h"
#include "OverwriteString.cpp"
#include "WRITERS.H"

using namespace std;

void gotoxy(int x, int y);
void ReadJson(char* data, Json::Value* root);
extern void Overwrite(string& target, int index, const char* value);

extern const int MIN_X;
extern const int MAX_X;

extern const int MIN_Y;
extern const int MAX_Y;

unsigned int WINAPI F_Attack(void* param)
{
    //Insert Code
    return 1;
}
unsigned int WINAPI E_Attack(void* param)
{
    Json::Value data;
    ReadJson((char*)((Att_Param*)param)->value, &data);
    string* target = ((Att_Param*)param)->target;
    char _tmp[30]="";


    sprintf(_tmp, "�� %c��", (char)data["skin"].asInt());

	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 1, "����");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 1, _tmp);
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 1, "����");

	printFrame(target);
	memset(_tmp, 0, 30);
	Sleep(125);






	sprintf(_tmp, "���%c ���", (char)data["skin"].asInt());

	Overwrite(target[data["ypos"].asInt() + 2], data["xpos"].asInt() - 2, "������");
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 2, "������");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 2, _tmp);
	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 2, "������");
	Overwrite(target[data["ypos"].asInt() - 2], data["xpos"].asInt() - 2, "������");

	printFrame(target);
	memset(_tmp, 0, 30);
	Sleep(125);







	sprintf(_tmp, "�����%c ��ᢹ", (char)data["skin"].asInt());

	Overwrite(target[data["ypos"].asInt() - 3], data["xpos"].asInt() - 3, "�١������");
	Overwrite(target[data["ypos"].asInt() - 2], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 3, _tmp);
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt() + 2], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt() + 3], data["xpos"].asInt() - 3, "�١������");

	printFrame(target);
	memset(_tmp, 0, 30);
	Sleep(125);






	sprintf(_tmp, "����  %c   �ᢹ", (char)data["skin"].asInt());

	Overwrite(target[data["ypos"].asInt() - 3], data["xpos"].asInt() - 3, "�ޡޡޡޡޡޡ�");
	Overwrite(target[data["ypos"].asInt() - 2], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 3, "����      �ᢹ");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 3, _tmp);
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 3, "����      �ᢹ");
	Overwrite(target[data["ypos"].asInt() + 2], data["xpos"].asInt() - 3, "�������ᢹ");
	Overwrite(target[data["ypos"].asInt() + 3], data["xpos"].asInt() - 3, "�ޡޡޡޡޡޡ�");

	printFrame(target);
	memset(_tmp, 0, 30);
	Sleep(125);





	sprintf(_tmp, "��    %c     ��", (char)data["skin"].asInt());

	Overwrite(target[data["ypos"].asInt() - 3], data["xpos"].asInt() - 3, "�ޡޡޡޡޡޡ�");
	Overwrite(target[data["ypos"].asInt() - 2], data["xpos"].asInt() - 3, "��          ��");
	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 3, "��          ��");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 3, _tmp);
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 3, "��          ��");
	Overwrite(target[data["ypos"].asInt() + 2], data["xpos"].asInt() - 3, "��          ��");
	Overwrite(target[data["ypos"].asInt() + 3], data["xpos"].asInt() - 3, "�ޡޡޡޡޡޡ�");

    printFrame(target);
	memset(_tmp, 0, 30);
	Sleep(125);





	Overwrite(target[data["ypos"].asInt() - 3], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt() - 2], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt() - 1], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt() + 1], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt() + 2], data["xpos"].asInt() - 3, "              ");
	Overwrite(target[data["ypos"].asInt() + 3], data["xpos"].asInt() - 3, "              ");


	sprintf(_tmp, "%c", (char)data["skin"].asInt());
	Overwrite(target[data["ypos"].asInt()], data["xpos"].asInt(), _tmp);

	DrawInterface(target, MAX_X, MIN_X, MAX_Y, MIN_Y);

	printFrame(target);

    return 1;
}
