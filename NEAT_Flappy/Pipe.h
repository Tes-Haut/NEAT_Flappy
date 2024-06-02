#pragma once
#include "Tools.h"

class Pipe
{
public:
	Pipe();
	~Pipe();

	std::vector<sf::Vector2f> GetPipes();
	void Draw(sf::RenderWindow& _window);

	void AddPipe(sf::Vector2f _pos);
	void RemovePipe(sf::Vector2f _pos);
	void Update();
private:
	sf::RectangleShape m_pipe;
	sf::Vector2f m_sizePipe;

	std::vector<sf::Vector2f> v_posPipes;
protected:

};

