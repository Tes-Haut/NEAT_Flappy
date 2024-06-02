#include "Individual.h"

Genome::Genome()
{
	totalInnovationNumber = -NUM_INPUTS - NUM_OUTPUTS;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-0.5, 0.5);

	sf::Vector2f pos{ 50.f,10.f };

	for (int i = 0; i < NUM_INPUTS; i++) {
		AddInput(NeuronGene(totalInnovationNumber++, 0.0, nullptr, pos));
		pos.y += 30.f;
	}

	pos = { 350.f,0.f - 15.f + (NUM_INPUTS / NUM_OUTPUTS) * 30.f };

	for (int i = 0; i < NUM_OUTPUTS; i++) {
		AddOutput(NeuronGene(totalInnovationNumber++, 0.0, nullptr, pos));
		pos.y += 30.f;
	}

	for (auto& input : inputs)
		for (auto& output : outputs)
			links.emplace_back(totalInnovationNumber++, dis(gen), true, input, output);
}

Genome::Genome(bool)
{
	totalInnovationNumber = -NUM_INPUTS - NUM_OUTPUTS;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-0.5, 0.5);

	sf::Vector2f pos{ 50.f,10.f };

	for (int i = 0; i < NUM_INPUTS; i++) {
		AddInput(NeuronGene(totalInnovationNumber++, 0.0, nullptr, pos));
		pos.y += 30.f;
	}

	pos = { 350.f,0.f - 15.f + (NUM_INPUTS / NUM_OUTPUTS) * 30.f };

	for (int i = 0; i < NUM_OUTPUTS; i++) {
		AddOutput(NeuronGene(totalInnovationNumber++, 0.0, nullptr, pos));
		pos.y += 30.f;
	}
}

Genome::Genome(const Genome& other) {
	this->totalInnovationNumber = other.totalInnovationNumber;

	for (const auto& input : other.inputs)
		this->inputs.push_back(NeuronGene(input.n_id, input.bias, input.activationFunction, input.pos));

	for (const auto& output : other.outputs)
		this->outputs.push_back(NeuronGene(output.n_id, output.bias, output.activationFunction, output.pos));

	for (const auto& neuron : other.neurons)
		this->neurons.push_back(NeuronGene(neuron.n_id, neuron.bias, neuron.activationFunction, neuron.pos));

	for (const auto& link : other.links) {
		bool test = true;
		auto inputNeuron = std::find_if(this->inputs.begin(), this->inputs.end(), [id = link.i_neuron->n_id](const auto& n) { return n.n_id == id; });
		auto outputNeuron = std::find_if(this->outputs.begin(), this->outputs.end(), [id = link.o_neuron->n_id](const auto& n) { return n.n_id == id; });

		if (inputNeuron == this->inputs.end()) {
			inputNeuron = std::find_if(this->neurons.begin(), this->neurons.end(), [id = link.i_neuron->n_id](const auto& n) { return n.n_id == id; });
			if (inputNeuron == this->neurons.end())
				test = false;
		}

		if (outputNeuron == this->outputs.end()) {
			outputNeuron = std::find_if(this->neurons.begin(), this->neurons.end(), [id = link.o_neuron->n_id](const auto& n) { return n.n_id == id; });
			if (outputNeuron == this->neurons.end())
				test = false;
		}

		if (test)
			this->links.emplace_back(link.innovationNumber, link.weight, link.is_enabled, *inputNeuron, *outputNeuron);
	}
}

Genome::~Genome()
{
}

