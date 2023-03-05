all: program
	./flowshopWCT assets/instances/DD_Ta090.txt
program : src/pfsp/pfspinstance.h src/flowshop.cpp src/pfsp/pfspinstance.cpp

	g++ -O3 -c ./src/flowshop.cpp -o bin/flowshop.o
	g++ -O3 -c ./src/pfsp/pfspinstance.cpp -o bin/pfspinstance.o

	g++ -O3 -c ./src/algorithm/operators/initialisation/random_permutation.cpp -o bin/random_permutation.o
	g++ -O3 -c ./src/algorithm/operators/initialisation/simplified_rz.cpp -o bin/simplified_rz.o

	g++ -O3 -c ./src/algorithm/operators/pivoting/exchange.cpp -o bin/exchange.o
	g++ -O3 -c ./src/algorithm/operators/pivoting/insert.cpp -o bin/insert.o
	g++ -O3 -c ./src/algorithm/operators/pivoting/transpose.cpp -o bin/transpose.o

	g++ -O3 -c ./src/algorithm/operators/neighbourhood/best_improvement.cpp -o bin/best_improvement.o
	g++ -O3 -c ./src/algorithm/operators/neighbourhood/first_improvement.cpp -o bin/first_improvement.o

	g++ -O3 -c ./src/algorithm/implementation/iterative/iterative_improvement.cpp -o bin/iterative_improvement.o
	g++ -O3 -c ./src/algorithm/implementation/vnd/variable_neighbourhood_descent.cpp -o bin/variable_neighbourhood_descent.o

	g++ -O3 bin/flowshop.o bin/pfspinstance.o bin/iterative_improvement.o bin/variable_neighbourhood_descent.o -o flowshopWCT
clean:
	rm bin/*.o flowshopWCT
