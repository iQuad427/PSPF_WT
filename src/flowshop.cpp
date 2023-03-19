#include <iostream>
#include <fstream>
#include <filesystem>

#include "algorithm/config/context.h"
#include "algorithm/operators/operators.h"

using namespace std;
namespace fs = std::filesystem;

int executeInstance(string config, char* path);
bool solutionIsValid(State solution, PfspInstance& instance);
State executeVariableNeighbourhoodDescent(PfspInstance& instance);
State executeIterativeImprovement(PfspInstance& instance);

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


State executeVariableNeighbourhoodDescent(PfspInstance& instance) {
    VariableNeighbourhoodDescent algorithm;
    vector<State (*) (State, int, int)> stateModifications;

    stateModifications.insert(stateModifications.begin(), transpose);
    stateModifications.insert(stateModifications.begin(), insert);
    stateModifications.insert(stateModifications.begin(), exchange);

    algorithm.configure(
            simplifiedRzHeuristic,
            firstImprovement,
            stateModifications
    );

    return algorithm.execute(instance);

}

State executeIterativeImprovement(PfspInstance& instance) {
    IterativeImprovement algorithm;

    algorithm.configure(
            simplifiedRzHeuristic,
            firstImprovement,
            insert
    );

    return algorithm.execute(instance);

}


Context parseArguments(int argc, char* argv[]) {
    Context context;

    // Configuration "--all", only require input directory
    if (!(((string) argv[1]).compare("--all"))) {
        context.setAlgorithm("all")
        context.setInputDirectory(argv[2]);
        return context;
    }

    // Configuration "--spec", only require input directory
    if (!(((string) argv[1]).compare("--spec"))) {
        context.setInputDirectory(argv[2]); // input directory path

        if (!(((string) argv[3]).compare("--ii"))) {

            context.setAlgorithm("ii")
            context.setInitialisation(argv[3]); // --rand or --srz
            context.setNeighbourhood(argv[4]); // --first or --best
            context.setPivotingII(argv[5]); // --tran or --ex or --in

        } else if (!(((string) argv[1]).compare("--vnd"))) {

            context.setAlgorithm("vnd")
            context.setInitialisation(argv[3]); // --rand or --srz
            context.setNeighbourhood(argv[4]); // --first or --best

            char* pivots[] = {argv[5], argv[6], argv[7]};
            context.setPivotingVND(pivots); // sequence of --tran/--ex/--in
        }
    }
    return context;
}


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

    vector<string> files = vector<string>();

    for (const auto &entry: fs::directory_iterator(context.getPath())) {
        files.insert(files.end(), (string) entry.path());
    }

    sort(files.begin(), files.end());

    ofstream myfile;
    myfile.open ("../out/example.txt");
    myfile << "Writing this to a file.\n";


    for (string filePath : files) {
        cout << filePath << endl;

        char* char_array = new char[filePath.length() + 1];
        strcpy(char_array, filePath.c_str());

        executeInstance(argv[1], char_array);
    }

    myfile.close();
}

int executeInstance(Context config, char* path) {
    /* initialize random seed: */
    srand(time(NULL));

    /* Create instance object */
    PfspInstance instance;

    /* Read data from file */
    if (!instance.readDataFromFile(path))
        return 1;

    State solution;
    if (!(config.getAlgorithm().compare("--vnd"))) {
        solution = executeVariableNeighbourhoodDescent(instance);
    } else if (!(config.compare("--ii"))) {
        solution = executeIterativeImprovement(instance);
    } else {
        cout << "Error: wrong config parameter, " << config << endl;
        return 1;
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
    long int WeightedSumCompletionTimes = instance.computeWCT(solution);
    long int WeightedTardiness = instance.computeWT(solution);
    cout << "Total weighted completion time: " << WeightedSumCompletionTimes << endl;
    cout << "Total weighted tardiness: " << WeightedTardiness << endl;

    return 0;
}
