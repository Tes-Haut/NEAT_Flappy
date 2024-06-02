#include "Individual.h"


Individual::Individual()
{
	genome.flappy = &flappy;
}

Individual::Individual(bool)
{
	genome = Genome(true);
	genome.flappy = &flappy;
}

Individual::Individual(const Genome& mutatedGenome) : genome(mutatedGenome) {
	genome.flappy = &flappy;
}

const float Individual::GetFitness() {
	return flappy.fitness;
}

const bool Individual::GetIsDead()
{
	return flappy.is_dead;
}

Genome& Individual::GetGenome() { return genome; }

Individual Individual::CrossOver(Individual& _a, Individual& _b) {
	Individual tmpIndivudual(true);
	if (_a.genome.neurons.size() > _b.genome.neurons.size())
		tmpIndivudual.AddHiddenLayer(_a, _b);
	else
		tmpIndivudual.AddHiddenLayer(_b, _a);

	if (_a.genome.links.size() > _b.genome.links.size()) {
		tmpIndivudual.AddLinks(_a, _b);
		tmpIndivudual.genome.totalInnovationNumber = _a.genome.totalInnovationNumber;
	}
	else {
		tmpIndivudual.AddLinks(_b, _a);
		tmpIndivudual.genome.totalInnovationNumber = _b.genome.totalInnovationNumber;
	}

	return &tmpIndivudual;
}

Genome* Individual::CrossOverGenome(Individual& _a, Individual& _b) {
	Genome* tmpIndivudual = new Genome(true);
	if (_a.genome.neurons.size() > _b.genome.neurons.size())
		Individual::AddHiddenLayerGenome(_a, _b, *tmpIndivudual);
	else
		Individual::AddHiddenLayerGenome(_b, _a, *tmpIndivudual);

	if (_a.genome.links.size() > _b.genome.links.size()) {
		Individual::AddLinksGenome(_a, _b, *tmpIndivudual);
		tmpIndivudual->totalInnovationNumber = _a.genome.totalInnovationNumber;
	}
	else {
		Individual::AddLinksGenome(_b, _a, *tmpIndivudual);
		tmpIndivudual->totalInnovationNumber = _b.genome.totalInnovationNumber;
	}

	return tmpIndivudual;
}

void Individual::AddHiddenLayer(Individual& _a, Individual& _b) {
	bool fitter = _a.GetFitness() > _b.GetFitness();
	for (auto o : _a.GetGenome().GetNeurons()) {
		int aId = o.GetId();
		auto Neuro = _b.GetGenome().FoundOptionalNeuron(aId);
		if (Neuro)
			genome.neurons.emplace_back(std::move(NeuronGene::CrossOver_Gene(o, *Neuro)));
		else if (fitter)
			genome.neurons.emplace_back(o.n_id, o.bias, o.activationFunction, o.pos);
	}
}

void Individual::AddHiddenLayerGenome(Individual& _a, Individual& _b, Genome& _genome) {
	bool fitter = _a.GetFitness() > _b.GetFitness();
	for (auto o : _a.GetGenome().GetNeurons()) {
		int aId = o.GetId();
		auto Neuro = _b.GetGenome().FoundOptionalNeuron(aId);
		if (Neuro)
			_genome.neurons.emplace_back(std::move(NeuronGene::CrossOver_Gene(o, *Neuro)));
		else if (fitter)
			_genome.neurons.emplace_back(o.n_id, o.bias, o.activationFunction, o.pos);
	}
}

void Individual::AddLinks(Individual& _a, Individual& _b) {
	bool fitter = _a.GetFitness() > _b.GetFitness();
	for (auto o : _a.genome.links) {
		int aId = o.GetId();
		auto Link = _b.genome.FoundOptionalLink(aId);
		if (Link)
			genome.links.emplace_back(std::move(
				LinkGene::CrossOver_Link(o, *Link, genome.FoundInput(o.i_neuron->n_id), genome.FoundOutput(o.o_neuron->n_id))
			));
		else if (fitter)
			genome.links.emplace_back(o.innovationNumber, o.weight, o.is_enabled, genome.FoundInput(o.i_neuron->n_id), genome.FoundOutput(o.o_neuron->n_id));
	}
}

void Individual::AddLinksGenome(Individual& _a, Individual& _b, Genome& _genome) {
	bool fitter = _a.GetFitness() > _b.GetFitness();
	for (auto o : _a.genome.links) {
		int aId = o.GetId();
		auto Link = _b.genome.FoundOptionalLink(aId);
		if (Link)
			_genome.links.emplace_back(std::move(
				LinkGene::CrossOver_Link(o, *Link, _genome.FoundInput(o.i_neuron->n_id), _genome.FoundOutput(o.o_neuron->n_id))
			));
		else if (fitter)
			_genome.links.emplace_back(o.innovationNumber, o.weight, o.is_enabled, _genome.FoundInput(o.i_neuron->n_id), _genome.FoundOutput(o.o_neuron->n_id));
	}
}