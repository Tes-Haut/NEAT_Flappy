#pragma once
#include "Link.h"
#include "Flappy.h"

class Individual;

class Genome
{
public:
	Genome();
	Genome(bool);
	Genome(const Genome& other);
	~Genome();

	void CrossOver(Individual _a, Individual _b);

	std::list<LinkGene> GetLinks();
	std::list<NeuronGene> GetNeurons();
	std::list<NeuronGene> GetInputs();
	std::list<NeuronGene> GetOutputs();

	void AddNeuron(NeuronGene);
	void AddLink(LinkGene);
	void AddInput(NeuronGene);
	void AddOutput(NeuronGene);

	std::optional<LinkGene> FoundOptionalLink(int);
	std::optional<NeuronGene> FoundOptionalNeuron(int);

	NeuronGene& FoundInput(int _id);
	NeuronGene& FoundOutput(int _id);

	NeuronGene& FoundNeuron(int _id);

	Genome Mutate();
	Genome MutationAddLink(); 
	Genome MutationRemoveLink();
	Genome MutationAddNeuron();
	Genome MutationRemoveNeuron();
	Genome MutationPerturbWeights();
	Genome MutationPerturbBias();
	int GetCompatibilityDistance();
	void ForwardPropagation(float pipe1, float pipe2);
	std::list<NeuronGene> neurons;
	void draw(sf::RenderWindow& _window, float i, sf::Color _color);

	std::list<LinkGene> links;

	int totalInnovationNumber;
	Flappy* flappy;
	std::list<NeuronGene> inputs;
	std::list<NeuronGene> outputs;

private:
	bool IsDuplicateLink(const int i_id, const int o_id);
};
