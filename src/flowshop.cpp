#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <cstdlib>

#include "algorithm/config/context.h"
#include "algorithm/operators/operators.h"
#include <set>

using namespace std;
namespace fs = std::filesystem;

Solution executeInstance(Context context, char* path);
bool solutionIsValid(State solution, PfspInstance& instance);
State executeVariableNeighbourhoodDescent(PfspInstance& instance, Context context);
State executeIterativeImprovement(PfspInstance& instance, Context context);
State executeTabuSearch(PfspInstance& instance, Context context);
State executeMemeticAlgorithm(PfspInstance& instance, Context context);
Context parseArguments(int argc, char* argv[]);
vector<string> getInputFiles(Context context);
string buildOutputFileNameFromContext(Context context);
void launchExperiment(Context context, vector<string>, int iteration);

int main(int argc, char *argv[]) {
    /*
     * Arguments :
     *  - input (directory containing the instances on which execute the algorithm)
     *      - will execute on all files of the input (sorted in alphabetical order)
     *      - output per algorithm combination on independent data files
     *      - output per size of instances
     *  - algorithm (either iterative improvement or variable pivoting descent)
     *      - initialisation
     *      - pivoting
     *      - neighbourhood
     *
     * Output file name :
     *  - ii-initialisation-pivoting-neighbourhood-instance_size
     *  - vnd-initialisation-pivoting-pivoting_order-instance_size
     *      example : ii-random-first-exchange-20_50
     *      example : vnd-random-first-transpose_exchange_insert-20_50
     *
     * Output file format :
     *  - Instance name
     *  - Best score found for the instance
     *  - Time taken
     */
    int iteration = atoi(argv[1]);

    Context context = parseArguments(argc, argv);
    vector<string> files = getInputFiles(context);

    launchExperiment(context, files, iteration);
}

void launchExperiment(Context context, vector<string> files, int iteration) {
    switch (context.getAlgorithm()) {
        case II:
        case VND:
        case TABU:
        case GEN: {
            string fileName = buildOutputFileNameFromContext(context);
            cout << "Experiment: " << fileName << endl;

            ofstream resultFile;
            resultFile.open(fileName);
            resultFile << "Instance Size Score Time" << endl;

            for (string filePath: files) {
                char *path = new char[filePath.length() + 1];
                strcpy(path, filePath.c_str());

                /* initialize random seed */
                srand(time(NULL));

                for (int i = 0; i < iteration; i++) {

                    auto start = chrono::high_resolution_clock::now();

                    Solution solution = executeInstance(context, path);

                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);

                    fs::path p(solution.getPath());
                    resultFile << p.stem().string() << " ";
                    resultFile << solution.getSize() << " ";
                    resultFile << solution.getScore()  << " ";
                    resultFile << ((double) time.count()) / 1000000 << endl;
                }
            }
            resultFile.close();
            break;
        }
        default:
            cout << "Error: wrong algorithm selected, " << context.getAlgorithm() << endl;
            throw;
    }
}

Solution executeInstance(Context context, char* path) {
    cout << "Instance: " << path << endl;

    /* Create instance object */
    PfspInstance instance;

    /* Read data from file */
    if (!instance.readDataFromFile(path)) {
        throw;
    }

    State solution;
    if (context.getAlgorithm() == VND) {
        solution = executeVariableNeighbourhoodDescent(instance, context);
    } else if (context.getAlgorithm() == II) {
        solution = executeIterativeImprovement(instance, context);
    } else if (context.getAlgorithm() == TABU) {
        solution = executeTabuSearch(instance, context);
    } else if (context.getAlgorithm() == GEN) {
        solution = executeMemeticAlgorithm(instance, context);
    } else {
        cout << "Error: wrong context parameter, " << context.getAlgorithm() << endl;
        throw;
    }

    /* Compute the WCT of this solution */
    long int weightedSumCompletionTimes = instance.computeWCT(solution);
    long int weightedTardiness = instance.computeWT(solution);

    return Solution(path, instance.getNbJob(), weightedTardiness);
}

bool solutionIsValid(State solution, PfspInstance& instance) {
    int n = instance.getNbJob();

    int sum = 0;
    for (int i = 1; i < n + 1; i++) {
        sum += solution[i];
    }
    bool value = (n * (n + 1))/2 == sum;

    bool size = solution.size() == n + 1;

    return size && value;
}

State executeVariableNeighbourhoodDescent(PfspInstance& instance, Context context) {
    VariableNeighbourhoodDescent algorithm;

    algorithm.configure(
            context.initialisation,
            context.pivoting,
            context.neighbourhoodVND
    );

    return algorithm.execute(instance);
}

