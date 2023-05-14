
#ifndef PSPF_WT_TABU_SEARCH_H
#define PSPF_WT_TABU_SEARCH_H

#include "../../../pfsp/pfspinstance.h"
#include <map>
#include <utility>

using namespace std;
namespace fs = std::filesystem;

typedef vector<int> State;
typedef map<State, int> History;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> Time;

class TabuSearch {
private:
    int tabuTenure;
    double maxTime;

    State (*generateState) (PfspInstance&);
    State (*modifyState) (State, int, int);
    History history; // associate a tabu status (tenure) to a state

    State nextState(PfspInstance& instance, State current);
    void updateHistory(State candidate);
    bool condition(State candidate);
    bool termination(Time start, Time current);
public:
    TabuSearch();
    ~TabuSearch();

    void configure(
            double maxTime,
            int tabuTenure,
            State (*generateState) (PfspInstance&),
            State (*modifyState) (State, int, int)
    );
    vector<int> execute(PfspInstance&, int);
};


#endif //PSPF_WT_TABU_SEARCH_H
