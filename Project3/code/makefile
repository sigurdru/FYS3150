compile:
	g++ -o main.exe -Wall main.cpp vec3.cpp solarsystem.cpp celestialbody.cpp euler.cpp verlet.cpp
test:
	make compile
	./main.exe circ_orbit_earth_sun.txt test 0.0001 100000 sun_earth_euler
