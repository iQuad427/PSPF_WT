#include <iostream>
#include "pfsp/pfspinstance.h"
#include "algorithm/operators/initialisation/random_permutation.cpp"
#include "algorithm/operators/initialisation/simplified_rz.cpp"
#include "algorithm/operators/neighbourhood/first_improvement.cpp"
#include "algorithm/operators/neighbourhood/best_improvement.cpp"
#include "algorithm/operators/pivoting/exchange.cpp"
#include "algorithm/operators/pivoting/transpose.cpp"
#include "algorithm/operators/pivoting/insert.cpp"
#include "algorithm/implementation/iterative/iterative_improvement.h"
#include "algorithm/implementation/vnd/variable_neighbourhood_descent.h"

using namespace std;


bool solutionIsValid(State solution, PfspInstance& instance) {

    int n = instance.getNbJob();

    int sum = 0;
    for (int i = 1; i < n + 1; i++) {
        sum += solution[i];
    }
    bool value = (n * (n + 1))/2 == sum;

    bool size = solution.size() == n + 1;

    return size && value;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Usage: ./flowshopWCT <instance_file>" << endl;
        return 0;
    }

    /* initialize random seed: */
    srand(time(NULL));

    /* Create instance object */
    PfspInstance instance;

    /* Read data from file */
    if (!instance.readDataFromFile(argv[1]))
        return 1;

    /* Create a vector of int to represent the solution
      WARNING: By convention, we store the jobs starting from index 1,
               thus the size nbJob + 1. */
//  vector<int> solution (instance.getNbJob()+ 1);

    VariableNeighbourhoodDescent algorithm;

    vector<State (*) (State, int, int)> stateModifications;
    stateModifications.insert(stateModifications.begin(), transpose);
    stateModifications.insert(stateModifications.begin(), exchange);
    stateModifications.insert(stateModifications.begin(), insert);

    algorithm.configure(
            simplifiedRzHeuristic,
            firstImprovement,
            stateModifications
    );

    State solution = algorithm.execute(instance);

    cout << "Solution: ";
    for (int i = 1; i <= instance.getNbJob(); ++i)
        cout << solution[i] << " ";
    cout << endl;

    if (solutionIsValid(solution, instance)) {
        cout << "solution is valid" << endl;
    } else {
        cout << "solution is not valid" << endl;
    }

    /* Compute the WCT of this solution */
    long int WeightedSumCompletionTimes = instance.computeWCT(solution);
    long int WeightedTardiness = instance.computeWT(solution);
    cout << "Total weighted completion time: " << WeightedSumCompletionTimes << endl;
    cout << "Total weighted tardiness: " << WeightedTardiness << endl;

    return 0;
}
