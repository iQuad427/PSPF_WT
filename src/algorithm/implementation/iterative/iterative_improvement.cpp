//
// Created by Quentin Roels on 04/03/2023.
//

#include "iterative_improvement.h"
#include <iostream>

using namespace std;

void IterativeImprovement::configure(
        State (*generateState) (PfspInstance&),
        State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
        State (*modifyState) (State, int, int))
        {
    this->improveState = improveState;
    this->generateState = generateState;
    this->modifyState = modifyState;
}

State IterativeImprovement::execute(PfspInstance& instance) {
    State solution = generateState(instance);
    State backup;

    cout << "Solution: ";
    for (int i = 1; i <= instance.getNbJob(); i++)
        cout << solution[i] << " ";
    cout << endl;

    do {
        backup = solution;
        solution = improveState(solution, modifyState, instance);
    } while (!equal(backup.begin(), backup.end(), solution.begin()));

    return solution;
}
