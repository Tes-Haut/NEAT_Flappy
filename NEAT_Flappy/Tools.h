#pragma once
#include <functional>
#include <random>
#include <vector>
#include <map>
#include <cassert>
#include <optional>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include "SFML/Graphics.hpp"

#define NUM_INPUTS 9
#define NUM_OUTPUTS 2

#define RESSORUCES "..\\ressources\\"
#define SIZE_PIPE { 26.f * 2.f,160.f * 2.f + 100.f}

namespace Tools {
	template<typename T> T random(T a, T b);
	bool Rectangle_Collision(sf::Vector2f _pos1, sf::Vector2f _pos2, sf::Vector2f _size1, sf::Vector2f _size2);
	void restartClock();
	float GetTimeDelta();
	int iRand(int _min, int _max);
	double RandomDouble(double a, double b);
	float RandomFloat0To1();
}