 //
// Created by Quentin Roels on 19/03/2023.
//

#ifndef PSPF_WT_OPERATORS_H
#define PSPF_WT_OPERATORS_H

#include <vector>
#include "../../pfsp/pfspinstance.h"

std::vector<int> exchange(std::vector<int> state, int i, int j);
std::vector<int> insert(std::vector<int> state, int i, int j);
std::vector<int> transpose(std::vector<int> state, int i, int j);

vector<int> bestImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> bestImprovement(
        vector<int> state,
        vector<int> (*yield) (vector<int>, int, int),
        PfspInstance& instance,
        bool (*condition) (vector<int>)
);
vector<int> bestNeighbour(
        vector<int> state,
        vector<int> (*yield) (vector<int>, int, int),
        bool (*condition) (vector<int>),
        PfspInstance& instance
);

vector<int> firstImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> firstImprovement(
        vector<int> state,
        vector<int> (*yield) (vector<int>, int, int),
        bool (*condition) (vector<int>),
        PfspInstance& instance
);
vector<int> betterNeighbour(
        vector<int> state,
        vector<int> (*yield) (vector<int>, int, int),
        bool (*condition) (vector<int>),
        PfspInstance& instance
);

vector<int> simplifiedRzHeuristic(PfspInstance &instance);
vector<int> getBestWCT(vector<int> partial, int newJob, PfspInstance& instance);
void getWeightedCompletionTime(vector <pair<double, int> > &WCT, PfspInstance &instance);

vector<int> randomPermutation(PfspInstance &instance);
int generateRndPosition(int min, int max);

#endif //PSPF_WT_OPERATORS_H
