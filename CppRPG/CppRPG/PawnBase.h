#pragma once
#include <iostream>

using namespace std;

class PawnBase
{
public:
	PawnBase();
	~PawnBase();

	virtual void Init(string name,float hp,float atk,float def,float speed)=0;

protected:
	string Name;
	float HP;
	float ATK;
	float Def;
	float Speed;
};

