#pragma once

#include <iostream>

#include "Game.h"

#define NUMBER_OF_ITEMS 3

enum gridSize { Easy = 11, Normal = 18, ProH = 18, ProW = 32 };
enum Mines { EasyM = 10, NormalM = 40, ProM = 99 };
enum TextSize { EasyS = 22, NormalS = 34, ProS = 66 };


class Menu
{
	//Variables:
	int selItemIndex; // selected item index
	sf::Font menuFont;
	sf::Text menuText[NUMBER_OF_ITEMS];
	sf::Text title;

	//Window:
	sf::RenderWindow* mWindow;
	sf::VideoMode videoMode;

	//Sound for Select:
	sf::SoundBuffer bufferSelect;
	sf::Sound MenuSelect;

	//Sound for Move:
	sf::SoundBuffer bufferMove;
	sf::Sound MenuMove;


	//Parameters for game with default values:
	int gridH = Normal; 
	int gridW = Normal; 
	int maxMines = NormalM;
	int posCoef = NormalS;

	//Private fucntions:
	void initText();
	void initWindow();
	void initMenuSelect();
	void initMenuMove();
public:
	//Constructors and Destructors:
	Menu();
	~Menu();

	//Function:
	void run();
	void render(sf::RenderTarget*);
	void MoveUp();
	void MoveDown();
	int GetPressedInt();
};