//
// Created by Quentin Roels on 19/03/2023.
//

#include "solution.h"

Solution::Solution(string instance, long int score) {
    this->score = score;
    this->instance = instance;
}

Solution::~Solution() {}

string Solution::toString() {
    // TODO: should return a string containing, "instance_name score"
    return "this is a test";
}