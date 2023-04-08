
#ifndef PSPF_WT_OPERATORS_H
#define PSPF_WT_OPERATORS_H

#include "../../pfsp/pfspinstance.h"

vector<int> exchange(vector<int> state, int i, int j);
vector<int> insert(vector<int> state, int i, int j);
vector<int> transpose(vector<int> state, int i, int j);

vector<int> bestImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> bestNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);

vector<int> firstImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> betterNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);

vector<int> simplifiedRzHeuristic(PfspInstance &instance);
vector<int> getBestWCT(vector<int> partial, int newJob, PfspInstance& instance);
void getWeightedCompletionTime(vector <pair<double, int> > &WCT, PfspInstance &instance);

vector<int> randomPermutation(PfspInstance &instance);
int generateRndPosition(int min, int max);

#endif //PSPF_WT_OPERATORS_H
