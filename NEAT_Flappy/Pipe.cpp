#include "Pipe.h"

Pipe::Pipe()
{
	m_sizePipe = { 52.f, 420.f };

	m_pipe.setFillColor(sf::Color::Green);
	m_pipe.setOutlineThickness(-1);
	m_pipe.setOutlineColor(sf::Color::Red);
	m_pipe.setSize(m_sizePipe);

	v_posPipes.push_back(sf::Vector2f(600.f, -110.f));
	v_posPipes.push_back(sf::Vector2f(600.f, 530.f));
}

Pipe::~Pipe()
{
}

std::vector<sf::Vector2f> Pipe::GetPipes()
{
	return v_posPipes;
}

void Pipe::Update()
{
	for (auto& o : v_posPipes) {
		o.x -= 300.f * Tools::GetTimeDelta();
		if (o.x < -m_sizePipe.x) {
			RemovePipe(v_posPipes[0]);
			RemovePipe(v_posPipes[0]);
			float tmp = static_cast<float>(Tools::iRand(-200, 100));
			v_posPipes.push_back(sf::Vector2f(600.f, -110.f + tmp));
			v_posPipes.push_back(sf::Vector2f(600.f, 480.f + tmp));
		}
	}
}

void Pipe::Draw(sf::RenderWindow& _window)
{
	for (auto o : v_posPipes) {
		m_pipe.setPosition(o);
		_window.draw(m_pipe);
	}
}

void Pipe::AddPipe(sf::Vector2f _pos)
{
	v_posPipes.push_back(_pos);
}

void Pipe::RemovePipe(sf::Vector2f _pos)
{
	v_posPipes.erase(std::remove_if(v_posPipes.begin(), v_posPipes.end(),
		[_pos](const sf::Vector2f& pipePos) {
			return pipePos == _pos;
		}), v_posPipes.end());

}