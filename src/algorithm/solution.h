//
// Created by Quentin Roels on 19/03/2023.
//

#ifndef PSPF_WT_SOLUTION_H
#define PSPF_WT_SOLUTION_H

#include <vector>
#include <string>

using namespace std;

// TODO: add solution class to Makefile
class Solution {
private:
    vector<int> state;
    string instance;
    long int score;
public:
    Solution(string instance, long int score);
    ~Solution();

    string toString();
};


#endif //PSPF_WT_SOLUTION_H
