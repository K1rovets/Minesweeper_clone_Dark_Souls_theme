#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#define TILE_WIDTH 32

using std::cout;
using std::endl;

// grid[0] = visible grid
// grid[1] = hidden grid

class Grid
{
	const int subGrid = 2;

	int gridH;
	int gridW;
	int maxMines;
	int toWin;

	int*** grid;

	sf::Texture texture;
	sf::Sprite sprite;

	//Private function:
	void initTextureAndSprite();
public:
	//Constructor and Destructor:	
	Grid(int gH, int gW, int maxM);
	~Grid();

	//Getters:
	int getTile(int, int, int);

	// Functions:
	void plantTiles();
	void update(int, int);
	void update(int, int, int);
	bool validCoor(int, int);
	void revealTiles(int, int);	
	void explosion();
	bool checkWin();
	void render(sf::RenderTarget*);

	//Functions for debugging:
	void show();
	void cheat();
};