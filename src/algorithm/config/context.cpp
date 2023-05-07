
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

int Context::getInitialPB() {
    return this->initPB;
}

int Context::getRecombination() {
    return this->recombine;
}

int Context::getSelection() {
    return this->select;
}

int Context::getMutation() {
    return this->mutate;
}

int Context::getTabuTenure(){
    return this->tabuTenure;
}

float Context::getMutationRate() {
    return this->mutationRate;
}

int Context::getPopulationSize() {
    return this->populationSize;
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

void Context::setPopulationSize(int populationSize) {
    this->populationSize = populationSize;
}

void Context::setMutationRate(float mutationRate) {
    this->mutationRate = mutationRate;
}

void Context::setInitialisationPB(char* config) {
    if (!(((string) config).compare("--rand-init"))) {
        this->initPB = RAND_INIT;
        this->initialisationPB = randomPopulationInitialisation;
    }
    return;
}

void Context::setRecombination(char* config) {
    if (!(((string) config).compare("--rank-comb"))) {
        this->recombine = RANK_COMB;
        this->recombination = meritocraticRecombination;
    }
    return;
}

void Context::setSelection(char* config) {
    if (!(((string) config).compare("--rank-select"))) {
        this->select = RANK_SELECT;
        this->selection = rankSelection;
    }
    return;
}

void Context::setMutation(char* config) {
    if (!(((string) config).compare("--rand-mut"))) {
        this->mutate = RAND_EX_MUT;
        this->mutation = randomExchangeMutation;
    }
    return;
}