
#ifndef PSPF_WT_ANT_COLONY_OPTIMIZATION_H
#define PSPF_WT_ANT_COLONY_OPTIMIZATION_H

#include "../../../pfsp/pfspinstance.h"

using namespace std;

typedef vector<int> State;

class AntColonyOptimization {
public:
    AntColonyOptimization();
    ~AntColonyOptimization();

    void configure();
    vector<int> execute(PfspInstance&);
};


#endif //PSPF_WT_ANT_COLONY_OPTIMIZATION_H
