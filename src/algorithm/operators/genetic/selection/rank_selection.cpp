
#include "../../operators.h"
#include <queue>

struct ScoredIndividual {
    long int score;
    State individual;

    ScoredIndividual(State individual, long int score) : individual(individual), score(score) {}
};

struct CompareScore {
    bool operator()(ScoredIndividual const& p1, ScoredIndividual const& p2) {
        return p1.score > p2.score;
    }
};

Population rankSelection(PfspInstance& instance, Population population, int populationSize) {
    priority_queue<ScoredIndividual, vector<ScoredIndividual>, CompareScore> scoredPopulation;
    Population selectedPopulation;

    for (int i = 0; i < population.size(); i++) {
        scoredPopulation.push(ScoredIndividual(population[i], instance.computeWT(population[i])));
    }

    for (int i = 0; i < populationSize; i++) {
        selectedPopulation.insert(selectedPopulation.end(), scoredPopulation.top().individual);
        scoredPopulation.pop();
    }

    return selectedPopulation;
}

