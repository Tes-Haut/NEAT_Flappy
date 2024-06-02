#pragma once
#include "Tools.h"

class Map
{
public:
	Map();
	~Map();

	void draw(sf::RenderWindow& _window);
private:
	sf::Sprite m_spriteBackGround;
	sf::Sprite m_spritePipes;
	sf::Sprite m_spriteGround;

	sf::Texture m_textureFlappy;

	sf::IntRect m_rectBackGround;//3,0,143,255
	sf::IntRect m_rectPipes;//152,3         177,162 | 180,3      205,162
	sf::IntRect m_rectGround;//215,10,      382,65
	//Flappy 17/12
protected:

};

