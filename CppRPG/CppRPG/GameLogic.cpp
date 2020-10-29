#include "GameLogic.h"
#include <iostream>




GameLogic::GameLogic()
{

	std::cout << "111" << std::endl;
}


GameLogic::~GameLogic()
{
}

GameLogic* GameLogic::Get()
{
	static GameLogic* GL = new GameLogic;
	return GL;
}

void GameLogic::Run()
{
	std::cout << "hello" << std::endl;
}
