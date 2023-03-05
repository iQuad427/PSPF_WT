
#include "variable_neighbourhood_descent.h"
#include <iostream>

using namespace std;

void VariableNeighbourhoodDescent::configure(
        State (*generateState) (PfspInstance&),
        State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
        vector<State (*) (State, int, int)> stateModifications)
{
    this->improveState = improveState;
    this->generateState = generateState;
    this->stateModifications = stateModifications;
}

State VariableNeighbourhoodDescent::execute(PfspInstance& instance) {
    State solution = generateState(instance);
    State backup;

    cout << "Initial : ";
    for (int i = 1; i <= instance.getNbJob(); i++)
        cout << solution[i] << " ";
    cout << endl;

    for (State (*modification) (State, int, int) : stateModifications) {
        do {
            backup = solution;
            solution = improveState(solution, modification, instance);
        } while (!equal(backup.begin(), backup.end(), solution.begin()));
    }

    return solution;
}
