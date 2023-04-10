import os

algorithms = ["--ii", "--vnd"]
improvements = ["--best", "--first"]
initialisations = ["--rand", "--srz"]
modifications = ["--tran", "--ex", "--in"]

input_directory = "assets/instances"

if __name__ == '__main__':
    os.system("make")

    for algo in algorithms:
        if algo == "--ii":
            for init in initialisations:
                for improve in improvements:
                    for modif in modifications:
                        command = f"./PFSP-WT {input_directory} --ii {init} {improve} {modif}"
                        print(command)
                        os.system(command)

        if algo == "--vnd":
            for init in initialisations:
                for improve in improvements:
                    command = f"./PFSP-WT {input_directory} --vnd {init} {improve} --tran --in --ex"
                    print(command)
                    os.system(command)

                    command = f"./PFSP-WT {input_directory} --vnd {init} {improve} --tran --ex --in"
                    print(command)
                    os.system(command)
