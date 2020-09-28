compile:
	g++ -o main.exe -Wall main.cpp jacobi.cpp qm.cpp -larmadillo -llapack -lblas

test: compile_unittest run_test

compile_unittest:
	g++ -o unit_test.exe -Wall jacobi.cpp unit_test.cpp -larmadillo -llapack -lblas

run_test:
	./unit_test.exe
