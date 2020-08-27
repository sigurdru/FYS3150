all: compile execute

compile:
	g++ -o main.exe main.cpp lineq.cpp fast_lineq.cpp slow_lineq.cpp

compile_alternative:
	g++ -o main.exe $(wildcard *.cpp)

execute:
	./main.exe
