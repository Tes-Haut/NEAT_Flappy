#pragma once
#include "Individual.h"
#include "Pipe.h"

class Population
{
public:
	Population();
	~Population();

	void update();
	void draw(sf::RenderWindow& _window);
	std::list<Individual*> individuals;
	std::map<int, std::list<Individual*>> species;
	Pipe pipe;
	int nbrGen;
	void newPopulation();
	
};

