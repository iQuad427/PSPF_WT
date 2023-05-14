
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
    vector<State> toErase = vector<State>();

    bool found = false;
    while (it != this->history.end()) {
        if (it->first == candidate) {
            it->second = this->tabuTenure;
            found = true;
        } else {
            it->second = it->second - 1;
            if (it->second <= 0) {
                toErase.insert(toErase.end(), it->first);
            }
        }
        it++;
    }

    for (State free : toErase) {
        this->history.erase(free);
    }

    if (!found && this->tabuTenure > 0) {
        this->history.insert(pair<State, int>(candidate, this->tabuTenure));
    }
}

/**
 * Simple best improvement loop that take the tabu condition into account
 */
State TabuSearch::nextState(PfspInstance& instance, State state) {
    State result = modifyState(state, 1, 2);
    long int best = instance.computeWT(result);
    long int current;

    for (int i = 1; i < state.size(); i++) {
        for (int j = i + 1; j < state.size(); j++) {
            State newState = modifyState(state, i, j);
            if ((current = instance.computeWT(newState)) < best && condition(newState)) {
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

vector<int> TabuSearch::execute(PfspInstance& instance, int iteration) {
    Time start = Clock::now();
    Time now;

    fs::path p(instance.fileName);

    ofstream runTimeDistribution;
    runTimeDistribution.open("out/rtd/tabu/" + p.stem().string() + "_" + to_string(iteration));

    State solution = generateState(instance);

    State best_solution = solution;
    long int best_score = instance.computeWT(best_solution);
    long int new_score;

    now = Clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(now - start);
    double time = ((double) duration.count()) / 1000000;

    runTimeDistribution << time << " " << best_score << endl;

    do {
        solution = nextState(instance, solution);

        if ((new_score = instance.computeWT(solution)) < best_score) {
            best_score = new_score;
            best_solution = solution;
        }

        updateHistory(solution);

        now = Clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(now - start);
        time = ((double) duration.count()) / 1000000;

        runTimeDistribution << time << " " << best_score << endl;
    } while (!termination(start, Clock::now())); // && !equal(backup.begin(), backup.end(), solution.begin())

    return best_solution;
}
