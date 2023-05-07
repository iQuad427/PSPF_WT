
#include "../operators.h"

/**
 * Insert element at index i after element at index j
 */
std::vector<int> insert(std::vector<int> state, int i, int j) {
    int buffer = state[i];
    state.erase(state.begin() + i);
    state.insert(state.begin() + j, buffer);

    return state;
}