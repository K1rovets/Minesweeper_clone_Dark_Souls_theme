#pragma once

#include "Game.h"
#include "Menu.h"
#include <cstdlib>
#include <ctime>

int main()
{
	//RNG seed:
	srand(time(0));

	//Start main menu:
	Menu menu;
	menu.run();
	return 0;
}