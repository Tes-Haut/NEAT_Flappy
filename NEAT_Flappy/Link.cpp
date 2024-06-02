#include "Link.h"

LinkGene::LinkGene(int _innovationNumber, double _weigth, bool _is_enabled)
{
	innovationNumber = _innovationNumber;
	weight = _weigth;
	is_enabled = _is_enabled;
}

LinkGene::LinkGene(int _innovationNumber, double _weigth, bool _is_enabled, NeuronGene& _input, NeuronGene& _output)
{
	innovationNumber = _innovationNumber;
	weight = _weigth;
	is_enabled = _is_enabled;
	i_neuron = &_input;
	o_neuron = &_output;
	_input.AddLink(this);
	_output.AddLink(this);
}

LinkGene::LinkGene()
{
	innovationNumber = 0;
	weight = 0;
	is_enabled = true;
}

LinkGene::~LinkGene()
{
}

double LinkGene::GetWeigth()
{
	return weight;
}

bool LinkGene::GetIsEnabled()
{
	return is_enabled;
}

LinkGene LinkGene::CrossOver_Link(LinkGene& a, LinkGene& b, NeuronGene& _input, NeuronGene& _output) {
	return { a.innovationNumber, Tools::random(a.weight, b.weight), Tools::random(a.is_enabled, b.is_enabled), _input, _output };
}

void LinkGene::SetWeigth(double _weigth)
{
	weight = _weigth;
}

void LinkGene::SetIsEnabled(bool _is_enabled)
{
	is_enabled = _is_enabled;
}

int LinkGene::GetId() { return innovationNumber; }

NeuronGene* LinkGene::GetInputNeuron()
{
	return i_neuron;
}

NeuronGene* LinkGene::GetOutputNeuron()
{
	return o_neuron;
}

void LinkGene::SetInputNeuron(NeuronGene _neuron)
{
	i_neuron = &_neuron;
}

void LinkGene::SetOutputNeuron(NeuronGene _neuron)
{
	o_neuron = &_neuron;
}

std::vector<LinkGene*> LinkGene::GetLink()
{
	return std::vector<LinkGene*>();
}

