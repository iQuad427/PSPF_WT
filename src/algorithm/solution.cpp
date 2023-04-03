//
// Created by Quentin Roels on 19/03/2023.
//

#include "solution.h"

Solution::Solution(string instance, int size, long int score) {
    this->score = score;
    this->size = size;
    this->instance = instance;
}

long int Solution::getScore() {
    return this->score;
}

string Solution::getPath() {
    return this->instance;
}

int Solution::getSize() {
    return this->size;
}

Solution::~Solution() {}

string Solution::toString() {
    // TODO: should return a string containing, "instance_name score"
    return "this is a test";
}