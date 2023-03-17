#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum buttonStates { BDefault = 0, BClicked };


class Button
{
	int BState;	

	float width;
	float height;

	sf::Sprite* bSprite;

public:
	//Constructors and Destructors:
	Button(float, float, int, int, sf::Texture*);
	~Button();

	//Getters:
	const int isClicked();

	//Functions:
	void update(sf::Vector2f);
	void render(sf::RenderTarget*);
};