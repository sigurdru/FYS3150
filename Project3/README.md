# FYS3150 Project 3
Sigurd Sørlie Rustad and Vegard Falmår.

The report Project2.pdf is found in the tex directory.

Code dependencies:
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy
    - matplotlib

# How to run the code
```
# move into the code directory
cd code

# compile the code with
make compile
```

# Input parameters
The code is designed to run with input files created by `create_init_cond.sh`. The raw data from NASA located in the `input/raw` directory should not be edited. In order to produce initial new initial conditions, edit `create_init_cond.sh` according to the instructions in the program file and run it with
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
