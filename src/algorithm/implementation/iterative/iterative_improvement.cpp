//
// Created by Quentin Roels on 04/03/2023.
//

#include "iterative_improvement.h"

void IterativeImprovement::configure(
        State (*generateState) (PfspInstance&),
        State (*improveState) (State, State (*) (State, int, int), PfspInstance&),
        State (*modifyState) (State, int, int))
        {
    this->generateState = generateState;
    this->improveState = improveState;
    this->modifyState = modifyState;
}

State IterativeImprovement::execute(PfspInstance& instance, State candidate) {
    State solution = candidate;
    State backup;

    do {
        backup = solution;
        solution = improveState(solution, modifyState, instance);
    } while (!equal(backup.begin(), backup.end(), solution.begin()));

    return solution;
}

State IterativeImprovement::execute(PfspInstance& instance) {
    return execute(instance, generateState(instance));
}
