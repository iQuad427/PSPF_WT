//
// Created by Quentin Roels on 04/03/2023.
//

#ifndef PSPF_WT_CONTEXT_H
#define PSPF_WT_CONTEXT_H

#include "../operators/operators.h"
#include "../implementation/iterative/iterative_improvement.h"
#include "../implementation/vnd/variable_neighbourhood_descent.h"

using namespace std;
typedef vector<int> State;

class Context {
private:
    string path;
    string algorithm;
    State (*initialisation) (PfspInstance&);
    State (*neighbourhood) (State, State (*) (State, int, int), PfspInstance&);
    State (*pivotingII) (State, int, int);
    vector<State (*) (State, int, int)> pivotingVND;

public:
    string getPath();
    string getAlgorithm();

    void setAlgorithm(string algo);
    void setInputDirectory(char* path);
    void setInitialisation(char* config);
    void setNeighbourhood(char* config);
    void setPivotingII(char* config);
    void setPivotingVND(char* config[]);
};


#endif //PSPF_WT_CONTEXT_H
