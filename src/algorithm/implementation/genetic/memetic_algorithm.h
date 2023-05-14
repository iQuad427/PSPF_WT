
#ifndef PSPF_WT_MEMETIC_ALGORITHM_H
#define PSPF_WT_MEMETIC_ALGORITHM_H

#include "../../../pfsp/pfspinstance.h"
#include "../iterative/iterative_improvement.h"
#include "../../operators/operators.h"

using namespace std;
namespace fs = std::filesystem;

typedef vector<int> State;
typedef vector<State> Population;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> Time;

class MemeticAlgorithm {
private:
    float mutationRate;
    int populationSize;
    double maxTime;

    IterativeImprovement subsidiaryLocalSearch;
    Population (*initialisation) (PfspInstance& instance, int populationSize);
    Population (*recombination) (PfspInstance& instance, Population population, int populationSize);
    Population (*mutation) (PfspInstance& instance, Population population, float mutationRate);
    Population (*selection) (PfspInstance& instance, Population population, int populationSize);

    Population applySubsidiaryLocalSearch(PfspInstance& instance, Population population);
    bool termination(Time start, Time current);
public:
    MemeticAlgorithm();
    ~MemeticAlgorithm();

    void configure(
            int populationSize,
            float mutationRate,
            double maxTime,
            Population (*initialisation) (PfspInstance& instance, int populationSize),
            Population (*recombination) (PfspInstance& instance, Population population, int populationSize),
            Population (*mutation) (PfspInstance& instance, Population population, float mutationRate),
            Population (*selection) (PfspInstance& instance, Population population, int populationSize),
            State (*modifyState) (State, int, int)
    );
    State execute(PfspInstance&, int);
};


#endif //PSPF_WT_MEMETIC_ALGORITHM_H
