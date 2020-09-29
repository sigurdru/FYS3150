# FYS3150 Project 2
Sigurd Sørlie Rustad and Vegard Falmår.

The report Project2.pdf is found in the tex directory.

Code dependencies:
- C++
    - armadillo
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy
    - matplotlib
    - pandas

# How to run the code
```
# move into the code directory
cd code

# to compile and run the test code
make test

# to compile the main code
make compile
```

Then, to produce all the results in the report, that is run the code and plot for all n, all the different equations and all different values of omega_r, run:
```
bash run.sh all
```

The code can be run with n+1 grid points with:
```
bash run.sh n BB            # buckling beam
bash run.sh n QM1           # quantum mechanics with one electron
bash run.sh n QM2 omega_r   # QM with two electrons and omega_r
```
This will write the results to file and plot them.

To time the code and produce a table of the results, run
```
bash run.sh time
```
This will run the code 3-5 times for all equations and values of n, and compute the mean time. A table of results is printed to the terminal and saved to file in the output folder.

# Example run
```
cd code
make test           # runs the test code
make compile        # compile
bash run.sh time    # times the code, average over 5 runs
bash run.sh all     # produces all the results
```
