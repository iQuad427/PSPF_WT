
#include "context.h"

Context::Context() {
    this->algorithm = -1;
    this->initial = 0;
    this->pivot = 0;
    this->tabuTenure = 0;
    this->maxTime = 0;
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

int Context::getTabuTenure(){
    return this->tabuTenure;
}

double Context::getMaxTime() {
    return this->maxTime;
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

void Context::setTabuTenure(int tenure) {
    this->tabuTenure = tenure;
}

void Context::setMaxTime(double time) {
    this->maxTime = time;
}

void Context::setNeighbourhoodII(char* config) {
    if (!(((string) config).compare("--tran"))) {
        this->neighbourhoods.insert(neighbourhoods.end(), TRANSPOSE);
        this->neighbourhoodII = transpose;
    } else if (!(((string) config).compare("--in"))) {
        this->neighbourhoods.insert(neighbourhoods.end(), INSERT);
        this->neighbourhoodII = insert;
    } else if (!(((string) config).compare("--ex"))) {
        this->neighbourhoods.insert(neighbourhoods.end(), EXCHANGE);
        this->neighbourhoodII = exchange;
    }
    return;
}

void Context::setNeighbourhoodVND(char* config[]) {

    for (int i = 0; i < 3; i++) {
        if (!(((string) config[i]).compare("--tran"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), TRANSPOSE);
            this->neighbourhoodVND.insert(neighbourhoodVND.end(), transpose);
        } else if (!(((string) config[i]).compare("--ex"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), EXCHANGE);
            this->neighbourhoodVND.insert(neighbourhoodVND.end(), exchange);
        } else if (!(((string) config[i]).compare("--in"))) {
            this->neighbourhoods.insert(neighbourhoods.end(), INSERT);
            this->neighbourhoodVND.insert(neighbourhoodVND.end(), insert);
        }
    }
    return;
}