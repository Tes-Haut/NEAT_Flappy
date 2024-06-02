#include "Flappy.h"

Flappy::Flappy()
{
	m_size = { 20.f,20.f };
	m_pos = { 20.f,50.f + static_cast<float>(Tools::iRand(50, 500)) };
	m_velocity = { 0.f,0.f };

	m_flappy.setSize(m_size);
	m_flappy.setFillColor(sf::Color::Red);
	m_flappy.setPosition(m_pos);
	m_flappy.setOutlineThickness(-1.f);
	m_flappy.setOutlineColor(sf::Color::White);
	is_dead = false;
	raycastForward = false;
	raycastDown = false;
	raycastUp = false;
	fitness = 0.f;
	timerJump = 0.f;
}

Flappy::~Flappy()
{
}

void Flappy::Draw(sf::RenderWindow& _window)
{
	if (!is_dead)
		_window.draw(m_flappy);
}

void Flappy::Update(std::vector<sf::Vector2f> _allPipes)
{
	if (is_dead) return;

	raycastForward = false;
	raycastDown = false;
	raycastUp = false;

	m_velocity.y += 1200.f * Tools::GetTimeDelta();

	m_pos.y += m_velocity.y * Tools::GetTimeDelta();

	if (m_pos.y > 620 || m_pos.y <= 0) {
		is_dead = true;
		fitness -= 10000.f;
	}

	m_flappy.setPosition(m_pos);

	for (auto o : _allPipes) {
		if (Tools::Rectangle_Collision(m_pos, o, m_size, SIZE_PIPE)) {
			is_dead = true;
			fitness -= 20.f;
		}
		if (Tools::Rectangle_Collision(m_pos, o, { 300.f, m_size.y }, SIZE_PIPE)) 
			raycastForward = true;
		if (Tools::Rectangle_Collision(m_pos, o, { m_size.x, -20.f }, SIZE_PIPE))
			raycastUp = true;
		if (Tools::Rectangle_Collision(m_pos, o, { m_size.x, m_size.y  + 20.f }, SIZE_PIPE))
			raycastDown = true;

		if (m_pos.x > o.x + 52.f)
			fitness += 100.f;
	}
	fitness += Tools::GetTimeDelta();
	timerJump += Tools::GetTimeDelta();

	
}

sf::Vector2f Flappy::GetPosition()
{
	return m_pos;
}

void Flappy::Jump()
{
	if (timerJump > 0.2f) {
		m_velocity.y = -450.f;
		timerJump = 0.f;
	}
}

void Flappy::Reset()
{
	m_pos = { 20.f,100.f + static_cast<float>(Tools::iRand(50, 500)) };
	m_velocity = { 0.f,0.f };
	is_dead = false;
	fitness = 0.f;
	timerJump = 0.f;
}
