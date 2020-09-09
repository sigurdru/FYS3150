import os
import sys
import numpy as np
from formats import Table

def read(fname):
    with open(fname, 'r') as infile:
        line = infile.readline()
    time = line.split()[3]
    time = int(time)
    return time

path, N, I = sys.argv[1:]
N = int(N)
I = int(I)
means = np.zeros((N, 3))
algos = ['slow', 'fast', 'LU']
for i, algo in enumerate(algos):
    start = 1 if algo == 'LU' else 2
    for n in range(start, N+1):
        sum = 0
        for j in range(1, I+1):
            fname = os.path.join(path, algo + f'_{n}_{j}.txt')
            try:
                time = read(fname)
            except FileNotFoundError:
                time = 0
            finally:
                sum += time
        mean = sum/I
        means[n-1, i] = mean


tab = [['$n$', 'Slow', 'Fast', 'LU']] + [[f'$10^{{{i+1}}}$'] + ['-' if mean == 0 else f'{mean:.2f}' for mean in means[i]] for i in range(N)]

tab = Table(tab)
tab.write()
tab.latex(filename='../output/time_it_tex.txt')
