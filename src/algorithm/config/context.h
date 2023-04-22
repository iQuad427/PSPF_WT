
#ifndef PSPF_WT_CONTEXT_H
#define PSPF_WT_CONTEXT_H

#include "../operators/operators.h"
#include "../implementation/algorithms.h"
#include "../solution.h"

/// ALGORITHMS
#define ALL 0
#define II 1
#define VND 2
#define TABU 3
#define GEN 4

/// SIMPLE SEARCH
// STATE INITIALISATION
#define RANDOM 1
#define SIMPLE_RZ 2

// PIVOTING RULES
#define BEST 1
#define FIRST 2

// NEIGHBOURHOODS
#define EXCHANGE 1
#define INSERT 2
#define TRANSPOSE 3

/// GENETIC ALGORITHM
// POPULATION INITIALISATION
#define RAND_INIT 1

// MUTATION
#define RAND_EX_MUT 1

// RECOMBINATION
#define RANK_COMB 1

// CROSSOVER
#define ONE_PT_CROSS 1
#define TWO_PT_CROSS 2
#define K_PT_CROSS 3
#define UNIFORM_CROSS 4

// SELECTION
#define RANK_SELECT 1

using namespace std;
typedef vector<int> State;

class Context {
private:
    // Generic
    string path;
    int algorithm;

    // Simple Search
    int initial;
    int pivot;
    vector<int> neighbourhoods;

    // Tabu Search
    int tabuTenure;

    // Memetic Algorithm
    int initPB;
    int select;
    int mutate;
    int recombine;
    int populationSize;
    float mutationRate;

    // Termination
    double maxTime;

public:
    // Search Algorithm
    State (*initialisation) (PfspInstance&);
    State (*pivoting) (State, State (*) (State, int, int), PfspInstance&);
    State (*neighbourhoodII) (State, int, int);
    vector<State (*) (State, int, int)> neighbourhoodVND;

    // Memetic Algorithm
    Population (*initialisationPB) (PfspInstance& instance, int populationSize);
    Population (*recombination) (PfspInstance& instance, Population population, int populationSize);
    Population (*mutation) (PfspInstance& instance, Population population, float mutationRate);
    Population (*selection) (PfspInstance& instance, Population population, int populationSize);

    // Constructors
    Context();
    ~Context();

    /// GETTERS
    string getPath();
    int getAlgorithm();
    int getInitial();
    int getPivot();

    int getInitialPB();
    int getRecombination();
    int getSelection();
    int getMutation();

    vector<int> getNeighbourhoods();

    int getTabuTenure();
    int getPopulationSize();
    float getMutationRate();
    double getMaxTime();

    /// SETTERS
    // Configuration
    void setAlgorithm(int algo);
    void setInputDirectory(char* path);
    void setInitialisation(char* config);
    void setPivoting(char* config);
    void setNeighbourhoodII(char* config);
    void setNeighbourhoodVND(char* config[]);

    void setInitialisationPB(char* config);
    void setRecombination(char* config);
    void setMutation(char* config);
    void setSelection(char* config);

    // Constants
    void setTabuTenure(int tenure);
    void setPopulationSize(int populationSize);
    void setMutationRate(float mutationRate);
    void setMaxTime(double time);
};


#endif //PSPF_WT_CONTEXT_H
