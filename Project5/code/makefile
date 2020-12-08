compile:
	g++ -o main.exe -Wall main.cpp forward_euler.cpp backward_euler.cpp crank_nicolson.cpp solvers.cpp tridiag.cpp
run:
	./main.exe 1 2 6 CrankNicolson test

compile_test:
	g++ -o unit_test.exe -Wall unit_test.cpp tridiag.cpp forward_euler.cpp backward_euler.cpp crank_nicolson.cpp

run_test:
	./unit_test.exe

test: compile_test run_test
