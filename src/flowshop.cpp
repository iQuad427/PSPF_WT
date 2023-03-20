#include <iostream>
#include <fstream>
#include <filesystem>

#include "algorithm/config/context.h"
#include "algorithm/operators/operators.h"

using namespace std;
namespace fs = std::filesystem;

Solution executeInstance(Context context, char* path);
bool solutionIsValid(State solution, PfspInstance& instance);
State executeVariableNeighbourhoodDescent(PfspInstance& instance, Context context);
State executeIterativeImprovement(PfspInstance& instance, Context context);
Context parseArguments(int argc, char* argv[]);
vector<string> getInputFiles(Context context);
string buildOutputFileNameFromContext(Context context);
void launchExperiment(Context context, vector<string>);
void retrieveOperators();

vector<vector<int> (*) (PfspInstance&)> stateGenerations;
vector<vector<int> (*) (vector<int>, vector<int> (*) (vector<int>, int, int), PfspInstance&)> stateImprovements;
vector<vector<int> (*) (vector<int>, int, int)> stateModifications;

int main(int argc, char *argv[]) {
    /*
     * TODO : implement Context variable to save the parameters of the execution
     * Arguments :
     *  - execution type :
     *      - "--all" : benchmark, do every combination, every instances, save everything
     *      - "--spec" : specific configuration
     *  - input (directory containing the instances on which execute the algorithm)
     *      - will execute on all files of the input (sorted in alphabetical order)
     *      - output per algorithm combination on independent data files
     *      - output per size of instances
     *  - algorithm (either iterative improvement or variable neighbourhood descent)
     *      - initialisation
     *      - neighbourhood
     *      - pivoting
     *      - NOTE : possibility to run every combination in the same run
     *
     * Output file name :
     *  - ii-initialisation-neighbourhood-pivoting-instance_size.dat
     *  - vnd-initialisation-neighbourhood-pivoting_order-instance_size.dat
     *      example : ii-random-first-exchange-20_50.dat
     *      example : vnd-random-first-transpose_exchange_insert-20_50.dat
     *
     * Output file format :
     *  - Instance name
     *  - Best score found for the instance
     *  - The solution?
     */
    Context context = parseArguments(argc, argv);
    vector<string> files = getInputFiles(context);

    launchExperiment(context, files);
}

void launchExperiment(Context context, vector<string> files) {
    switch (context.getAlgorithm()) {
        case ALL: {
            cout << "Experiment: Executing ALL Combinations" << endl;
            retrieveOperators();
            Context subContext;

            for (auto generate : stateGenerations) {
                for (auto improve : stateImprovements) {
                    for (auto modify : stateModifications) {
                        continue;
                    }
                }
            }

            // TODO: loop through all operators and create new context each time,
            //  then call launchExperiment on each of those new contexts

            return;
        }
        case II:
        case VND: {
            // TODO: save experiment results in a file (I created a pseudo code hereunder)
            cout << "Experiment: " << buildOutputFileNameFromContext(context) << endl;

            string fileName = buildOutputFileNameFromContext(context);
            cout << "File Name: " << fileName << endl;

            ofstream resultFile;
            resultFile.open(fileName);
            resultFile << "Writing this to a file.\n";

            for (string filePath: files) {
                char *path = new char[filePath.length() + 1];
                strcpy(path, filePath.c_str());

                Solution solution = executeInstance(context, path);

                // TODO: find a way to stringify the solution object
                resultFile << solution.toString() << "\n";

                // TODO: going face a problem since we must execute each algo a certain number of time
                //  but I was expecting both the best known and result files to have the same format
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

    /* initialize random seed: */
    srand(time(NULL));

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
    } else {
        cout << "Error: wrong context parameter, " << context.getAlgorithm() << endl;
        throw;
    }

    cout << "Solution: ";
    for (int i = 1; i <= instance.getNbJob(); ++i)
        cout << solution[i] << " ";
    cout << endl;

    if (solutionIsValid(solution, instance)) {
        cout << "solution is valid" << endl;
    } else {
        cout << "solution is not valid" << endl;
    }

    /* Compute the WCT of this solution */
    long int weightedSumCompletionTimes = instance.computeWCT(solution);
    long int weightedTardiness = instance.computeWT(solution);
    cout << "Total weighted completion time: " << weightedSumCompletionTimes << endl;
    cout << "Total weighted tardiness: " << weightedTardiness << endl;

    return Solution(path, weightedTardiness);
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
            context.neighbourhood,
            context.pivotingVND
    );

    return algorithm.execute(instance);
}

State executeIterativeImprovement(PfspInstance& instance, Context context) {
    IterativeImprovement algorithm;

    algorithm.configure(
            context.initialisation,
            context.neighbourhood,
            context.pivotingII
    );

    return algorithm.execute(instance);
}

Context parseArguments(int argc, char* argv[]) {
    Context context;

    // Configuration "--all", only require input directory
    if (!(((string) argv[1]).compare("--all"))) {
        context.setAlgorithm(ALL);
        context.setInputDirectory(argv[2]);
        return context;
    }

    // Configuration "--spec", only require input directory
    if (!(((string) argv[1]).compare("--spec"))) {
        context.setInputDirectory(argv[2]); // input directory path

        if (!(((string) argv[3]).compare("--ii"))) {

            context.setAlgorithm(II);
            context.setInitialisation(argv[4]); // --rand or --srz
            context.setNeighbourhood(argv[5]); // --first or --best
            context.setPivotingII(argv[6]); // --tran or --ex or --in

        } else if (!(((string) argv[3]).compare("--vnd"))) {

            context.setAlgorithm(VND);
            context.setInitialisation(argv[4]); // --rand or --srz
            context.setNeighbourhood(argv[5]); // --first or --best

            char* pivots[] = {argv[6], argv[7], argv[8]};
            context.setPivotingVND(pivots); // sequence of --tran/--ex/--in
        }
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

    cout << "algo: " << context.getAlgorithm() << endl;
    switch (context.getAlgorithm()) {
        case II:
            fileName += "ii/ii";
            break;
        case VND:
            fileName += "vnd/vnd";
            break;
    }
    cout << "neighbour: " << context.getNeighbour() << endl;
    switch (context.getNeighbour()) {
        case BEST:
            fileName += "-best";
            break;
        case FIRST:
            fileName += "-first";
            break;
    }
    cout << "initial: " << context.getInitial() << endl;
    switch (context.getInitial()) {
        case RANDOM:
            fileName += "-rnd";
            break;
        case SIMPLE_RZ:
            fileName += "-srz";
            break;
    }

    for (int pivot : context.getPivots()) {
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
    return fileName;
}

void retrieveOperators() {
    stateModifications.insert(stateModifications.end(), transpose);
    stateModifications.insert(stateModifications.end(), exchange);
    stateModifications.insert(stateModifications.end(), insert);

    stateImprovements.insert(stateImprovements.end(), bestImprovement);
    stateImprovements.insert(stateImprovements.end(), firstImprovement);

    stateGenerations.insert(stateGenerations.end(), randomPermutation);
    stateGenerations.insert(stateGenerations.end(), simplifiedRzHeuristic);
}