State executeIterativeImprovement(PfspInstance& instance, Context context) {
    IterativeImprovement algorithm;

    algorithm.configure(
            context.initialisation,
            context.pivoting,
            context.neighbourhoodII
    );

    return algorithm.execute(instance);
}

State executeTabuSearch(PfspInstance& instance, Context context) {
    TabuSearch algorithm;

    algorithm.configure(
            context.getMaxTime(),
            context.getTabuTenure(),
            context.initialisation,
            context.neighbourhoodII
    );

    return algorithm.execute(instance);
}

State executeMemeticAlgorithm(PfspInstance& instance, Context context) {
    MemeticAlgorithm algorithm;

    algorithm.configure(
            context.getPopulationSize(),
            context.getMutationRate(),
            context.getMaxTime(),
            context.initialisationPB,
            context.recombination,
            context.mutation,
            context.selection,
            context.neighbourhoodII
    );

    return algorithm.execute(instance);
}

Context parseArguments(int argc, char* argv[]) {
    // TODO : verify number of arguments at each step and return the error made in config
    Context context;

    context.setInputDirectory(argv[2]); // input directory path

    if (!(((string) argv[3]).compare("--ii"))) {

        context.setAlgorithm(II);
        context.setInitialisation(argv[4]); // --rand or --srz
        context.setPivoting(argv[5]); // --first or --best
        context.setNeighbourhoodII(argv[6]); // --tran or --ex or --in

    } else if (!(((string) argv[3]).compare("--vnd"))) {

        context.setAlgorithm(VND);
        context.setInitialisation(argv[4]); // --rand or --srz
        context.setPivoting(argv[5]); // --first or --best

        char* pivots[] = {argv[6], argv[7], argv[8]};
        context.setNeighbourhoodVND(pivots); // sequence of --tran/--ex/--in

    } else if (!(((string) argv[3]).compare("--tabu"))) {

        context.setAlgorithm(TABU);
        context.setInitialisation(argv[4]); // --rand or --srz
        context.setNeighbourhoodII(argv[5]); // --ex or --ins or --tran
        context.setTabuTenure(atoi(argv[6])); // integer for tabu tenure
        context.setMaxTime(atof(argv[7])); // double for max computation time

    } else if (!(((string) argv[3]).compare("--gen"))) {

        context.setAlgorithm(GEN);

        context.setInitialisationPB(argv[4]);
        context.setRecombination(argv[5]);
        context.setMutation(argv[6]);
        context.setSelection(argv[7]);

        context.setNeighbourhoodII(argv[8]);

        context.setPopulationSize(atoi(argv[9]));
        context.setMutationRate(atof(argv[10]));
        context.setMaxTime(atof(argv[11]));

    }

    return context;
}

vector<string> getInputFiles(Context context) {
    vector<string> files = vector<string>();

    for (const auto &entry: fs::directory_iterator(context.getPath())) {
        files.insert(files.end(), (string) entry.path());
    }

    sort(files.begin(), files.end());

    return files;
}

string buildOutputFileNameFromContext(Context context) {
    string fileName = "out/";

    switch (context.getAlgorithm()) {
        case II:
            fileName += "ii/ii";
            break;
        case VND:
            fileName += "vnd/vnd";
            break;
        case TABU:
            fileName += "tabu/tabu";
            break;
        case GEN:
            fileName += "gen/gen";
            break;
    }

    switch (context.getPivot()) {
        case BEST:
            fileName += "-best";
            break;
        case FIRST:
            fileName += "-first";
            break;
    }

    switch (context.getInitial()) {
        case RANDOM:
            fileName += "-rnd";
            break;
        case SIMPLE_RZ:
            fileName += "-srz";
            break;
    }

    for (int pivot : context.getNeighbourhoods()) {
        switch (pivot) {
            case TRANSPOSE:
                fileName += "-tran";
                break;
            case EXCHANGE:
                fileName += "-ex";
                break;
            case INSERT:
                fileName += "-ins";
                break;
        }
    }

    switch (context.getAlgorithm()) {
        case TABU:
            fileName += "-tenure-" + to_string(context.getTabuTenure());
            fileName += "-max_time-" + to_string((int) context.getMaxTime());
            break;
        case GEN:
            fileName += "-pop_size-" + to_string(context.getPopulationSize());
            fileName += "-mut_rate-" + to_string(context.getMutationRate());
            fileName += "-max_time-" + to_string((int) context.getMaxTime());
            break;
    }

    return fileName;
}