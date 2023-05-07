
#include "memetic_algorithm.h"

MemeticAlgorithm::MemeticAlgorithm() {}

MemeticAlgorithm::~MemeticAlgorithm() {}

void MemeticAlgorithm::configure(
        int populationSize,
        float mutationRate,
        double maxTime,
        Population (*initialisation) (PfspInstance& instance, int populationSize),
        Population (*recombination) (PfspInstance& instance, Population population, int populationSize),
        Population (*mutation) (PfspInstance& instance, Population population, float mutationRate),
        Population (*selection) (PfspInstance& instance, Population population, int populationSize),
        State (*modifyState) (State, int, int)
        ) {

    subsidiaryLocalSearch.configure(
            randomPermutation,
            firstImprovement,
            modifyState
    );

    this->populationSize = populationSize;
    this->mutationRate = mutationRate;
    this->maxTime = maxTime;
    this->initialisation = initialisation;
    this->recombination = recombination;
    this->mutation = mutation;
    this->selection = selection;


}

Population MemeticAlgorithm::applySubsidiaryLocalSearch(PfspInstance& instance, Population population) {
    Population newPopulation = vector<State>(population.size());

    for (int i = 0; i < population.size(); i++) {
        newPopulation[i] = subsidiaryLocalSearch.execute(instance, population[i]);
    }

    return newPopulation;
}

bool MemeticAlgorithm::termination(Time start, Time current) {
    auto duration = chrono::duration_cast<chrono::microseconds>(current - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}

State MemeticAlgorithm::execute(PfspInstance& instance) {
    Population population = initialisation(instance, this->populationSize);
    population = applySubsidiaryLocalSearch(instance, population);

    Population runningPopulation; // contain all the individuals currently under investigation
    Population recombinedPopulation; // contain individuals that have been recombined (population size)
    Population mutatedPopulation; // contain individuals that have been mutated (two times population size)

    Time start = Clock::now();

    do {
        recombinedPopulation = recombination(instance, population, this->populationSize);
        recombinedPopulation = applySubsidiaryLocalSearch(instance, recombinedPopulation);

        runningPopulation = population;
        runningPopulation.insert(runningPopulation.end(), recombinedPopulation.begin(), recombinedPopulation.end());

        mutatedPopulation = mutation(instance, runningPopulation, this->mutationRate);
        mutatedPopulation = applySubsidiaryLocalSearch(instance, mutatedPopulation);

        runningPopulation.insert(runningPopulation.end(), mutatedPopulation.begin(), mutatedPopulation.end());
        population = selection(instance, runningPopulation, this->populationSize);
    } while (!termination(start, Clock::now()));

    return population[0]; // best rated individual in the population (after selection, decreasing order of quality)
}