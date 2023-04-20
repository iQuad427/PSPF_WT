
#include "memetic_algorithm.h"

MemeticAlgorithm::MemeticAlgorithm() {}

MemeticAlgorithm::~MemeticAlgorithm() {}

void MemeticAlgorithm::configure() {}

Population MemeticAlgorithm::applySubsidiaryLocalSearch(PfspInstance& instance, Population population) {

}

bool MemeticAlgorithm::termination(Time start, Time current) {
    auto duration = chrono::duration_cast<chrono::microseconds>(current - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}

State MemeticAlgorithm::execute(PfspInstance& instance) {
    Time start = Clock::now();

    Population population = initialisation(instance, this->populationSize);
    population = applySubsidiaryLocalSearch(instance, population);

    Population recombinedPopulation;

    do {

    } while (!termination(start, Clock::now()));

    return population[0]; // TODO: change to return the best out of the last population
}