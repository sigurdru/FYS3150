compile:
	g++ -o main.exe -Wall main.cpp metropolis.cpp -fopenmp

run:
	./main.exe 2 1 0.1 50 100000 true false test 8

leak-check:
	valgrind --leak-check=yes ./main.exe
