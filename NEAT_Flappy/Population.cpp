#include "Population.h"

Population::Population()
{
	for (int i = 0; i < 500; i++)
		individuals.emplace_back(new Individual());

	for (auto& i : individuals)
		species[i->genome.GetCompatibilityDistance()].push_back(i);

	nbrGen = 1;
}

Population::~Population()
{

}

void Population::update()
{
	pipe.Update();

	for (auto& o : individuals) {
		if (o->GetIsDead()) continue;
		o->genome.ForwardPropagation(pipe.GetPipes()[0].x, pipe.GetPipes()[1].x);
		o->genome.flappy->Update(pipe.GetPipes());
	}

	for (auto& o : individuals)
		if (!o->GetIsDead()) return;

	pipe = Pipe();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::exponential_distribution<> distribution(0.1);

	auto chooseRandomIndividual = [&]() {
		double randValue = distribution(gen);

		std::size_t listSize = individuals.size();

		std::size_t index = static_cast<std::size_t>(randValue * listSize);

		auto it = individuals.begin();

		std::advance(it, std::min(index, listSize - 1));

		return it;
		};

	auto chooseRandomIndividualInSpecies = [&](std::list<Individual*>& _list) {
		double randValue = distribution(gen);

		std::size_t listSize = _list.size();

		std::size_t index = static_cast<std::size_t>(randValue * listSize);

		auto it = _list.begin();

		std::advance(it, std::min(index, listSize - 1));

		return it;
		};

	individuals.sort([](const auto& a, const auto& b) { return a->GetFitness() > b->GetFitness(); });
	std::cout << "Best Fitness : " << individuals.front()->GetFitness() << std::endl;

	for (auto& o : species) {
		o.second.sort([](const auto& a, const auto& b) { return a->GetFitness() < b->GetFitness(); });
	}
	for (int i = 0; i < 500; i++) {
		auto it = chooseRandomIndividual();
		int distance = (*it)->genome.totalInnovationNumber;
		std::list<Individual*>::iterator it2;

		if (species[distance].size() < 2) {
			it2 = chooseRandomIndividual();
			while (*it == *it2)
				it2 = chooseRandomIndividual();
		}
		else {
			it2 = chooseRandomIndividualInSpecies(species[distance]);
			while (*it == *it2)
				it2 = chooseRandomIndividualInSpecies(species[distance]);
		}
		Genome tmpGenome(true);
		tmpGenome.CrossOver(*(*it), *(*it2));
		if (Tools::random(true, false))
			tmpGenome.Mutate();
		individuals.emplace_back(new Individual(std::move(tmpGenome)));
	}

	auto suprr = individuals.begin();
	int a = 0;

	for (int i = 0; i < 500; i++) {
		delete* suprr;
		suprr = individuals.erase(suprr);
	}

	species.clear();

	for (auto& i : individuals) {
		i->flappy.is_dead = false;
		species[i->genome.totalInnovationNumber].push_back(i);
	}

	std::cout << "New Pop " << ++nbrGen << std::endl;
}

void Population::draw(sf::RenderWindow& _window)
{
	pipe.Draw(_window);

	for (auto& o : individuals)
		o->flappy.Draw(_window);
}

void Population::newPopulation()
{

}
