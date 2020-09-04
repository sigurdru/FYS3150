# FYS3150 Project 1

Sigurd Sørlie Rustad and Vegard Falmår.

The report Project1.pdf is found in the tex directory.

Code dependencies:
- C++
    - something
- Python
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

Now the code can be run with step size h = 10^(-n):
```
bash run.sh slow n      # with the slow, general algorithm
bash run.sh fast n      # with the fast, specialized algorithm
```
This will write the results to file and plot them.

To produce all the results in the report, that is run the code for all n from 2 to 6, plot the results and make plots and tables of the errors, run:
```
bash run.sh all
```

To run the test code described in the report, simply run the following command after compiling:
```
bash test.sh
```
If the test fails for either the fast or the slow algorithm, python error messages will be printed to the terminal.

# Example run
```
cd code
make compile_all
bash run.sh fast 2      # runs the fast algorithm with h = 0.01
bash test.sh            # runs the test code
bash run.sh all         # produces all the results
```
