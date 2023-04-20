
#ifndef PSPF_WT_OPERATORS_H
#define PSPF_WT_OPERATORS_H

#include <vector>
#include <cstdlib>
#include "../../pfsp/pfspinstance.h"

using namespace std;
typedef vector<int> State;

/** NEIGHBOURHOODS */
std::vector<int> exchange(std::vector<int> state, int i, int j);
std::vector<int> insert(std::vector<int> state, int i, int j);
std::vector<int> transpose(std::vector<int> state, int i, int j);

/** PIVOTING*/
// best improvement
vector<int> bestImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> bestNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), bool (*condition) (vector<int>), PfspInstance& instance);
// first improvement
vector<int> firstImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance);
vector<int> betterNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), bool (*condition) (vector<int>), PfspInstance& instance);

/** INITIALISATION */
// simplified RZ heuristic
vector<int> simplifiedRzHeuristic(PfspInstance &instance);
vector<int> getBestWCT(vector<int> partial, int newJob, PfspInstance& instance);
void getWeightedCompletionTime(vector <pair<double, int> > &WCT, PfspInstance &instance);
// random initialisation
vector<int> randomPermutation(PfspInstance &instance);
int generateRndPosition(int min, int max);

/** GENETIC */
// initialisation
vector<State> randomPopulationInitialisation(PfspInstance& instance, int populationSize);
// mutation
vector<State> randomExchangeMutation(PfspInstance& instance, vector<State> population, float mutationRate);
// recombination


#endif //PSPF_WT_OPERATORS_H
