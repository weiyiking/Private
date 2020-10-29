#pragma once
#include "PawnBase.h"
class Hero :
	public PawnBase
{
public:
	Hero();
	~Hero();

	void Init(string name, float hp, float atk, float def, float speed);
};

