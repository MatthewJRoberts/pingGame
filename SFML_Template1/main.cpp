#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <iostream>
#include "game.h"


int main()
{
	game game1;
	game1.runGame();
	return 0;
}