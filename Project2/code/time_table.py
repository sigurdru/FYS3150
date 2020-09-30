import os
import numpy as np
from formats import Table

def read(fname):
    times = []
    iters = []
    with open(fname, 'r') as infile:
        for i, line in enumerate(infile):
            if i%2 == 0:
                times.append(int(line))
            else:
                iters.append(int(line))
    return np.mean(times), np.mean(iters)

path = '../output/'
tab = [['N', 'BB', 'QM1', 'QM2']]
ns = []
data = {}
for method in tab[0][1:]:
    data[method] = {}

for root, dirs, fnames in os.walk(path):
    for fname in fnames:
        if 'time_' in fname:
            time, iters = read(path + fname)
            _, method, n = fname.replace('.txt', '').split('_')
            data[method][n] = (time, iters)
            n = int(n)
            if n not in ns:
                ns.append(n)

for n in sorted(ns):
    n = str(n)
    tab.append([n] + [f'{data[m][n][0]:.0f} ms' for m in tab[0][1:]])
table = Table(tab)
print('\nComputing time:')
table.write()
table.latex(filename='../output/table_time.txt', complete=False)

tab = [tab[0]]
for n in sorted(ns):
    n = str(n)
    tab.append([n] + [f'{data[m][n][1]:.0f}' for m in tab[0][1:]])
table = Table(tab)
print('\nIterations:')
table.write()
table.latex(filename='../output/table_iters.txt', complete=False)
