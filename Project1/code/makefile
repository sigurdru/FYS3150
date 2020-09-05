compile_all: compile compile_test

compile:
	g++ -o main.exe -Wall main.cpp lineq.cpp fast_lineq.cpp slow_lineq.cpp

compile_test:
	g++ -o test_lineq.exe -Wall main.cpp lineq.cpp fast_lineq.cpp slow_lineq.cpp lu_lineq.cpp -larmadillo -llapack -lblas
