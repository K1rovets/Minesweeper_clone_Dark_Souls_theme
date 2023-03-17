#include "Button.h"

//Constructors and Destructors:
Button::Button(float x, float y, int width, int height, sf::Texture* bTexture)
{
	//initBTexture();	

	this->width = width;
	this->height = height;
	
	bSprite = new sf::Sprite;
	bSprite->setTexture(*bTexture);

	this->bSprite->setPosition(x , y);
	this->bSprite->setScale(0.25f, 0.25f);

	BState = BDefault;

	this->bSprite->setTextureRect(sf::IntRect(0, 0, this->width, this->height));
}

Button::~Button()
{
	delete this->bSprite;
}

//Getters
const int Button::isClicked()
{
	return BState;
}

//Functions:
void Button::update(sf::Vector2f mousePos)
{	
	if (this->bSprite->getGlobalBounds().contains(mousePos))
	{		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			BState != BClicked ? BState = BClicked : BState = BDefault;
		}
	}

	switch (BState)
	{
	case BDefault:
		this->bSprite->setTextureRect(sf::IntRect(this->width, 0, this->width, this->height));
		break;
	case BClicked:
		this->bSprite->setTextureRect(sf::IntRect(0, 0, this->width, this->height));
		break;
	default:
		this->bSprite->setTextureRect(sf::IntRect(this->width, 0, this->width, this->height));
		break;
	}
}

//Functions:
void Button::render(sf::RenderTarget* whereTo)
{
	whereTo->draw(*bSprite);
}