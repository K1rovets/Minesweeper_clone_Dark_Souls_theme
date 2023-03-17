#include "Menu.h"

//Private fucntions:
void Menu::initText()
{
	//Load fonts:
	if (!this->menuFont.loadFromFile("./Resources/OptimusPrincepsSemiBold.ttf"))
	{
		std::cout << "ERROR in Menu.cpp. OptimusPrinceps.ttf not found!" << std::endl;
	}
}

void Menu::initWindow()
{
	mWindow = new sf::RenderWindow (sf::VideoMode(400, 400), "MAIN MENU", sf::Style::Titlebar | sf::Style::Close);
	mWindow->setFramerateLimit(30);
}

void Menu::initMenuSelect()
{
	if (!bufferSelect.loadFromFile("./Resources/Select.wav"))
	{
		std::cout << "ERROR in Menu.cpp. Select SOUND not found!" << std::endl;
	}
	MenuSelect.setBuffer(bufferSelect);
	MenuSelect.setVolume(50);
}

void Menu::initMenuMove()
{
	if (!bufferMove.loadFromFile("./Resources/Move.wav"))
	{
		std::cout << "ERROR in Menu.cpp. Move SOUND not found!" << std::endl;
	}
	MenuMove.setBuffer(bufferMove);
	MenuMove.setVolume(50);
}

//Constructors and Destructors:
Menu::Menu()
{
	this->initWindow();
	this->initText();
	this->initMenuSelect();
	this->initMenuMove();
	//Set parameters to texts:
	menuText[0].setFont(menuFont);	
	menuText[0].setFillColor(sf::Color(255, 215, 0));
	menuText[0].setCharacterSize(30);
	menuText[0].setPosition(sf::Vector2f(mWindow->getSize().x / 2.5f, mWindow->getSize().y / 2.f));
	menuText[0].setString("Easy");

	menuText[1].setFont(menuFont);
	menuText[1].setCharacterSize(30);
	menuText[1].setFillColor(sf::Color::White);
	menuText[1].setPosition(sf::Vector2f(mWindow->getSize().x / 3.1f, mWindow->getSize().y / 1.65f));
	menuText[1].setString("Normal");

	menuText[2].setFont(menuFont);
	menuText[2].setCharacterSize(30);
	menuText[2].setFillColor(sf::Color::White);
	menuText[2].setPosition(sf::Vector2f(mWindow->getSize().x / 4.f, mWindow->getSize().y / 1.4f));
	menuText[2].setString("Professional");

	//Set title:
	title.setFont(menuFont);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color(255, 215, 0));
	title.setOutlineThickness(1.f);
	title.setCharacterSize(50);
	title.setPosition(sf::Vector2f(mWindow->getSize().x / 10.f, mWindow->getSize().y / 4.f));
	title.setString("DARK BOMBS");

	selItemIndex = 0;
}

Menu::~Menu()
{
	delete this->mWindow;
}

void Menu::run()
{
	while (mWindow->isOpen())
	{
		sf::Event mEvent;
		while (mWindow->pollEvent(mEvent))
		{
			if (mEvent.type == sf::Event::Closed)
				mWindow->close();
			if (mEvent.type == sf::Event::KeyPressed)
			{
				if (mEvent.key.code == sf::Keyboard::W || mEvent.key.code == sf::Keyboard::Up)
				{
					MoveUp();
				}
				else if (mEvent.key.code == sf::Keyboard::S || mEvent.key.code == sf::Keyboard::Down)
				{
					MoveDown();
				}
				else if (mEvent.key.code == sf::Keyboard::Enter || mEvent.key.code == sf::Keyboard::Space)
				{
					if (GetPressedInt() == 0)
					{
						int gridH = Easy;
						int gridW = Easy;
						int maxMines = EasyM;
						int posCoef = EasyS;
						MenuSelect.play();
						sf::sleep(sf::milliseconds(1400));
						Game mineSweeper(gridH, gridW, maxMines, posCoef);
						mineSweeper.run();
					}
					if (GetPressedInt() == 1)
					{
						int gridH = Normal;
						int gridW = Normal;
						int maxMines = NormalM;
						int posCoef = NormalS;
						MenuSelect.play();
						sf::sleep(sf::milliseconds(1400));
						Game mineSweeper(gridH, gridW, maxMines, posCoef);
						mineSweeper.run();
					}
					if (GetPressedInt() == 2)
					{
						gridH = ProH;
						gridW = ProW;
						maxMines = ProM;
						posCoef = ProS;
						MenuSelect.play();
						sf::sleep(sf::milliseconds(1400));
						Game mineSweeper(gridH, gridW, maxMines, posCoef);
						mineSweeper.run();
					}
				}
			}
		}
		mWindow->clear();
		render(mWindow);
		mWindow->display();
	}
}

//Function:
void Menu::render(sf::RenderTarget* whereTo)
{
	whereTo->draw(title);
	for (int row = 0; row < NUMBER_OF_ITEMS; ++row)
	{
		whereTo->draw(menuText[row]);
	}
	
}

void Menu::MoveUp()
{
	MenuMove.play();
	if (selItemIndex - 1 >= 0)
	{
		menuText[selItemIndex].setFillColor(sf::Color::White);
		selItemIndex--;
		menuText[selItemIndex].setFillColor(sf::Color(255, 215, 0));
	}
}

void Menu::MoveDown()
{
	MenuMove.play();
	if (selItemIndex + 1 < NUMBER_OF_ITEMS)
	{
		menuText[selItemIndex].setFillColor(sf::Color::White);
		selItemIndex++;
		menuText[selItemIndex].setFillColor(sf::Color(255, 215, 0));
	}
}

int Menu::GetPressedInt()
{
	return selItemIndex;
}