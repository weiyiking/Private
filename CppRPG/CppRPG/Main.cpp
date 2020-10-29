#include <iostream>
#include "GameLogic.h"


using namespace std;

int main()
{

	GameLogic::Get()->Run();
	GameLogic::Get()->Run();
	GameLogic::Get()->Run();


	system("pause");
	return 0;
}