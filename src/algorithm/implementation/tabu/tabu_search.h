
#ifndef PSPF_WT_TABU_SEARCH_H
#define PSPF_WT_TABU_SEARCH_H

#include "../../../pfsp/pfspinstance.h"

using namespace std;

typedef vector<int> State;

class TabuSearch {
public:
    TabuSearch();
    ~TabuSearch();

    void configure();
    vector<int> execute(PfspInstance&);
};


#endif //PSPF_WT_TABU_SEARCH_H