void Genome::CrossOver(Individual _a, Individual _b) {
	if (_a.genome.neurons.size() >= _b.genome.neurons.size()) {
		bool fitter = _a.GetFitness() >= _b.GetFitness();
		for (auto o : _a.GetGenome().GetNeurons()) {
			int aId = o.GetId();
			auto Neuro = _b.GetGenome().FoundOptionalNeuron(aId);
			if (Neuro)
				neurons.emplace_back(std::move(NeuronGene::CrossOver_Gene(o, *Neuro)));
			else if (fitter)
				neurons.emplace_back(o.n_id, o.bias, o.activationFunction, o.pos);
		}
	}
	else {
		bool fitter = _a.GetFitness() <= _b.GetFitness();
		for (auto o : _b.GetGenome().GetNeurons()) {
			int aId = o.GetId();
			auto Neuro = _a.GetGenome().FoundOptionalNeuron(aId);
			if (Neuro)
				neurons.emplace_back(std::move(NeuronGene::CrossOver_Gene(o, *Neuro)));
			else if (fitter)
				neurons.emplace_back(o.n_id, o.bias, o.activationFunction, o.pos);
		}
	}
	if (_a.genome.links.size() >= _b.genome.links.size()) {
		bool fitter = _a.GetFitness() >= _b.GetFitness();
		for (auto o : _a.genome.links) {
			int aId = o.GetId();
			auto Link = _b.genome.FoundOptionalLink(aId);
			if (Link)
				links.emplace_back(std::move(
					LinkGene::CrossOver_Link(o, *Link, FoundInput(o.i_neuron->n_id), FoundOutput(o.o_neuron->n_id))
				));
			else if (fitter)
				links.emplace_back(o.innovationNumber, o.weight, o.is_enabled, FoundInput(o.i_neuron->n_id), FoundOutput(o.o_neuron->n_id));
		}
	}
	else {
		bool fitter = _a.GetFitness() <= _b.GetFitness();
		for (auto o : _b.genome.links) {
			int aId = o.GetId();
			auto Link = _a.genome.FoundOptionalLink(aId);
			if (Link)
				links.emplace_back(std::move(
					LinkGene::CrossOver_Link(o, *Link, FoundInput(o.i_neuron->n_id), FoundOutput(o.o_neuron->n_id))
				));
			else if (fitter)
				links.emplace_back(o.innovationNumber, o.weight, o.is_enabled, FoundInput(o.i_neuron->n_id), FoundOutput(o.o_neuron->n_id));
		}
	}
	totalInnovationNumber = neurons.size() + links.size();
}

std::list<LinkGene> Genome::GetLinks() { return links; }

std::list<NeuronGene> Genome::GetNeurons() { return neurons; }

std::list<NeuronGene> Genome::GetInputs() { return inputs; }

std::list<NeuronGene> Genome::GetOutputs() { return outputs; }

void Genome::AddNeuron(NeuronGene _neuron)
{
	neurons.push_back(_neuron);
}

void Genome::AddLink(LinkGene _link)
{
	links.push_back(_link);
}

void Genome::AddInput(NeuronGene _inputNeuron)
{
	inputs.push_back(_inputNeuron);
}

void Genome::AddOutput(NeuronGene _outputNeuron)
{
	outputs.push_back(_outputNeuron);
}

std::optional<LinkGene> Genome::FoundOptionalLink(int _id)
{
	for (auto i : links) {
		if (i.GetId() == _id) {
			return i;
		}
	}
	return std::nullopt;
}

std::optional<NeuronGene> Genome::FoundOptionalNeuron(int _id)
{
	for (auto i : neurons) {
		if (i.GetId() == _id) {
			return i;
		}
	}
	return std::nullopt;
}

NeuronGene& Genome::FoundInput(int _id)
{
	for (auto& i : inputs) {
		if (i.GetId() == _id) {
			return i;
		}
	}
	for (auto& i : neurons) {
		if (i.GetId() == _id) {
			return i;
		}
	}
}

NeuronGene& Genome::FoundOutput(int _id)
{
	for (auto& i : outputs) {
		if (i.GetId() == _id) {
			return i;
		}
	}
	for (auto& i : neurons) {
		if (i.GetId() == _id) {
			return i;
		}
	}
}

NeuronGene& Genome::FoundNeuron(int _id)
{
	for (auto& i : neurons) {
		if (i.GetId() == _id) {
			return i;
		}
	}
}

Genome Genome::Mutate()
{
	float random = Tools::RandomFloat0To1();
	if (random <= 0.4) {
		return MutationPerturbWeights();
	}
	else if (random <= 0.8) {
		return MutationPerturbBias();
	}
	else if (random <= 0.85) {
		return MutationAddLink();
	}
	else if (random <= 0.90) {
		return MutationRemoveLink();
	}
	else if (random <= 0.95) {
		return MutationAddNeuron();
	}
	else if (random <= 1) {
		return MutationRemoveNeuron();
	}
}

