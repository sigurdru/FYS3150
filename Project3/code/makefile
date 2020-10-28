compile:
	g++ -o main.exe -Wall main.cpp vec3.cpp solarsystem.cpp celestialbody.cpp euler.cpp verlet.cpp

test:
	make compile
	./main.exe circ_orbit_earth_sun.txt test 0.0001 100000 sun_earth_euler

test2:
	make compile
	./main.exe circ_orbit_earth_sun.txt test 0.000000000001 10000000000000 sun_earth_verlet

test3:
	make compile
	./main.exe planets.txt output 0.000001 1000000 verlet
merc:
	make compile
	./main.exe mercury_relativistic 0.00001 10000000 mercury 2

plot:
	python3 plot.py mercury_relativistic-mercury-0.01-10000-2 2D