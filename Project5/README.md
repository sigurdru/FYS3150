# FYS3150 Project 5
Sigurd Sørlie Rustad and Vegard Falmår.

*Edit 25.12.2020:* We deleted two lines of code in `code/produce_results.py`.
The lines were added at the very end of the project to time the code for large
grids with many time steps and should have been deleted for the final delivery.
Running the code with these parameters would have taken some time, and the
results in the report are with smaller grids. The changes were cleared with the
professor beforehand.

The report Project5.pdf is found in the tex directory.

Code dependencies:
- C++
    - Catch2
    - OpenMP
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy, 1.19.4
    - matplotlib, 3.3.1
    - pandas, 1.1.4

## How to run the code
```
# move into the code directory
cd code

# compile the code
make compile
```

The code is now run by calling the program `run.py`. The arguments are handled
by the `argparse` module and directions will be printed to the terminal by
running the program with the `-h` flag (or `--help`):
```
python3 run.py -h
```

Notably, the `-r` flag (or `--results`) is for producing the results in the
report (both calculation and plotting):
```
python3 run.py -r 1D    # for the results to the 1D equation
python3 run.py -r 2D    # for the results to the 2D equation

# and equivalent to running both the above commands one after the other
python3 run.py -r all   # to produce all the results in the report
```

**Note:** Running `run.py` with the `-r` flag will ignore all others except for
the `-Nc` (`--num-cores`) flag.

### Code tests
All code tests are implemented in the program `unit_test.cpp`. They can be
compiled and run with one command:
```
make test
```
Running
```
make test_memory
```
will run the tests while simultaniously checking for memory leaks using
Valgrind. Note that the parallelization with OpenMP causes Valgrind to mark
some memory as potentially lost because OpenMP leaves some allocated memory to
be dealt with by the system garbage collector. Disabling the parallelization
by for example commenting out the two lines containing
```
omp_set_num_threads(numCores); // set number of threads in parallel
...
#pragma omp parallel for
```
in the `TwoDimensions::Solve` method in `two_dimensions.cpp` will cause this
warning to disappear.

### Example run
The following will reproduce all the results in the report:
```
cd code
make compile
python3 run.py -r all

# to run a specific calulation, for example
python3 run.py -Nx 100 -Nt 2000 -dt 0.0003 -m CrankNicolson
```
