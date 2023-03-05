#include "../../../pfsp/pfspinstance.h"
#include <iostream>
#include <vector>

using namespace std;

void getWeightedCompletionTime(vector <pair<double, int> > &WCT, PfspInstance &instance) {
    for (int i = 1; i < instance.getNbJob() + 1; i++) {
        long int sum = 0;
        for (int j = 1; j < instance.getNbMac(); j++) {
            sum += instance.getTime(i, j);
        }
        WCT[i].first = sum;
        WCT[i].second = i;
    }

    for (int i = 0; i < instance.getNbJob() + 1; i++) {
        WCT[i].first = WCT[i].first / instance.getPriority(i);
    }
}

vector<int> getBestWCT(vector<int> partial, int newJob, PfspInstance& instance) {
    vector<int> current = partial;

    if (current.size() == 1) {
        current.insert(current.begin() + 1, newJob);
        return current;
    }

    current.insert(current.begin() + 1, newJob);
    vector<int> solution = current;
    long int best = instance.computeWctPerJob(solution);
    long int score;

    for (int i = 2; i < partial.size() + 1; i++) {
        current = partial;
        current.insert(current.begin() + i, newJob);

        if ((score = instance.computeWctPerJob(current)) < best) {
            solution = current;
            best = score;
        }

    }

    return solution;
}


vector<int> simplifiedRzHeuristic(PfspInstance &instance) {
    vector < pair < double, int > > WCT = vector < pair < double, int > > (instance.getNbJob() + 1);
    getWeightedCompletionTime(WCT, instance);

    sort(WCT.begin(), WCT.end());

    vector<int> partial = vector<int>();
    partial.insert(partial.begin(), 0);

    for (int i = 1; i < instance.getNbJob() + 1; i++) {
        partial = getBestWCT(partial, WCT[i].second, instance);
    }

    return partial;
}
