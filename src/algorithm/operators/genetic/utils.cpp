

#include "../operators.h"
#include <set>

/**
 * Repair a candidate solution to make it valid (permutation of numbers from 1 to 50)
 *
 * @param instance the instance information
 * @param candidate1 the candidate to repair
 * @param candidate2 the candidate it was merged with
 * @return the repaired candidate (valid solution)
 */
State repair(PfspInstance& instance, State candidate1, State candidate2) {
    State repairedCandidate = vector<int>(instance.getNbJob() + 1);
    set<int> doneJobs(candidate1.begin(), candidate1.end());

    vector<int> remainingJobs;
    for (int i = 1; i < instance.getNbJob() + 1; i++) {
        if (doneJobs.insert(candidate2[i]).second) {
            // if job is not in first candidate, add it to remaining jobs
            remainingJobs.insert(remainingJobs.begin(), candidate2[i]);
        }
    }

    set<int> buffer;
    vector<int>::iterator it = remainingJobs.begin();
    for (int i = 1; i < instance.getNbJob() + 1; i++) {
        if (!buffer.insert(candidate1[i]).second) {
            // if already in the buffer (mean that we have a duplicate)
            repairedCandidate[i] = (*it);
        } else {
            // else not seen the job yet, can simply keep it
            repairedCandidate[i] = candidate1[i];
        }
    }

    return repairedCandidate;
}