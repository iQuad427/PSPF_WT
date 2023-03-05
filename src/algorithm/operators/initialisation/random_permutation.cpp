#include <cstdlib>
#include <vector>
#include "../../../pfsp/pfspinstance.h"

using namespace std;

int generateRndPosition(int min, int max)
{
    return ( rand() % max + min );
}

/* Fill the solution with numbers between 1 and nbJobs, shuffled */
vector<int> randomPermutation(PfspInstance &instance)
{
    vector<int> sol = vector<int>(instance.getNbJob() + 1);

    int nbJobs = instance.getNbJob();

    vector<bool> alreadyTaken(nbJobs + 1, false); // nbJobs elements with value false
    vector<int>  chosenNumber(nbJobs + 1, 0);

    int nbj;
    int rnd, i, j, nbFalse;

    nbj = 0;
    for (i = nbJobs; i >= 1; --i)
    {
        rnd = generateRndPosition(1, i);
        nbFalse = 0;

        /* find the rndth cell with value = false : */
        for (j = 1; nbFalse < rnd; ++j)
            if ( ! alreadyTaken[j] )
                ++nbFalse;
        --j;

        sol[j] = i;

        ++nbj;
        chosenNumber[nbj] = j;

        alreadyTaken[j] = true;
    }

    return sol;
}