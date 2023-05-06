all: parts init pivots neighbours genetic context algo
	g++ -std=c++17 -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -std=c++17 -O3 \
		bin/flowshop.o bin/solution.o bin/context.o bin/pfspinstance.o \
		bin/random_permutation.o bin/simplified_rz.o \
		bin/first_improvement.o bin/best_improvement.o \
		bin/insert.o bin/exchange.o bin/transpose.o \
		bin/iterative_improvement.o bin/variable_neighbourhood_descent.o \
		bin/tabu_search.o bin/memetic_algorithm.o \
		bin/random_initialisation.o bin/random_exchange.o bin/rank_selection.o bin/utils.o \
		bin/rank_recombination.o bin/one_point_crossover.o \
		-o PFSP-WT
parts:
	g++ -std=c++17 -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -std=c++17 -O3 -c ./src/pfsp/pfspinstance.cpp -o bin/pfspinstance.o
init:
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/initialisation/random_permutation.cpp -o bin/random_permutation.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/initialisation/simplified_rz.cpp -o bin/simplified_rz.o
pivots:
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/neighbourhood/exchange.cpp -o bin/exchange.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/neighbourhood/insert.cpp -o bin/insert.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/neighbourhood/transpose.cpp -o bin/transpose.o
neighbours:
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/pivoting/best_improvement.cpp -o bin/best_improvement.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/pivoting/first_improvement.cpp -o bin/first_improvement.o
genetic:
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/initialisation/random_initialisation.cpp -o bin/random_initialisation.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/mutation/random_exchange.cpp -o bin/random_exchange.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/selection/rank_selection.cpp -o bin/rank_selection.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/utils.cpp -o bin/utils.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/recombination/rank_recombination.cpp -o bin/rank_recombination.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/genetic/recombination/crossovers/one_point_crossover.cpp -o bin/one_point_crossover.o
context:
	g++ -std=c++17 -O3 -c ./src/algorithm/config/context.cpp -o bin/context.o
	g++ -std=c++17 -O3 -c ./src/algorithm/solution.cpp -o bin/solution.o
algo:
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/iterative/iterative_improvement.cpp -o bin/iterative_improvement.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/vnd/variable_neighbourhood_descent.cpp -o bin/variable_neighbourhood_descent.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/tabu/tabu_search.cpp -o bin/tabu_search.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/genetic/memetic_algorithm.cpp -o bin/memetic_algorithm.o
run: all
	#./PFSP-WT 1 assets/instances/size-all --ii --rand --best --in
	#./PFSP-WT 1 assets/instances/size-all --vnd --srz --best --in --ex --tran
	#./PFSP-WT 1 assets/instances/size-all --tabu --srz --ex 20 5.0
	./PFSP-WT 1 assets/instances/size-all --gen --rand-init --rank-comb --rand-mut --rank-select --tran 100 0.5 30
clean:
	rm bin/*.o PFSP-WT