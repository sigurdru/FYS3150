compile:
	g++ -o main.exe -Wall main.cpp forward_euler.cpp backward_euler.cpp crank_nicolson.cpp solvers.cpp tridiag.cpp two_dimensions.cpp -fopenmp
# Her ser du eksempler på hvordan man kjører koden
runcn:
	python3 run.py -Nx 2 -Nt 5 -dt 6 -m CrankNicolson
runall:
	python3 run.py -Nx 2 -Nt 5 -dt 6 -m all
#

compile_test:
	g++ -o unit_test.exe -Wall unit_test.cpp tridiag.cpp solvers.cpp forward_euler.cpp backward_euler.cpp crank_nicolson.cpp two_dimensions.cpp -fopenmp

run_test:
	./unit_test.exe

run_test_memory:
	valgrind --leak-check=yes ./unit_test.exe

test: compile_test run_test
test_memory: compile_test run_test_memory

compile_2DV:
	g++ -o main2D.exe -Wall main2D.cpp solvers.cpp two_dimensions.cpp -fopenmp

run_2DV:
	./main2D.exe

all_2DV: compile_2DV run_2DV
