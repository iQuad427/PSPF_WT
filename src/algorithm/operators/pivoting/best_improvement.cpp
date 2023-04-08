
#include "../operators.h"

using namespace std;


vector<int> bestNeighbour(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    vector<int> result = state;
    long int best = instance.computeWT(state);
    long int current;

    for (int i = 1; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            if ((current = instance.computeWT(yield(state, i, j))) < best) {
                result = yield(state, i, j);
                best = current;
            }
        }
    }

    return result;
}

vector<int> bestImprovement(vector<int> state, vector<int> (*yield) (vector<int>, int, int), PfspInstance& instance) {
    return bestNeighbour(state, yield, instance);
}