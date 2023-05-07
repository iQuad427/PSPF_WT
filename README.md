# INFO-H413 - PFSP/WT - Implementation Exercises

## Description

This repository contains various algorithms to optimise the
Permutation Flow-Shop Scheduling Problem with Weighted Tardiness (PFSP-WT).
Those were implemented for the INFO-H413 - "Heuristic Optimization" course 
at the ULB.

Contact me at :
- quentin.roels@gmail.com

## Usage

They are two ways to execute the code :
- one algorithm experiment, by providing the specifications of the 
algorithm you want to run directly as argument in the command line
- all algorithm experiment, by running the ```execute.py``` python script

### One experiment

One experiment is defined as running one algorithm 5 times for each instance, and outputting
the result in a file named after the algorithm specifications. You can find the resulting file
in the ```out``` directory.


Usage : ```./PFSP-WT iter input_directory --algo [configuration]```
- II : ```[configuration] := --init --pivot --neighbour```
- VND : ```[configuration] := --init --pivot --neighbour-1 --neighbour-2 --neighbour-3```
- Tabu : ```[configuration] := --init --neighbour tabu-tenure max-time```
- Memetic : ```[configuration] := --init --comb --mut --select --neighbour pop-size mut-rate max-time```

Where :
- input_directory is the directory (relatively to the executable) containing the instances you want to run the algorithm 
specifications you gave as argument
- iter is the number of time the experiment should be done on each instance of the input_directory
- algo is the type of algorithm to run, and one of the following :
  - ii : iterative improvement algorithm (only one neighbourhood parameter)
  - vnd : variable neighbourhood descent algorithm (require three neighbourhood parameters)
- init is the initial solution construction method, and one of the following :
  - rnd : using random initialisation
  - srz : using simple RZ heuristic 
  - rand-init : generation of a population using random initialisation
- pivot is the way of determining the next position to explore :
  - first : chose the first improving solution
  - best : chose the best improving solution
- neighbour-1/-2/-3 is the rule to apply to create the next possible states
  - tran : transpose rule
  - in : insert rule
  - ex : exchange rule
  - _Note: the neighbourhood will be applied in the order in which hey were given_ 
- comb is the combination operator -> rank-comb
- mut is the mutation operator -> rand-mut
- select is the selection operator -> rank-select

Example : run 5 times on each instance a VND algorithm with simple RZ initialisation, best improvement, 
and use in order insert, exchange and transpose neighbourhood before stopping.

```bash
make # build
./PFSP-WT 5 assets/instances/size-all --vnd --srz --best --in --ex --tran
```
or run the example provided in the make file, comment the ones you don't need and use
```bash
make run
```


### Multiple experiments

Because of the amount of combination that must be tested, I used a Python script to automatically run all possible 
combinations.

```
python3 execute.py input_directory iterations --algorithm, ...
```

For example, to run the experiment for tabu search and memetic algorithm :

```bash
python3 execute.py asset/instances/size-all 5 --tabu --gen
```

> Note : I used the os library to run bash commands from a Python script, you might need to install it using 
> ```pip3 install os```


## Statistical tests

Most of the exercise was the statistical comparisons between each and every algorithm.
To this end I wrote multiple R scripts to compute and store statistical results in a
readable format. Most of the result can be found in the report related to this implementation exercise.

In ```src/statistics/implementation-1``` you will find the following scripts :
- ```statistic.R```contains a script to automatically parse all the output data of the ```execute.py``` script. 
Its output is one file per combination containing the average results (deviation to best-known solution + execution time) 
on the five runs, for all instances.
- ```ii_init.R``` was used to determine if one initialisation method had a significant impact on the result quality
- ```ii_statistics.R``` and ```vns_statistics.R``` helped me answer the questions of the exercise statement

In ```src/statistics/implementation-2``` you will find the following scripts :
- ```tabu_tenure.R``` was used to fond a good tabu tenure for the tabu search that was implemented
- ```pop_size.R``` was used to find a good value for the population size of the memetic algorithm
- ```mut_rate.R``` was used to find a good value for the mutation rate of the memetic algorithm
- ```correlation_plot.R``` was used to compute the statistics and correlation plots with the results of the experiments