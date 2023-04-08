//
// Created by Quentin Roels on 05/03/2023.
//

#ifndef PSPF_WT_VARIABLE_NEIGHBOURHOOD_DESCENT_H
#define PSPF_WT_VARIABLE_NEIGHBOURHOOD_DESCENT_H

#include "../../../pfsp/pfspinstance.h"

using namespace std;

typedef vector<int> State;

class VariableNeighbourhoodDescent {
private:
    State (*generateState) (PfspInstance&);
    State (*improveState) (State, State (*) (State, int, int), PfspInstance&);
    vector<State (*) (State, int, int)> stateModifications;
public:
    void configure(
            State (*generateState) (PfspInstance&),
            State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
            vector<State (*) (State, int, int)> stateModifications
    );
    vector<int> execute(PfspInstance&);
};

#endif //PSPF_WT_VARIABLE_NEIGHBOURHOOD_DESCENT_H
