#pragma once
#include "NeuronGene.h"

class NeuronGene;

class LinkGene
{
public:
	LinkGene(int, double, bool);
	LinkGene(int, double, bool, NeuronGene&, NeuronGene&);
	LinkGene();
	~LinkGene();
	
	double GetWeigth();
	bool GetIsEnabled();
	static LinkGene CrossOver_Link(LinkGene& a, LinkGene& b, NeuronGene& _input, NeuronGene& _output);
	void SetWeigth(double);
	void SetIsEnabled(bool);
	int GetId();
	NeuronGene* GetInputNeuron();
	NeuronGene* GetOutputNeuron();
	void SetInputNeuron(NeuronGene);
	void SetOutputNeuron(NeuronGene);

	bool operator==(LinkGene& other) {
		return innovationNumber == other.GetId();
	}
	bool is_enabled;

	NeuronGene* i_neuron;
	NeuronGene* o_neuron;
	double weight;
	int innovationNumber;
protected:
	std::vector<LinkGene*> GetLink();
};


