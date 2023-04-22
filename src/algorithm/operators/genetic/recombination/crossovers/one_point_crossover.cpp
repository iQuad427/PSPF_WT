
#include "../../../operators.h"

State onePointCrossover(PfspInstance& instance, State candidate1, State candidate2) {
    int pivot = rand() % candidate1.size() + 1;

    State newCandidate = vector<int>(candidate1.begin(), candidate1.begin() + pivot);
    newCandidate.insert(newCandidate.end(), candidate2.begin() + pivot, candidate2.end());

    newCandidate = repair(instance, candidate1, candidate2);

    return newCandidate;
}