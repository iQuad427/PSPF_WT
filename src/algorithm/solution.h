//
// Created by Quentin Roels on 19/03/2023.
//

#ifndef PSPF_WT_SOLUTION_H
#define PSPF_WT_SOLUTION_H

#include <vector>
#include <string>

using namespace std;

/**
 * Simple data class to return easily all the required information about the end of an algorithm.
 */
class Solution {
private:
    vector<int> state;
    int size;
    string instance;
    long int score;
public:
    Solution(string instance, int size, long int score);
    ~Solution();

    string getPath();
    long int getScore();
    int getSize();

    string toString();
};


#endif //PSPF_WT_SOLUTION_H
