import os
import sys

algorithms = ["--ii", "--vnd", "--tabu"]
improvements = ["--best", "--first"]
initialisations = ["--rand", "--srz"]
modifications = ["--ex", "--in", "--tran"]

input_directory = "assets/instances/size-all"

if __name__ == '__main__':
    os.system("make")

    input_directory = sys.argv[1]
    iteration = sys.argv[2]

    print(input_directory, iteration)

    for arg in sys.argv[3:]:
        algo = arg
        if algo == "--ii":
            for init in initialisations:
                for improve in improvements:
                    for modif in modifications:
                        command = f"./PFSP-WT {iteration} {input_directory} --ii {init} {improve} {modif}"
                        print(command)
                        os.system(command)

        if algo == "--vnd":
            for init in initialisations:
                for improve in improvements:
                    command = f"./PFSP-WT {iteration} {input_directory} --vnd {init} {improve} --tran --in --ex"
                    print(command)
                    os.system(command)

                    command = f"./PFSP-WT {iteration} {input_directory} --vnd {init} {improve} --tran --ex --in"
                    print(command)
                    os.system(command)

        elif algo == "--tabu":
            command = f"./PFSP-WT {iteration} {input_directory} --tabu --rand --ex 100 60"
            print(command)
            os.system(command)

        elif algo == "--gen":
            command = f"./PFSP-WT {iteration} {input_directory} --gen --rand-init --rank-comb --rand-mut --rank-select --ex 100 0.7 60"
            print(command)
            os.system(command)
