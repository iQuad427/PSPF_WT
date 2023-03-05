//
// Created by Quentin Roels on 04/03/2023.
//

#include <vector>
#include "../../../pfsp/pfspinstance.h"

using namespace std;


vector<int> bestNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    vector<int> result = state;
    long int best = instance.computeWT(state);
    long int current;

    for (int i = 1; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            if ((current = instance.computeWT(yield(state, i, j))) < best) {
                result = yield(state, i, j); // TODO: non-sense for transposition, j is not used, useless iterations
                best = current;
            }
        }
    }

    return result;
}

vector<int> bestImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    return bestNeighbour(state, yield, instance);
}