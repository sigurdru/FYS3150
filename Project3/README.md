# FYS3150 Project 3
Sigurd Sørlie Rustad and Vegard Falmår.

The report Project3.pdf is found in the tex directory.

Code dependencies:
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy
    - matplotlib

# How to run the code
```
# move into the code directory
cd code

# compile the code
make compile
```
The code can now be run with the desired parameters and the results plotted with
```
bash run.sh input_file dt N solver_method beta
```
for example
```
bash run.sh earth_sun_circ 4 7 verlet 2
```
This will run a simulation of the Earth-Sun system with initial conditions that should give a circular orbit. The four last arguments specify
- dt = 10^(-4)
- N = 10^7
- solver method is velocity verlet
- distance dependence parameter beta is 2 (normal inverse square law of gravity)

The `run.sh` program can also be run with a single keyword to produce a bunch of the results in the report automatically, for instance
```
bash run.sh three_body
```
This will run the simulations of the three-body system with all three different masses of Jupiter and for several different values of dt. A complete list of possible keywords is
- "all" to produce all the results in the report except a full simulation of the entire solar system
- "solar_system" to run a full simulation of the entire solar system (takes some time)
- "circ" to run simulations of the Earth-Sun system with both euler and velocity verlet for a range of different values for dt
- "beta" to run simulations of the Earth-Sun system with five different values of beta
- "escape_vel" to run the code showing the Earth just escaping the gravitational pull of the Sun
- "three_body" to run the simulations of the three-body system with all three different masses of Jupiter and for several different values of dt
- "mercury" to run code that calculates the perihelion presession of Mercury

# Input files
The code is designed to read intial conditions from input files created by `create_init_cond.sh`. The raw data from NASA located in the `input/raw` directory should not be edited. In order to produce new initial conditions, edit `create_init_cond.sh` according to the instructions in the program file and run it with
```
bash create_init_cond.sh
```

The following input files are already prepared:
- "earth_sun_circ.txt", initial conditions for the Sun and the Earth that should make the Earth's orbit circular.
- "earth_sun_ellip.txt", initial conditions for the Sun and the Earth that should make the Earth's orbit elliptical.
- "earth_sun_escape.txt", initial conditions for the Sun and the Earth that should let the Earth escape the Sun's gravitational pull
- "three_body.txt", initial conditions for the Sun, the Earth and Jupiter
- "three_body10.txt", initial conditions for the Sun, the Earth and Jupiter with the mass of Jupiter multiplied with 10
- "three_body1000.txt", initial conditions for the Sun, the Earth and Jupiter with the mass of Jupiter multiplied with 1000
- "planets.txt", all the 10 bodies in our solar system (from Sun to Pluto)
- "all.txt", all the 10 bodies in our solar system plus various moons

# Visualizing the results with Ovito
Ovito can be used to visualize the results. In Ovito, open a trajectory file stored in `output/positions`. We intend the following settings:
- Skip column 1 containing names
- Read column 2 as "Particle types"
    - This will give different colors to stars, planets and moons and allow you to adjust their sizes separately
- Read columns 3-5 as xyz-positions

# Example run
The following runs will reproduce all the results in the report:
```
cd code
make compile
bash run.sh all
bash run.sh solar_system
```
