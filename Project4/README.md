# FYS3150 Project 4
Sigurd Sørlie Rustad and Vegard Falmår.

The report Project4.pdf is found in the tex directory.

Code dependencies:
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy, 1.19.4
    - matplotlib, 3.3.1
    - pandas, 1.1.4
    - scipy, 1.3.1

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

Notably, the `-t` flag (or `--task`) is for producing the results (both
simulation and plotting) for a specific task:
```
python3 run.py -t c     # for the results of task c
python3 run.py -t de    # for the results of tasks d and e
python3 run.py -t f     # for the results of task f (takes a few hours)

# and equivalent to running all three above one after the other
python3 run.py -t all   # to produce all the results in the report
```

### Example run
The following will reproduce all the results in the report:
```
cd code
make compile
python3 run.py -t all
```
