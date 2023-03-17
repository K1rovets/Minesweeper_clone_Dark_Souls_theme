#pragma once

#include "Grid.h"
#include "Button.h"

//GAME ENGINE

class Game
{
	//Variables:
	int gridH;
	int gridW;
	int maxMines;
	int posCoef; //text size for different difficulties

	bool GameOver = false;
	bool Victory = false;
	bool click = false;

	float t = 0; //fade in coefficient
	int flags = 0; //for of bonefires 

	//Window:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	//Grid:
	Grid* mapGrid;

	//Sound for endgame:
	sf::SoundBuffer bufferDeath;
	sf::Sound deathEND;

	sf::SoundBuffer bufferVictory;
	sf::Sound victoryEND;

	//Music for game:
	sf::Music music;

	//Rectangle for endgame:
	sf::RectangleShape rectangle;

	//Font and Texts:
	sf::Font DarkSouls;

	sf::Text Text;
	sf::Text ResetText;
	
	sf::Text GameOverLoss;
	sf::Text VictoryText;

	//Music button:
	sf::Texture musicTexture;
	Button* buttonMusic;

	//Private fucntions:
	void initWindow();
	void initGrid();
	void initText();
	void initRect(int);
	void initSoundDeath();
	void initSoundVictory();
	void initMusic();
	void initButton();
public:
	//Constructors and Destructors:
	Game(int, int, int, int);
	~Game();

	//Functions:
	void run();
	void updatePollEvents();
	void updateText();
	void fadeIn(sf::Text&, int, int, int);
	void render();
	void renderText();
};