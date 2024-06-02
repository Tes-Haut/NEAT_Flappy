#include "Map.h"

Map::Map()
{
	m_rectBackGround = { 3,0,143,255 };
	m_rectPipes = { 152,3,26,160 };
	m_rectGround = { 215,10,167,55 };

	m_textureFlappy.loadFromFile(RESSORUCES"Flappy.png");

	m_spriteBackGround.setTexture(m_textureFlappy, true);
	m_spriteBackGround.setTextureRect(m_rectBackGround);

	m_spritePipes.setTexture(m_textureFlappy, true);
	m_spritePipes.setTextureRect(m_rectPipes);

	m_spriteGround.setTexture(m_textureFlappy, true);
	m_spriteGround.setTextureRect(m_rectGround);
}

Map::~Map()
{

}

void Map::draw(sf::RenderWindow& _window)
{
	_window.draw(m_spriteBackGround);
	_window.draw(m_spriteGround);
	_window.draw(m_spritePipes);
}
