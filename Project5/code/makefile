compile:
	g++ -o main.exe -Wall main.cpp forward_euler.cpp 
run:
	./main.exe 100 100 0.01 ForwardEuler

compile_test:
	g++ -o unit_test.exe -Wall unit_test.cpp tridiag.cpp forward_euler.cpp backward_euler.cpp crank_nicolson.cpp

run_test:
	./unit_test.exe

test: compile_test run_test
