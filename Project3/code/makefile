compile:
	g++ -o main.exe -Wall main.cpp vec3.cpp solarsystem.cpp celestialbody.cpp euler.cpp verlet.cpp
test:
	make compile
	./main.exe earth_sun.txt output 0.001 1000
