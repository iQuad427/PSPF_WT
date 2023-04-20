
#ifndef PSPF_WT_MEMETIC_ALGORITHM_H
#define PSPF_WT_MEMETIC_ALGORITHM_H

#include "../../../pfsp/pfspinstance.h"
#include "../iterative/iterative_improvement.h"

using namespace std;

typedef vector<int> State;

class MemeticAlgorithm {
private:
    IterativeImprovement subsidiaryLocalSearch;
    vector<State> (*initialisation) (int populationSize, PfspInstance&);
    vector<State> (*recombination) (vector<State> population, PfspInstance&);
    vector<State> (*mutation) (vector<State> population, PfspInstance&);
    vector<State> (*selection) (vector<State> population, PfspInstance&);
public:
    MemeticAlgorithm();
    ~MemeticAlgorithm();

    void configure();
    vector<int> execute(PfspInstance&);
};


#endif //PSPF_WT_MEMETIC_ALGORITHM_H
