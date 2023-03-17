#pragma once

#include "Grid.h"

/*	0  - blank tile		6  - 6 pointer		12 - BORDER
    1  - 1 pointer		7  - 7 pointer
    2  - 2 pointer		8  - 8 pointer
    3  - 3 pointer		9  - mine
    4  - 4 pointer		10 - hidden
    5  - 5 pointer		11 - flag*/

//Private function:
void Grid::initTextureAndSprite()
{
	//Load texture:
	if (!this->texture.loadFromFile("./Resources/textures2.jpg"))
	{
		cout << "ERROR in GRID.cpp. Texture not found!" << endl;
	}
    //Set sprite from texture:
    sprite.setTexture(texture);
}

//Constructor and Destructor:
Grid::Grid(int gH, int gW, int maxM)
{
	gridH = gH;
	gridW = gW;
	maxMines = maxM;
    toWin = (gridH - 2) * (gridW - 2) - maxMines;

	grid = new int** [subGrid];
	for (int sg = 0; sg < subGrid; ++sg)
	{
		grid[sg] = new int* [gridH];
		for (int row = 0; row < gridH; ++row)
		{
			grid[sg][row] = new int[gridW];
		}
	}

	this->initTextureAndSprite();
}

Grid::~Grid()
{
	delete[] grid[0][0];
	delete[] grid[0];
	delete[] grid;
	grid = 0;
}

//Getters:
int Grid::getTile(int sG, int x, int y)
{
    return grid[sG][y][x];
}

//Functions:
void Grid::plantTiles()
{
    int counter = 1; //for mines
    for (int row = 0; row < gridH; ++row)
    {
        for (int col = 0; col < gridW; ++col)
        {
            if ((row >= 1 && row < gridH-1) && (col >= 1 && col < gridW-1))
                grid[0][row][col] = 10;
            else
                grid[0][row][col] = 12;
                
            
            //Planting mines:
            if ((row >= 1 && row < gridH - 1) && (col >= 1 && col < gridW - 1))
            {
                if (rand() % 6 == 0 && counter <= maxMines)
                {
                    grid[1][row][col] = 9;
                    counter++;
                }
                else
                    grid[1][row][col] = 0;
            }
            else
                grid[1][row][col] = 12;
        }
    }

    for (int row = 0; row < gridH; ++row)
    {
        for (int col = 0; col < gridW; ++col)
        {
            //Planting more mines:
            if ((row >= 1 && row < gridH - 1) && (col >= 1 && col < gridW - 1))
            {
                if (grid[1][row][col] == 0 && rand() % 5 == 0 && counter <= maxMines)
                {
                    grid[1][row][col] = 9;
                    counter++;
                }
            }
        }
    }

    for (int row = 1; row <= gridH - 2; ++row)
        for (int col = 1; col <= gridW - 2; ++col)
        {
            //Count and display pointers to mines:
            int minePoint = 0;
            if (grid[1][row][col] == 9) //Center
            {
                continue;
            }
            if (grid[1][row - 1][col - 1] == 9) //North-West
            {
                minePoint++;
            }
            if (grid[1][row - 1][col] == 9) // North
            {
                minePoint++;
            }
            if (grid[1][row - 1][col + 1] == 9) // North-East
            {
                minePoint++;
            }
            if (grid[1][row][col + 1] == 9) // East
            {
                minePoint++;
            }
            if (grid[1][row + 1][col + 1] == 9) // South-East
            {
                minePoint++;
            }
            if (grid[1][row + 1][col] == 9) // South
            {
                minePoint++;
            }
            if (grid[1][row + 1][col - 1] == 9) // South-West
            {
                minePoint++;
            }
            if (grid[1][row][col - 1] == 9) // West
            {
                minePoint++;
            }
            grid[1][row][col] = minePoint;
        }
}


void Grid::update(int x, int y)
{
    grid[0][y][x] = grid[1][y][x];
}

//Used for bonefires only:
void Grid::update(int x, int y, int tile)
{
    grid[0][y][x] = tile;
}

bool Grid::validCoor(int x, int y)
{
    if ((x > 0 && x < gridW) && (y > 0 && y < gridH))
        return true;
    return false;
}

void Grid::revealTiles(int x, int y)
{
    if (grid[1][y][x] == 9)
    {
        return;
    }
    else
    {
        if (grid[1][y][x] >= 1 && grid[1][y][x] <= 8)
            grid[0][y][x] = grid[1][y][x];
        if (grid[1][y][x] == 0)
        {
            grid[0][y][x] = grid[1][y][x]; // reveal
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++)
                {
                    if (validCoor(x + j, y + i) && grid[0][y + i][x + j] == 10)
                    {
                        revealTiles(x + j, y + i);
                        //cout << x + j << ' ' << y + i << ' ' << endl; //Debug
                    }
                }
                //cout << endl; // Debug
            }
        }
    }
}

void Grid::explosion()
{
    for (int row = 1; row < gridH - 1; ++row)
    {
        for (int col = 1; col < gridW - 1; ++col)
        {
            if (grid[1][row][col] == 9 && grid[0][row][col] != 11)
            {
                update(col, row);
            }
        }
    }
}

bool Grid::checkWin()
{
    int count = 0;
    for (int row = 1; row < gridH - 1; ++row)
    {
        for (int col = 1; col < gridW - 1; ++col)
        {
            if (grid[0][row][col] != 10 && grid[0][row][col] != 11 && grid[0][row][col] != 9)
            {
                count++;
            }
        }
    }
    //cout << count << endl;
    if (count == toWin)
        return true;
    return false;

}

void Grid::render(sf::RenderTarget* whereTo)
{    
    for (int row = 1; row < gridH - 1; ++row)
    {
        for (int col = 1; col < gridW - 1; ++col)
        {
            sprite.setTextureRect(sf::IntRect(grid[0][row][col] * TILE_WIDTH, 0, TILE_WIDTH, TILE_WIDTH));
            sprite.setPosition(col * TILE_WIDTH, row * TILE_WIDTH);
            whereTo->draw(this->sprite);
        }
    }	
}

//Functions for debugging:
void Grid::show()
{
    for (int sg = 0; sg < subGrid; ++sg)
    {
        for (int row = 0; row < gridH; ++row)
        {
            for (int col = 0; col < gridW; ++col)
            {
                cout << grid[sg][row][col] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Grid::cheat()
{
    for (int row = 1; row < gridH - 1; ++row)
    {
        for (int col = 1; col < gridW - 1; ++col)
        {
            if (grid[1][row][col] != 9)
            {
                grid[0][row][col] = grid[1][row][col];
            }
        }
    }
}