bool Genome::IsDuplicateLink(const int i_id, const int o_id)
{
	for (auto& checkLink : links) {
		if (i_id == checkLink.i_neuron->n_id && o_id == checkLink.o_neuron->n_id) {
			checkLink.is_enabled = true;
			checkLink.i_neuron->is_enabled = true;
			checkLink.o_neuron->is_enabled = true;
			return true;
		}
	}
	return false;
}

template <typename Container>
void DisableLinkById(Container& neurons, int neuronId, int linkId) {
	for (auto& neuron : neurons) {
		if (neuron.GetId() == neuronId) {
			auto& links = neuron.GetLink();
			bool good = false;
			auto it = std::find_if(links.begin(), links.end(),
				[linkId, &good](const auto& link) {
					if (link->GetId() == linkId) {
						good = true;
						return good;
					}
					return false;
				});
			if (good) {
				(*it)->is_enabled = false;
			}
			break;
		}
	}
}

template<typename Container, typename Iterator>
bool FoundEnabled(Container& neurons, Iterator& _it) {
	int previousId = _it->GetId();
	int loop = 0;
	while (!_it->is_enabled) {
		++_it;
		if (_it == neurons.end())
			_it = std::prev(neurons.end(), neurons.size());
		if (_it->GetId() == previousId)
			loop++;
		if (loop > 0)
			return false;
	}
	return true;
}

Genome Genome::MutationAddLink()
{
	int type = Tools::iRand(0, 2);
	int i, o;
	std::list<NeuronGene>::iterator input;
	std::list<NeuronGene>::iterator output;
	bool noNeurons = true;

	if (type == 1 && !noNeurons) {
		i = Tools::iRand(0, neurons.size());
		input = std::next(neurons.begin(), i);
		FoundEnabled(neurons, input);
	}
	else {
		i = Tools::iRand(0, inputs.size());
		input = std::next(inputs.begin(), i);
	}

	type = Tools::iRand(0, 2);

	if (type == 1 && !noNeurons) {
		o = Tools::iRand(0, neurons.size());
		output = std::next(neurons.begin(), o);
		FoundEnabled(neurons, output);
	}
	else {
		o = Tools::iRand(0, outputs.size());
		output = std::next(outputs.begin(), o);
	}

	if (!IsDuplicateLink(input->n_id, output->n_id))
		links.emplace_back(totalInnovationNumber++, 0.1, true, *input, *output);

	return *this;
}

Genome Genome::MutationRemoveLink()
{
	if (links.empty()) return *this;
	int i = Tools::iRand(0, links.size());
	std::list<LinkGene>::iterator link;
	if (i != links.size())
		link = std::next(links.begin(), i);
	else
		link = std::prev(links.end());

	FoundEnabled(links, link);

	int i_id = link->i_neuron->GetId();
	int o_id = link->o_neuron->GetId();

	int link_id = link->GetId();

	if (i_id < 0)
		DisableLinkById(inputs, i_id, link_id);
	else
		DisableLinkById(neurons, i_id, link_id);
	if (o_id < 0)
		DisableLinkById(outputs, o_id, link_id);
	else
		DisableLinkById(neurons, o_id, link_id);

	bool desactiveNeuron = true;
	for (auto tmp : link->i_neuron->GetLink()) {
		if (tmp->is_enabled)
			desactiveNeuron = false;
	}
	if (desactiveNeuron)
		link->i_neuron->is_enabled = false;

	desactiveNeuron = true;
	for (auto tmp : link->o_neuron->GetLink()) {
		if (tmp->is_enabled)
			desactiveNeuron = false;
	}
	if (desactiveNeuron)
		link->o_neuron->is_enabled = false;

	return *this;
}

