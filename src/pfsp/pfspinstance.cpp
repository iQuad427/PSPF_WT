
#include "pfspinstance.h"

PfspInstance::PfspInstance() {}

PfspInstance::~PfspInstance() {}

int PfspInstance::getNbJob() {
    return nbJob;
}

int PfspInstance::getNbMac() {
    return nbMac;
}

long int PfspInstance::getPriority(int job) {
    return priority[job];
}

long int PfspInstance::getDueDate(int job) {
    return dueDates[job];
}

/* Allow the memory for the processing times matrix : */
void PfspInstance::allowMatrixMemory(int nbJ, int nbM) {
    processingTimesMatrix.resize(nbJ + 1);          // 1st dimension

    for (int cpt = 0; cpt < nbJ + 1; ++cpt) {
        processingTimesMatrix[cpt].resize(nbM + 1); // 2nd dimension

        dueDates.resize(nbJ + 1);
        priority.resize(nbJ + 1);
    }
}


long int PfspInstance::getTime(int job, int machine) {
    if (job == 0) {
        return 0;
    } else {
        if ((job < 1) || (job > nbJob) || (machine < 1) || (machine > nbMac))
            cout << "ERROR. file:pfspInstance.cpp, method:getTime. Out of bound. job=" << job
                 << ", machine=" << machine << std::endl;

        return processingTimesMatrix[job][machine];
    }
}


/* Read the instance from file : */
bool PfspInstance::readDataFromFile(char *fileName) {
    bool everythingOK = true;
    int j, m; // iterators
    long int readValue;
    string str;
    ifstream fileIn;
    char *aux2;
    char fileNameOK[100] = "";

    aux2 = (strrchr(fileName, '/'));

    if (aux2 == NULL) {
        aux2 = fileName;
    } else {
        aux2 += 1;
    }

    strcat(fileNameOK, aux2);

    fileIn.open(fileName);

    if (fileIn.is_open()) {
        fileIn >> nbJob;
        fileIn >> nbMac;
        allowMatrixMemory(nbJob, nbMac);

        for (j = 1; j <= nbJob; ++j) {
            for (m = 1; m <= nbMac; ++m) {
                fileIn >> readValue; // The number of each machine, not important !
                fileIn >> readValue; // Process Time

                processingTimesMatrix[j][m] = readValue;
            }
        }
        fileIn >> str; // this is not read

        for (j = 1; j <= nbJob; ++j) {
            fileIn >> readValue; // -1
            fileIn >> readValue;
            dueDates[j] = readValue;
            fileIn >> readValue; // -1
            fileIn >> readValue;
            priority[j] = readValue;
        }

        fileIn.close();
    } else {
        cout << "ERROR. file:pfspInstance.cpp, method:readDataFromFile, "
             << "error while opening file " << fileName << std::endl;

        everythingOK = false;
    }

    return everythingOK;
}


/* Compute the weighted sum of completion time of a given solution */
long int PfspInstance::computeWCT(vector<int> &sol) {
    int jobNumber;
    long int wct;

    /* We need end times on previous machine : */
    vector<long int> previousMachineEndTime(nbJob + 1);
    /* And the end time of the previous job, on the same machine : */
    long int previousJobEndTime;

    /* 1st machine : */
    previousMachineEndTime[0] = 0;
    for (int j = 1; j <= nbJob; j++) {
        jobNumber = sol[j];
        previousMachineEndTime[j] = previousMachineEndTime[j - 1] + processingTimesMatrix[jobNumber][1];
    }

    /* others machines : */
    for (int m = 2; m <= nbMac; m++) {
        previousMachineEndTime[1] += processingTimesMatrix[sol[1]][m];
        previousJobEndTime = previousMachineEndTime[1];

        for (int j = 2; j <= nbJob; j++) {
            jobNumber = sol[j];

            if (previousMachineEndTime[j] > previousJobEndTime) {
                previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[jobNumber][m];
                previousJobEndTime = previousMachineEndTime[j];
            } else {
                previousJobEndTime += processingTimesMatrix[jobNumber][m];
                previousMachineEndTime[j] = previousJobEndTime;
            }
        }
    }

    wct = 0;
    for (int j = 1; j <= nbJob; j++) {
        wct += previousMachineEndTime[j] * priority[sol[j]];
    }

    return wct;
}

long int PfspInstance::computeWctPerJob(vector<int> sol) {
    int jobNumber;
    long int wct;

    int nbJob = sol.size() - 1;

    /* We need end times on previous machine : */
    vector<long int> previousMachineEndTime(nbJob + 1);
    /* And the end time of the previous job, on the same machine : */
    long int previousJobEndTime;

    /* 1st machine : */
    previousMachineEndTime[0] = 0;
    for (int j = 1; j <= nbJob; j++) {
        jobNumber = sol[j];
        previousMachineEndTime[j] = previousMachineEndTime[j - 1] + processingTimesMatrix[jobNumber][1];
    }

    /* others machines : */
    for (int m = 2; m <= nbMac; m++) {
        previousMachineEndTime[1] += processingTimesMatrix[sol[1]][m];
        previousJobEndTime = previousMachineEndTime[1];

        for (int j = 2; j <= nbJob; j++) {
            jobNumber = sol[j];

            if (previousMachineEndTime[j] > previousJobEndTime) {
                previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[jobNumber][m];
                previousJobEndTime = previousMachineEndTime[j];
            } else {
                previousJobEndTime += processingTimesMatrix[jobNumber][m];
                previousMachineEndTime[j] = previousJobEndTime;
            }
        }
    }

    wct = 0;
    for (int j = 1; j <= nbJob; j++) {
        wct += previousMachineEndTime[j] * priority[sol[j]];
    }

    return wct;
}

long int PfspInstance::computeWT(vector<int> sol) {
    int jobNumber;
    long int wt;

    /* We need end times on previous machine : */
    vector<long int> previousMachineEndTime(nbJob + 1);
    /* And the end time of the previous job, on the same machine : */
    long int previousJobEndTime;

    /* 1st machine : */
    previousMachineEndTime[0] = 0;
    for (int j = 1; j <= nbJob; j++) {
        jobNumber = sol[j];
        previousMachineEndTime[j] = previousMachineEndTime[j - 1] + processingTimesMatrix[jobNumber][1];
    }

    /* others machines : */
    for (int m = 2; m <= nbMac; m++) {
        previousMachineEndTime[1] += processingTimesMatrix[sol[1]][m];
        previousJobEndTime = previousMachineEndTime[1];

        for (int j = 2; j <= nbJob; j++) {
            jobNumber = sol[j];

            if (previousMachineEndTime[j] > previousJobEndTime) {
                previousMachineEndTime[j] = previousMachineEndTime[j] + processingTimesMatrix[jobNumber][m];
                previousJobEndTime = previousMachineEndTime[j];
            } else {
                previousJobEndTime += processingTimesMatrix[jobNumber][m];
                previousMachineEndTime[j] = previousJobEndTime;
            }
        }
    }

    wt = 0;
    int tardiness;
    for (int j = 1; j < nbJob + 1; j++) {
        tardiness = previousMachineEndTime[j] - getDueDate(sol[j]);
        wt += (tardiness > 0 ? tardiness : 0) * priority[sol[j]];
    }

    return wt;
}