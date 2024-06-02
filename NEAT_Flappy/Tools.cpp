#include "Tools.h"

sf::Clock sfclock;
sf::Time sfTime;

namespace Tools {
	template<typename T>
	T random(T a, T b) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);

		return (dis(gen) <= 0.5) ? a : b;
	}

	template<>
	bool random<bool>(bool a, bool b) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);

		return (dis(gen) == 0) ? a : b;
	}

	template<>
	std::function<double(double)> random<std::function<double(double)>>(std::function<double(double)> a, std::function<double(double)> b) {
		return (random<bool>(true, false)) ? a : b;
	}

	template<>
	double random<double>(double a, double b) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.0, 1.0);

		return (dis(gen) <= 0.5) ? a : b;
	}

	bool Rectangle_Collision(sf::Vector2f _pos1, sf::Vector2f _pos2, sf::Vector2f _size1, sf::Vector2f _size2)
	{
		if ((_pos2.x >= _pos1.x + _size1.x)
			|| (_pos2.x + _size2.x <= _pos1.x)
			|| (_pos2.y >= _pos1.y + _size1.y)
			|| (_pos2.y + _size2.y <= _pos1.y))
			return false;
		else
			return true;
	}

	void restartClock()
	{
		sfTime = sfclock.restart();
		if (sfTime.asSeconds() > 0.1)
			sfTime = sf::Time::Zero;
	}

	float GetTimeDelta()
	{
		return sfTime.asSeconds();
	}
	int iRand(int _min, int _max)
	{
		return rand() % (_max - _min) + _min;
	}

	double RandomDouble(double a, double b) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(a, b);
		return dis(gen);
	}
	float RandomFloat0To1() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(0.0f, std::nextafter(1.0f, std::numeric_limits<float>::max()));
		return dis(gen);
	}
}