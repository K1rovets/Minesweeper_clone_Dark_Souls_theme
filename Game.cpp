#include "Game.h"
#pragma once

//Private fucntions:
void Game::initWindow()
{
	videoMode.height = gridH * 32;
	videoMode.width = gridW * 32;

	this->window = new sf::RenderWindow(videoMode, "DARK BOMBS");
	this->window->setFramerateLimit(30);
}

void Game::initGrid()
{
	mapGrid = new Grid(gridH, gridW, maxMines);
	mapGrid->plantTiles();

	//Debugging
	//mapGrid->show();
}

void Game::initText()
{
	if (!this->DarkSouls.loadFromFile("./Resources/OptimusPrinceps.ttf"))
	{
		std::cout << "ERROR in Game.cpp. OptimusPrinceps.ttf not found!" << std::endl;
	}
	//Set text:
	Text.setFont(DarkSouls);
	Text.setCharacterSize(20);
	Text.setFillColor(sf::Color::Red);
	Text.setStyle(sf::Text::Bold);
	Text.setPosition(5, videoMode.height - 30);

	//Set Reset Text:
	ResetText.setFont(DarkSouls);
	ResetText.setCharacterSize(20);
	ResetText.setFillColor(sf::Color::Red);
	ResetText.setStyle(sf::Text::Bold);
	ResetText.setPosition(5, 5);

	//Set GameOverLoss text:
	GameOverLoss.setFont(DarkSouls);
	GameOverLoss.setCharacterSize(posCoef);
	GameOverLoss.setPosition(sf::Vector2f(videoMode.width / 2.8f, videoMode.height / 2.3f));

	//Set Victory text:
	VictoryText.setFont(DarkSouls);
	VictoryText.setCharacterSize(posCoef);
	VictoryText.setPosition(sf::Vector2f(videoMode.width / 4.8f, videoMode.height / 2.2f));
}

void Game::initSoundDeath()
{
	if (!bufferDeath.loadFromFile("./Resources/Death.wav"))
	{
		std::cout << "ERROR in Game.cpp. Death SOUND not found!" << std::endl;
	}
	deathEND.setBuffer(bufferDeath);
	deathEND.setVolume(50);
}

void Game::initSoundVictory()
{
	if (!bufferVictory.loadFromFile("./Resources/Victory.wav"))
	{
		std::cout << "ERROR in Game.cpp. Victory SOUND not found!" << std::endl;
	}
	victoryEND.setBuffer(bufferVictory);
	victoryEND.setVolume(50);
}

void Game::initButton()
{
	if (!this->musicTexture.loadFromFile("./Resources/SoundB.png"))
	{
		std::cout << "ERROR in Game.cpp. Button Texture not found!" << std::endl;
	}
	buttonMusic = new Button((float)(videoMode.width - 36), (float)(videoMode.height - 40), 160.f, 180.f, &musicTexture);
}


void Game::initMusic()
{
	if (!music.openFromFile("./Resources/FirelinkShrine.wav"))
	{
		std::cout << "ERROR in Game.cpp. Game MUSIC not found!" << std::endl;
	}
}

void Game::initRect(int r)
{
	rectangle.setSize(sf::Vector2f(videoMode.width, (float)2 * posCoef));
	if (r == 255)
		rectangle.setPosition(sf::Vector2f(videoMode.width / 35.f, videoMode.height / (posCoef == 22 ? 2.3f : posCoef == 34 ? 2.3f : 2.35f) ));
	if (r == 200)
		rectangle.setPosition(sf::Vector2f(videoMode.width / 35.f, videoMode.height / (posCoef == 22 ? 2.45f : posCoef == 34 ? 2.43f : 2.48f)));
}

//Constructors and Destructors
Game::Game(int gH, int gW, int maxM, int posC)
{
	gridH = gH;
	gridW = gW;
	maxMines = maxM;
	posCoef = posC;

	this->initWindow();
	this->initGrid();
	this->initText();
	this->initSoundDeath();
	this->initSoundVictory();
	this->initMusic();
	this->initButton();
}

Game::~Game()
{
	delete this->window;
	delete this->mapGrid;
	delete this->buttonMusic;
}

//Function to run game:
void Game::run()
{
	music.play();
	music.setVolume(10);
	music.setLoop(window->isOpen());

	while (window->isOpen())
	{
		this->updatePollEvents();
		this->updateText();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		//Reset grid:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			window->close();
		}

		//Reset grid:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			mapGrid->plantTiles();
			GameOver = false;
			Victory = false;
			flags = 0;		
			t = 0;
			deathEND.stop();
			victoryEND.stop();
		}

		//Get mouse position relative to the window:
		sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
		sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);
		int x = mousePos.x / 32;
		int y = mousePos.y / 32;

		//for debugging
		//cout << "X coor" << x << endl;
		//cout << "Y coor" << y << endl;

		buttonMusic->update(worldPos);
		if (buttonMusic->isClicked() == 1 && !click)
		{
			music.stop();
			click = true;
		}
		if (buttonMusic->isClicked() == 0 && click)
		{
			music.play();
			music.setVolume(10);
			music.setLoop(window->isOpen());
			click = false;
		}

		//mouse control:
		if (!GameOver && !Victory)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			{
				mapGrid->cheat();
				Victory = mapGrid->checkWin();
				if (Victory)
					victoryEND.play();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mapGrid->getTile(0, x, y) == 10)
					{
						mapGrid->update(x, y);
						if (mapGrid->getTile(0, x, y) == 0)
							mapGrid->revealTiles(x, y);
						else if (mapGrid->getTile(0, x, y) == 9)
						{
							mapGrid->explosion();
							GameOver = true;
							if (GameOver)
								deathEND.play();
						}
						Victory = mapGrid->checkWin();
						if (Victory)
							victoryEND.play();
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (mapGrid->getTile(0, x, y) == 10 && flags < maxMines)
					{
						mapGrid->update(x, y, 11);
						flags++;
					}
					else if (mapGrid->getTile(0, x, y) == 11)
					{
						mapGrid->update(x, y, 10);
						flags--;
					}
				}
			}
		}
	}
}

void Game::updateText()
{
	int counter = maxMines - flags;
	Text.setString("Bonfires left: " + std::to_string(counter));
	ResetText.setString("Press 'F2' to reset or 'E' to go back");
	GameOverLoss.setString("YOU DIED");
	VictoryText.setString("VICTORY ACHIEVED");
}

void Game::fadeIn(sf::Text& text, int r, int b, int g)
{
	if (t >= 0 && t <= 255)
	{
		text.setFillColor(sf::Color(r, b, g, t));
		initRect(r);
		rectangle.setFillColor(sf::Color(0, 0, 0, t));
		t+=3;
	}
}

void Game::renderText()
{
	window->draw(Text);
	window->draw(ResetText);
	if (GameOver)
	{
		fadeIn(GameOverLoss, 200, 0, 1);
		window->draw(rectangle);
		window->draw(GameOverLoss);
	}
	if (Victory)
	{
		fadeIn(VictoryText, 255, 215, 0);
		window->draw(rectangle);
		window->draw(VictoryText);
	}
}

void Game::render()
{
	window->clear(sf::Color::Black);

	//drawing game:
	mapGrid->render(this->window);

	this->renderText();

	buttonMusic->render(this->window);

	window->display();
}