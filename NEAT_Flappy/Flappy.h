#pragma once
#include "Tools.h"

class Flappy
{
public:
	Flappy();
	~Flappy();

	void Draw(sf::RenderWindow& _window);
	void Update(std::vector<sf::Vector2f> _allPipes);
	sf::Vector2f GetPosition();
	void Jump();
	void Reset();
	sf::RectangleShape m_flappy;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	float fitness;
	bool is_dead;
	float timerJump;
	bool raycastForward;
	bool raycastUp;
	bool raycastDown;
protected:

};

