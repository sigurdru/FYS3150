compile_all: compile

compile:
	g++ -o main.exe -Wall main.cpp jacobi.cpp -larmadillo -llapack -lblas

compile_unittest:
	g++ -o unit_test.exe -Wall unittest_main.cpp jacobi.cpp unit_test.cpp -larmadillo -llapack -lblas