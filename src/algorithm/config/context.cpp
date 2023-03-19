//
// Created by Quentin Roels on 04/03/2023.
//

#include "context.h"

string Context::getPath() {
    return this->path;
}

int Context::getAlgorithm() {
    return this->algorithm;
}

void Context::setAlgorithm(int algo) {
    this->algorithm = algo;
}


void Context::setInputDirectory(char* path) {
    this->path = path;
}

void Context::setInitialisation(char* config) {
    if (!(((string) config).compare("--rand"))) {
        initialisation = randomPermutation;
    } else if (!(((string) config).compare("--srz"))) {
        initialisation = simplifiedRzHeuristic;
    }
    return;
}

void Context::setNeighbourhood(char* config) {
    if (!(((string) config).compare("--best"))) {
        neighbourhood = bestImprovement;
    } else if (!(((string) config).compare("--tran"))) {
        neighbourhood = firstImprovement;
    }
    return;
}
void Context::setPivotingII(char* config) {
    if (!(((string) config).compare("--tran"))) {
        pivotingII = transpose;
    } else if (!(((string) config).compare("--in"))) {
        pivotingII = insert;
    } else if (!(((string) config).compare("--ex"))) {
        pivotingII = exchange;
    }
    return;
}

void Context::setPivotingVND(char* config[]) {

    for (int i = 0; i < 3; i++) {
        if (!(((string) config[i]).compare("--tran"))) {
            pivotingVND.insert(pivotingVND.end(), transpose);
        } else if (!(((string) config[i]).compare("--ex"))) {
            pivotingVND.insert(pivotingVND.end(), exchange);
        } else if (!(((string) config[i]).compare("--in"))) {
            pivotingVND.insert(pivotingVND.end(), insert);
        }
    }
    return;
}