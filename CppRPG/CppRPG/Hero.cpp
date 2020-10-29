#include "Hero.h"



Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::Init(string name, float hp, float atk, float def, float speed)
{
	Name = name;
	HP = hp;
	ATK = atk;
	Def = def;
	Speed = speed;
}
