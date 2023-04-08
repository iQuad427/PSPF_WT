
#include "../operators.h"

/*
 * Transpose the element at index i from one place
 */
std::vector<int> transpose(std::vector<int> state, int i, int j) {
    int buffer = state[i+1];
    state[i+1] = state[i];
    state[i] = buffer;

    return state;
}