Genome Genome::MutationAddNeuron()
{
	if (links.size() == 0) return *this;
	std::list<LinkGene >::iterator it = std::next(links.begin(), Tools::iRand(0, links.size()));
	if (!FoundEnabled(links, it)) return *this;

	neurons.emplace_back(totalInnovationNumber++, 0.0, sigmoid, sf::Vector2f{ 200.f, 25.f + neurons.size() * 30.f });

	links.emplace_back(totalInnovationNumber++, 0.1, true, *it->GetInputNeuron(), neurons.back());
	links.emplace_back(totalInnovationNumber++, 0.1, true, neurons.back(), *it->GetOutputNeuron());

	it->is_enabled = false;

	return *this;
}

Genome Genome::MutationRemoveNeuron()
{
	if (neurons.empty()) return *this;
	std::list<NeuronGene >::iterator it = std::next(neurons.begin(), Tools::iRand(0, neurons.size()));

	for (auto o : it->GetLink())
		DisableLinkById(neurons, it->GetId(), o->GetId());

	it->is_enabled = false;

	return *this;
}

Genome Genome::MutationPerturbWeights() {
	for (auto& link : links)
		link.weight += Tools::RandomDouble(-0.1, 0.1);

	return *this;
}

Genome Genome::MutationPerturbBias() {
	for (auto& neuron : neurons)
		neuron.bias += Tools::RandomDouble(-0.1, 0.1);

	return *this;
}

int Genome::GetCompatibilityDistance()
{
	return neurons.size() + links.size();
}

void Genome::ForwardPropagation(float pipe1, float pipe2)
{
	Flappy& tmpFlappy = *flappy;

	std::list<NeuronGene>::iterator it_input = inputs.begin();
	double inputValues[NUM_INPUTS] = { tmpFlappy.m_pos.y, tmpFlappy.m_pos.y + 21.f, tmpFlappy.m_velocity.y, tmpFlappy.m_size.x, tmpFlappy.m_size.y, pipe1 + 420.f, pipe2 - 20.f, tmpFlappy.timerJump, tmpFlappy.raycastForward };
	for (auto& inputValue : inputValues) {
		it_input->value = inputValue;
		it_input->is_calculated = true;
		it_input++;
	}

	std::list<NeuronGene>::iterator it = outputs.begin();
	for (auto& output : outputs)
		output.Activate();
	for (auto& output : outputs) {
		if (it->value > output.value) {
			it = std::find_if(outputs.begin(), outputs.end(),
				[output](const NeuronGene _output)
				{
					return output == _output;
				}
			);
		}
	}
	if (it->n_id == outputs.begin()->n_id)
		flappy->Jump();

	for (auto& input : inputs)
		input.is_calculated = false;
	for (auto& neuron : neurons)
		neuron.is_calculated = false;
	for (auto& output : outputs)
		output.is_calculated = false;
}

void Genome::draw(sf::RenderWindow& _window, float _i, sf::Color _color)
{
	sf::CircleShape circle{ 10.f,64 };
	circle.setFillColor(sf::Color::Green);
	for (const auto& inputs : inputs)
	{
		circle.setPosition(inputs.pos + sf::Vector2f(200.f * _i, 250.f * _i));
		_window.draw(circle);
	}

	circle.setFillColor(sf::Color::Blue);

	for (const auto& output : outputs)
	{
		circle.setPosition(output.pos + sf::Vector2f(200.f * _i, 250.f * _i));
		_window.draw(circle);
	}

	circle.setFillColor(_color);

	for (const auto& neuron : GetNeurons())
	{
		if (!neuron.is_enabled) continue;
		circle.setPosition(neuron.pos + sf::Vector2f(200.f * _i, 250.f * _i));
		_window.draw(circle);
	}

	auto tmp = GetLinks();

	for (auto& link : tmp)
	{
		if (!link.is_enabled) continue;
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(link.GetInputNeuron()->pos + sf::Vector2f{10.f, 10.f} + sf::Vector2f(200.f * _i,250.f * _i))),
			sf::Vertex(sf::Vector2f(link.GetOutputNeuron()->pos + sf::Vector2f{10.f, 10.f} + sf::Vector2f(200.f * _i,250.f * _i)))
		};
		line[0].color = sf::Color::Green;
		line[1].color = sf::Color::Blue;
		_window.draw(line, 2, sf::Lines);
	}
}
