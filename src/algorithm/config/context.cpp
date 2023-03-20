//
// Created by Quentin Roels on 04/03/2023.
//

#include "context.h"

Context::Context() {
    this->algorithm = -1;
    this->initial = 0;
    this->neighbour = 0;
    this->pivots = vector<int>();
}

Context::~Context() {}

string Context::getPath() {
    return this->path;
}

int Context::getAlgorithm() {
    return this->algorithm;
}

int Context::getInitial() {
    return this->initial;
}

int Context::getNeighbour() {
    return this->neighbour;
}

vector<int> Context::getPivots() {
    return this->pivots;
}

void Context::setAlgorithm(int algo) {
    this->algorithm = algo;
}


void Context::setInputDirectory(char* path) {
    this->path = path;
}

void Context::setInitialisation(char* config) {
    if (!(((string) config).compare("--rand"))) {
        this->initial = RANDOM;
        this->initialisation = randomPermutation;
    } else if (!(((string) config).compare("--srz"))) {
        this->initial = SIMPLE_RZ;
        this->initialisation = simplifiedRzHeuristic;
    }
    return;
}

void Context::setNeighbourhood(char* config) {
    if (!(((string) config).compare("--best"))) {
        this->neighbour = BEST;
        this->neighbourhood = bestImprovement;
    } else if (!(((string) config).compare("--first"))) {
        this->neighbour = FIRST;
        this->neighbourhood = firstImprovement;
    }
    return;
}
void Context::setPivotingII(char* config) {
    if (!(((string) config).compare("--tran"))) {
        this->pivots.insert(pivots.end(), TRANSPOSE);
        this->pivotingII = transpose;
    } else if (!(((string) config).compare("--in"))) {
        this->pivots.insert(pivots.end(), INSERT);
        this->pivotingII = insert;
    } else if (!(((string) config).compare("--ex"))) {
        this->pivots.insert(pivots.end(), EXCHANGE);
        this->pivotingII = exchange;
    }
    return;
}

void Context::setPivotingVND(char* config[]) {

    for (int i = 0; i < 3; i++) {
        if (!(((string) config[i]).compare("--tran"))) {
            this->pivots.insert(pivots.end(), TRANSPOSE);
            this->pivotingVND.insert(pivotingVND.end(), transpose);
        } else if (!(((string) config[i]).compare("--ex"))) {
            this->pivots.insert(pivots.end(), EXCHANGE);
            this->pivotingVND.insert(pivotingVND.end(), exchange);
        } else if (!(((string) config[i]).compare("--in"))) {
            this->pivots.insert(pivots.end(), INSERT);
            this->pivotingVND.insert(pivotingVND.end(), insert);
        }
    }
    return;
}