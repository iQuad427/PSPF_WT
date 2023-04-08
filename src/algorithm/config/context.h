//
// Created by Quentin Roels on 04/03/2023.
//

#ifndef PSPF_WT_CONTEXT_H
#define PSPF_WT_CONTEXT_H

#include "../operators/operators.h"
#include "../implementation/algorithms.h"
#include "../solution.h"

#define ALL 0
#define II 1
#define VND 2

#define RANDOM 1
#define SIMPLE_RZ 2

#define BEST 1
#define FIRST 2

#define EXCHANGE 1
#define INSERT 2
#define TRANSPOSE 3

using namespace std;

typedef vector<int> State;

/**
 * Class for easier configuration of the algorithms, used when parsing the arguments,
 * contains all the information on the operators that one algorithm could need.
 *
 * Use :
 *  - Set all required attributes of the object through predefined strings (when parsing)
 *  - The Context object set up the corresponding functions in the correct fields by itself
 *  - Use the created object as a container for the configuration of an algorithm
 *
 *  Note : also serves as a global include file for the main file
 *      - includes all operators
 *      - includes all algorithms
 *      - includes all required classes
 *    => prevents from circular dependencies
 */
class Context {
private:
    string path;
    int algorithm;
    int initial;
    int pivot;
    vector<int> neighbourhoods;
public:
    // Constructors/Destructors
    Context();
    ~Context();

    // Generic getters and setters
    string getPath();
    int getAlgorithm();

    void setAlgorithm(int algo);
    void setInputDirectory(char* path);

    // Fields for Iterative Improvement and Variable Neighbourhood Descent algorithm configuration :
    State (*initialisation) (PfspInstance&);
    State (*pivoting) (State, State (*) (State, int, int), PfspInstance&);
    vector<State (*) (State, int, int)> neighbours;

    int getInitial();
    int getPivot();
    vector<int> getNeighbourhoods();

    void setInitialisation(char* config);
    void setPivoting(char* config);
    void setNeighbourhoods(int nbOfNeighbourhoods, char* config[]);

    // Fields for other algorithms :
    // ...
};


#endif //PSPF_WT_CONTEXT_H
