//
// Created by Quentin Roels on 04/03/2023.
//

#include "context.h"

Context::Context() {
    this->algorithm = -1;
    this->initial = 0;
    this->pivot = 0;
    this->neighbourhoods = vector<int>();
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

int Context::getPivot() {
    return this->pivot;
}

vector<int> Context::getNeighbourhoods() {
    return this->neighbourhoods;
}

void Context::setAlgorithm(int algo) {
    this->algorithm = algo;
}


void Context::setInputDirectory(char* path) {
    this->path = path;
}

/**
 * Set up the initialisation operator for II and/or VND algorithms
 *
 * @param config one of the strings corresponding to possible initialisation (random or simple RZ heuristic)
 */
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

/**
 * Set up the pivoting operator for II and/or VND algorithms
 *
 * @param config one of the strings corresponding to possible pivoting rules (best or first improvement)
 */
void Context::setPivoting(char* config) {
    if (!(((string) config).compare("--best"))) {
        this->pivot = BEST;
        this->pivoting = bestImprovement;
    } else if (!(((string) config).compare("--first"))) {
        this->pivot = FIRST;
        this->pivoting = firstImprovement;
    }
    return;
}

/**
 * Set up the different neighbourhoods for II/VND algorithms
 *
 * @param nbOfNeighbourhoods permits for generalization of VNDs, as many neighbourhoods as wanted (1 being a simple II)
 * @param config one of the strings corresponding to possible pivoting rules (transpose, insert or exchange)
 */
void Context::setNeighbourhoods(int nbOfNeighbourhoods, char* config[]) {

    for (int i = 0; i < nbOfNeighbourhoods; i++) {
        if (!(((string) config[i]).compare("--tran"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), TRANSPOSE);
            this->neighbours.insert(neighbours.end(), transpose);
        } else if (!(((string) config[i]).compare("--ex"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), EXCHANGE);
            this->neighbours.insert(neighbours.end(), exchange);
        } else if (!(((string) config[i]).compare("--in"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), INSERT);
            this->neighbours.insert(neighbours.end(), insert);
        }
    }
    return;
}