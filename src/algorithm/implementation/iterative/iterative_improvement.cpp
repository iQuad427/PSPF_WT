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

/**
 * Method for executing the Iterative Improvement local search
 *
 * @param instance containing all required information, such as the Job matrix
 * @return a local optima for the given algorithm specifications
 */
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
