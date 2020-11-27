compile:
	g++ -o main.exe -Wall main.cpp metropolis.cpp -fopenmp

run:
	./main.exe 40 2 0.05 7 100000 true false test

leak-check:
	valgrind --leak-check=yes ./main.exe
