#include "Link.h"

double sigmoid(const double x) {
	return 1.0 / (1.0 + std::exp(-x));
}

double tanh(const double x) {
	return std::tanh(x);
}

double relu(const double x) {
	return (x > 0.0) ? x : 0.0;
}


NeuronGene NeuronGene::CrossOver_Gene(const NeuronGene& a, const NeuronGene& b)
{
	assert(a.n_id == b.n_id);

	return { a.n_id, Tools::random(a.bias, b.bias), Tools::random(a.activationFunction, b.activationFunction), {1.f,1.f} };
}

int NeuronGene::GetId() { return n_id; }

double NeuronGene::GetBias() { return bias; }

ActivationFunction NeuronGene::GetActivationFunction() { return activationFunction; }

std::vector<LinkGene*>& NeuronGene::GetLink()
{
	return linksNeurons;
}

void NeuronGene::Activate()
{
	value = bias;
	this;
	for (auto link : linksNeurons) {
		if (link->o_neuron->n_id != n_id) continue;
		if (!link->i_neuron->is_calculated)
			link->i_neuron->Activate();
		value = link->i_neuron->value * link->weight;
	}

	if (activationFunction != nullptr) 
		value += activationFunction(value);

	is_calculated = true;
}

void NeuronGene::AddLink(LinkGene* _link)
{
	linksNeurons.push_back(_link);
}

NeuronGene::NeuronGene(int _id, double _bias, ActivationFunction _function, sf::Vector2f _pos)
{
	n_id = _id;
	bias = _bias;
	activationFunction = _function;
	pos = _pos;
	is_enabled = true;
	value = 0;
	is_calculated = false;
}

NeuronGene::NeuronGene()
{

}

NeuronGene::~NeuronGene()
{
}
