
#include "solution.h"

Solution::Solution(string instance, int size, long int score) {
    this->score = score;
    this->size = size;
    this->instance = instance;
}

Solution::~Solution() {}

long int Solution::getScore() {
    return this->score;
}

string Solution::getPath() {
    return this->instance;
}

int Solution::getSize() {
    return this->size;
}
