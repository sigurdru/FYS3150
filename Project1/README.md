# FYS3150 Project 1 
Sigurd Sørlie Rustad and Vegard Falmår.

The report Project1.pdf is found in the tex directory.

Code dependencies:
- C++
    - armadillo
- Python (runs with python version 3.6.9 and 3.8.2)
    - numpy
    - matplotlib
    - pandas

# How to run the code
Move into the code directory and compile the code:
```
cd code
make compile

# to compile the test code
make compile_test

# alternatively, to compile everything at once
make compile_all
```

Then, to produce all the results in the report, that is run the code for all n from 2 to 6, plot the results and make plots and tables of the errors, run:
```
bash run.sh all
```

The code can be run with step size h = 10^(-n):
```
bash run.sh slow n      # with the slow, general algorithm
bash run.sh fast n      # with the fast, specialized algorithm
bash run.sh LU n        # with the LU decomposition algorithm
```
This will write the results to file and plot them.

To run the test code described in the report, simply run the following command after compiling:
```
bash test.sh
```
If the test fails for either the fast or the slow algorithm, python error messages will be printed to the terminal.

To time the code and produce a table of the results, run
```
bash time_it.sh
```
This will run the code 5 times for all values of h, and compute the mean time. A table of results is printed to the terminal and saved to file in the output folder.

# Example run
```
cd code
make compile_all
bash test.sh            # runs the test code
bash time_it.sh         # times the code, average over 5 runs
bash run.sh fast 7      # runs the fast algorithm with h = 10^(-7)
bash run.sh all         # produces all the results
```
