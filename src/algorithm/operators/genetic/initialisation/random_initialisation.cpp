
#include "../../operators.h"

Population randomPopulationInitialisation(PfspInstance& instance, int populationSize) {
    Population population = vector<State>(populationSize);

    for (int i = 0; i < populationSize; i++) {
        population[i] = randomPermutation(instance);
    }

    return population;
}