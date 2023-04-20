
#include "../../operators.h"

vector<State> randomPopulationInitialisation(PfspInstance& instance, int populationSize) {
    vector<State> population = vector<State>(populationSize);

    for (int i = 0; i < populationSize; i++) {
        population[i] = randomPermutation(instance);
    }

    return population;
}