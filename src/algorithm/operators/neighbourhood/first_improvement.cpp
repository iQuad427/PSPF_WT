//
// Created by Quentin Roels on 04/03/2023.
//

#include <vector>
#include "../../../pfsp/pfspinstance.h"

using namespace std;


vector<int> betterNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    long int best = instance.computeWT(state);
    vector<int> current;

    for (int i = 1; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            if (instance.computeWT((current = yield(state, i, j))) < best) {
                return current;
            }
        }
    }

    return state;
}

vector<int> firstImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    return betterNeighbour(state, yield, instance);
}