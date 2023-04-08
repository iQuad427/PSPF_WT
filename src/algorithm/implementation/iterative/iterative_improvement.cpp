//
// Created by Quentin Roels on 04/03/2023.
//

#include "iterative_improvement.h"

void IterativeImprovement::configure(
        State (*generateState) (PfspInstance&),
        State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
        State (*modifyState) (State, int, int))
        {
    this->improveState = improveState;
    this->generateState = generateState;
    this->modifyState = modifyState;
}

/**
 * Method for executing the Iterative Improvement local search
 *
 * @param instance containing all required information, such as the Job matrix
 * @return a local optima for the given algorithm specifications
 */
State IterativeImprovement::execute(PfspInstance& instance) {
    State solution = generateState(instance);
    State backup;

    do {
        backup = solution;
        solution = improveState(solution, modifyState, instance);
    } while (!equal(backup.begin(), backup.end(), solution.begin()));

    cout << "Solution: ";
    for (int i = 1; i <= instance.getNbJob(); i++)
        cout << solution[i] << " ";
    cout << endl;

    return solution;
}
