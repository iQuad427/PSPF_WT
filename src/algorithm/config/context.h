//
// Created by Quentin Roels on 04/03/2023.
//

#ifndef PSPF_WT_CONTEXT_H
#define PSPF_WT_CONTEXT_H

#include "../operators/operators.h"
#include "../implementation/iterative/iterative_improvement.h"
#include "../implementation/vnd/variable_neighbourhood_descent.h"
#include "../solution.h"

#define ALL 0
#define II 1
#define VND 2

#define RANDOM 1
#define SIMPLE_RZ 2

#define BEST 1
#define FIRST 2

#define EXCHANGE 1
#define INSERT 2
#define TRANSPOSE 3

using namespace std;
typedef vector<int> State;

class Context {
private:
    string path;
    int algorithm;
    int initial;
    int neighbour;
    vector<int> pivots;
public:
    State (*initialisation) (PfspInstance&);
    State (*neighbourhood) (State, State (*) (State, int, int), PfspInstance&);
    State (*pivotingII) (State, int, int);
    vector<State (*) (State, int, int)> pivotingVND;

    Context();
    ~Context();

    string getPath();
    int getAlgorithm();
    int getInitial();
    int getNeighbour();
    vector<int> getPivots();

    void setAlgorithm(int algo);
    void setInputDirectory(char* path);
    void setInitialisation(char* config);
    void setNeighbourhood(char* config);
    void setPivotingII(char* config);
    void setPivotingVND(char* config[]);
};


#endif //PSPF_WT_CONTEXT_H
