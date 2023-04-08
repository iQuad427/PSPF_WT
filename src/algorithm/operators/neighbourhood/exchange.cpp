
#include "../operators.h"

/*
 * Exchange element at index i and j
 */
std::vector<int> exchange(std::vector<int> state, int i, int j) {
    int buffer = state[j];
    state[j] = state[i];
    state[i] = buffer;

    return state;
}