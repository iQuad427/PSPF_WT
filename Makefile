all: program
	./flowshopWCT --spec assets/instances/ --ii --srz --best --in
	#./flowshopWCT --spec assets/instances/ --vnd --srz --best --in --ex --tran
program :
	g++ -std=c++17 -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -std=c++17 -O3 -c ./src/pfsp/pfspinstance.cpp -o bin/pfspinstance.o

	g++ -std=c++17 -O3 -c ./src/algorithm/operators/initialisation/random_permutation.cpp -o bin/random_permutation.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/initialisation/simplified_rz.cpp -o bin/simplified_rz.o

	g++ -std=c++17 -O3 -c ./src/algorithm/operators/pivoting/exchange.cpp -o bin/exchange.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/pivoting/insert.cpp -o bin/insert.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/pivoting/transpose.cpp -o bin/transpose.o

	g++ -std=c++17 -O3 -c ./src/algorithm/operators/neighbourhood/best_improvement.cpp -o bin/best_improvement.o
	g++ -std=c++17 -O3 -c ./src/algorithm/operators/neighbourhood/first_improvement.cpp -o bin/first_improvement.o

	g++ -std=c++17 -O3 -c ./src/algorithm/config/context.cpp -o bin/context.o
	g++ -std=c++17 -O3 -c ./src/algorithm/solution.cpp -o bin/solution.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/iterative/iterative_improvement.cpp -o bin/iterative_improvement.o
	g++ -std=c++17 -O3 -c ./src/algorithm/implementation/vnd/variable_neighbourhood_descent.cpp -o bin/variable_neighbourhood_descent.o


	g++ -std=c++17 -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -std=c++17 -O3 bin/flowshop.o bin/solution.o bin/random_permutation.o bin/simplified_rz.o bin/first_improvement.o bin/best_improvement.o bin/insert.o bin/exchange.o bin/transpose.o bin/context.o bin/pfspinstance.o bin/iterative_improvement.o bin/variable_neighbourhood_descent.o -o flowshopWCT
clean:
	rm bin/*.o flowshopWCT