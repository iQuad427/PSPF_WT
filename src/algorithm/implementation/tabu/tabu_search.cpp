
#include "tabu_search.h"

TabuSearch::TabuSearch() {}

TabuSearch::~TabuSearch() {}

void TabuSearch::configure(
        double maxTime,
        int tabuTenure,
        State (*generateState) (PfspInstance&),
        State (*modifyState) (State, int, int))
        {
    this->maxTime = maxTime;
    this->tabuTenure = tabuTenure;
    this->generateState = generateState;
    this->modifyState = modifyState;
}

void TabuSearch::updateHistory(State candidate) {
    History::iterator it = this->history.begin();

    while (it != this->history.end()) {
        if (it->first == candidate) {
            it->second = this->tabuTenure;
        } else {
            it->second = it->second - 1;
            if (it->second == 0) {
                this->history.erase(it->first);
            }
        }
        it++;
    }
}

State TabuSearch::nextState(PfspInstance& instance, State state) {
    State result = state;
    long int best = instance.computeWT(state);
    long int current;

    for (int i = 1; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            State newState = modifyState(state, i, j);
//            cout << condition(newState) << endl;
            if ((current = instance.computeWT(newState)) < best && condition(newState)) {
//                cout << "improvement" << endl;
                result = newState;
                best = current;
            }
        }
    }

    return result;
}

bool TabuSearch::condition(State candidate) {
    History::iterator it = this->history.find(candidate);

    bool ret;
    if (it != this->history.end())
        ret = false;
    else {
        ret = true;
    }

    return ret;
}

bool TabuSearch::termination(Time start, Time current) {
    auto duration = chrono::duration_cast<chrono::microseconds>(current - start);

    return ((double) duration.count()) / 1000000 > this->maxTime;
}

vector<int> TabuSearch::execute(PfspInstance& instance) {
    Time start = Clock::now();

    State solution = generateState(instance);
    State backup;
    do {
        backup = solution;
        solution = nextState(instance, solution);
        updateHistory(solution);
    } while (!termination(start, Clock::now())); // && !equal(backup.begin(), backup.end(), solution.begin())

    return solution;
}
