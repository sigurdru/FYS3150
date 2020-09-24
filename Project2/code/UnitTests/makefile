all: compile execute
compile:
	g++ -o test.exe -Wall main.cpp unit_test.cpp  jacobi.cpp -larmadillo -llapack -lblas
execute:
	./test.exe