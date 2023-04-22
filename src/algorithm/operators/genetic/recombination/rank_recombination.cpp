
#include "../../operators.h"

/**
 * Recombination giving the best performing individuals the right to chose any partner in the population
 *
 * @param instance
 * @param population
 * @param populationSize
 * @return
 */
Population meritocraticRecombination(PfspInstance& instance, Population population, int populationSize) {
    // TODO: could want to forbid self recombination
    Population recombinedPopulation;

    while (recombinedPopulation.size() < populationSize) {
        recombinedPopulation.insert(
                recombinedPopulation.end(),
                onePointCrossover(
                        instance,
                        population[rand() % (populationSize / 4)],
                        population[rand() % populationSize]
                )
        );
    }

    return recombinedPopulation;
}