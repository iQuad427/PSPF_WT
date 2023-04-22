//
// Created by Quentin Roels on 04/03/2023.
//

#ifndef PSPF_WT_ITERATIVE_IMPROVEMENT_H
#define PSPF_WT_ITERATIVE_IMPROVEMENT_H

#include "../../../pfsp/pfspinstance.h"

using namespace std;

typedef vector<int> State;

class IterativeImprovement {
private:
    State (*generateState) (PfspInstance&);
    State (*improveState) (State, State (*) (State, int, int), PfspInstance&);
    State (*modifyState) (State, int, int);
public:
    void configure(
            State (*generateState) (PfspInstance&),
            State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
            State (*modifyState) (State, int, int)
    );
    vector<int> execute(PfspInstance& instance, State candidate);
    vector<int> execute(PfspInstance& instance);
};


#endif //PSPF_WT_ITERATIVE_IMPROVEMENT_H
