
#include "variable_neighbourhood_descent.h"

void VariableNeighbourhoodDescent::configure(
        State (*generateState) (PfspInstance&),
        State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
        vector<State (*) (State, int, int)> stateModifications
        ) {
    this->improveState = improveState;
    this->generateState = generateState;
    this->stateModifications = stateModifications;
}

State VariableNeighbourhoodDescent::execute(PfspInstance& instance) {
    State solution = generateState(instance);
    State backup;

    int nbOfNeighbourhoods = stateModifications.size();
    int currentNeighbourhood = 0;
    State (*modification) (State, int, int);

    while (currentNeighbourhood < nbOfNeighbourhoods) {
        modification = stateModifications[currentNeighbourhood];
        backup = solution;
        solution = improveState(solution, modification, instance);

        if (equal(backup.begin(), backup.end(), solution.begin())) {
            currentNeighbourhood++;
        } else {
            currentNeighbourhood = 0;
        }
    }

    return solution;
}
