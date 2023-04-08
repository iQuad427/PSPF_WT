
#ifndef PSPF_WT_ITERATED_LOCAL_SEARCH_H
#define PSPF_WT_ITERATED_LOCAL_SEARCH_H

#include "../../../pfsp/pfspinstance.h"

using namespace std;

typedef vector<int> State;

/**
 * Implementation of an iterated local search stochastic algorithm
 *
 * Basic configuration (for implementation exercise) :
 *  - initialisation : either SRZ or random
 *  - local search : either first or best improvement with exchange neighbourhood
 *  - acceptance criterion : simulated annealing, http://www.upv.es/deioac/Investigacion/Local%20search%20based%20algorithm_final.pdf
 *  - perturbation : x random insertions
 */
class IteratedLocalSearch {
private:

public:
    IteratedLocalSearch();
    ~IteratedLocalSearch();

    void configure();
    vector<int> execute(PfspInstance&);
};


#endif //PSPF_WT_ITERATED_LOCAL_SEARCH_H
