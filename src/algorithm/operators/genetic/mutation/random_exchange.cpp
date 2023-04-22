
#include "../../operators.h"


State randomExchange(PfspInstance& instance, State individual) {
    // generate two pseudo-random integers in [1, 50]
    int i = rand() % instance.getNbJob() + 1;
    int j = rand() % instance.getNbJob() + 1;

    return exchange(individual, i, j);
}


Population randomExchangeMutation(PfspInstance& instance, Population population, float mutationRate) {
    Population newPopulation = vector<State>(population.size());

    for (int i = 0; i < population.size(); i++) {
        float rng = (float) (rand() % 100) / (float) 100;
        if (rng <= mutationRate) {
            newPopulation[i] = randomExchange(instance, population[i]);
        } else {
            newPopulation[i] = population[i];
        }
    }

    return newPopulation;
}
