#ifndef _PFSPINSTANCEWT_H_
#define _PFSPINSTANCEWT_H_

#include <string>
#include <vector>

using namespace std;

class PfspInstance{
  private:
    int nbJob;
    int nbMac;
    std::vector< long int > dueDates;
    std::vector< long int > priority;

    std::vector< std::vector <long int> > processingTimesMatrix;

  public:
    PfspInstance();
    ~PfspInstance();

    /* Read write privates attributes : */
    int getNbJob();
    int getNbMac();

    /* Allow the memory for the processing times matrix : */
    void allowMatrixMemory(int nbJ, int nbM);

    /* Read\Write values in the matrix : */
    long int getTime(int job, int machine);
    void setTime(int job, int machine, long int processTime);

    long int getDueDate(int job);
    void setDueDate(int job, int value);

    long int getPriority(int job);
    void setPriority(int job, int value);

    /* Read Data from a file : */
    bool readDataFromFile(char * fileName);

    long int computeWCT (vector< int > & sol);
    long int computeWctPerJob(vector< int > sol);

    long int computeWT(vector<int> sol);
};

#endif
