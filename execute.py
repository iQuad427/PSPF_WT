import os
import sys

algorithms = ["--ii", "--vnd", "--tabu"]
improvements = ["--best", "--first"]
initialisations = ["--rand", "--srz"]
modifications = ["--ex", "--in", "--tran"]

input_directory = "assets/instances"

if __name__ == '__main__':
    os.system("make")

    algo = sys.argv[1]
    if algo == "--ii":
        for init in initialisations:
            for improve in improvements:
                for modif in modifications:
                    command = f"./PFSP-WT {input_directory} --ii {init} {improve} {modif}"
                    print(command)
                    os.system(command)

    elif algo == "--vnd":
        for init in initialisations:
            for improve in improvements:
                command = f"./PFSP-WT {input_directory} --vnd {init} {improve} --tran --in --ex"
                print(command)
                os.system(command)

                command = f"./PFSP-WT {input_directory} --vnd {init} {improve} --tran --ex --in"
                print(command)
                os.system(command)

    elif algo == "--tabu":
        for init in initialisations:
            for modif in modifications:
                for tenure in range(10):
                    command = f"./PFSP-WT {input_directory} --tabu {init} {modif} {tenure} 3.0"
                    print(command)
                    os.system(command)
