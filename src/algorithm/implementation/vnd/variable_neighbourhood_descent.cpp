
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

/**
 * Method for executing the Variable Neighbourhood Descent local search
 *
 * @param instance containing all required information, such as the Job matrix
 * @return a local optima for the given algorithm specifications
 */
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

    cout << "Solution: ";
    for (int i = 1; i <= instance.getNbJob(); i++)
        cout << solution[i] << " ";
    cout << endl;

    return solution;
}
