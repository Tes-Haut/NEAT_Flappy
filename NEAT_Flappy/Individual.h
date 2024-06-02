#pragma once
#include "Genome.h"


class Individual
{
public:
	Individual();
	Individual(bool);
	Individual(const Genome& mutatedGenome);

	~Individual() {}

	const float GetFitness();
	const bool GetIsDead();
	Genome& GetGenome();

	static Individual CrossOver(Individual& a, Individual& b);
	static Genome* CrossOverGenome(Individual& _a, Individual& _b);

	void AddHiddenLayer(Individual& _a, Individual& _b);
	static void AddHiddenLayerGenome(Individual& _a, Individual& _b, Genome& _genome);

	void AddLinks(Individual& _a, Individual& _b);
	static void AddLinksGenome(Individual& _a, Individual& _b, Genome& _genome);
	Genome genome;
	Flappy flappy;
protected:
};

