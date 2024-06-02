#pragma once
#include "Tools.h"
#include "Link.h"

using ActivationFunction = std::function<double(const double)>;

double sigmoid(const double x);

double tanh(const double x);

double relu(const double x);

class LinkGene;

class NeuronGene
{
public:
	NeuronGene(int, double, ActivationFunction, sf::Vector2f);
	NeuronGene();
	~NeuronGene();

	static NeuronGene CrossOver_Gene(const NeuronGene& a, const NeuronGene& b);
	int GetId();
	double GetBias();
	ActivationFunction GetActivationFunction();
	void AddLink(LinkGene*);
	std::vector<LinkGene*>& GetLink();
	int n_id;
	bool is_enabled, is_calculated;
	sf::Vector2f pos;
	double bias, value;
	ActivationFunction activationFunction;
	void Activate();
	bool operator==(const NeuronGene& other) const {
		return n_id == other.n_id;
	}
private:
	std::vector<LinkGene*> linksNeurons;
};

