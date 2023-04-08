all: parts init pivots neighbours context algo
	g++ -std=c++17 -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -std=c++17 -O3 \
		bin/flowshop.o bin/solution.o bin/context.o bin/pfspinstance.o \
		bin/random_permutation.o bin/simplified_rz.o \
		bin/first_improvement.o bin/best_improvement.o \
		bin/insert.o bin/exchange.o bin/transpose.o \
		bin/iterative_improvement.o bin/variable_neighbourhood_descent.o \
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
context:
	g++ -std=c++17 -O3 -c ./src/algorithm/config/context.cpp -o bin/context.o
	g++ -std=c++17 -O3 -c ./src/algorithm/solution.cpp -o bin/solution.o
algo:
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/iterative/iterative_improvement.cpp -o bin/iterative_improvement.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/vnd/variable_neighbourhood_descent.cpp -o bin/variable_neighbourhood_descent.o
run: all
	./PFSP-WT assets/instances/ --ii --rand --best --in
	#./PFSP-WT assets/instances/ --vnd --srz --best --in --ex --tran
clean:
	rm bin/*.o PFSP-WT