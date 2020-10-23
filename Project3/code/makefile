compile:
	g++ -o main.exe -Wall main.cpp vec3.cpp solarsystem.cpp celestialbody.cpp euler.cpp verlet.cpp
test:
	make compile
	./main.exe planets.txt output 0.0001 10000000 verlet
