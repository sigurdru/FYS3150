import os
import matplotlib.pyplot as plt
from formats import Table
import sys

plt.style.use('seaborn')
# plt.rc('text', usetex=True)
# plt.rc('font', family='Computer Modern')

algo = sys.argv[1]
msg = 'Algoritm must be "fast" or "slow"'
assert ((algo == 'fast') or (algo == 'slow')), msg

path = '../output/'

tab = [[r'$\log_{10}(h)$', r'$\eps$']]
d = {}

def read(fname):
    with open(fname, 'r') as infile:
        line = infile.readline()
    num = float(line)
    return num

for root, dirs, files in os.walk(path):
    for fname in files:
        if (fname[0:4] == algo) and (fname[-9:] == 'error.txt'):
            n = int(fname[5])
            error = read(os.path.join(path, fname))
            d[-n] = error

for key in sorted(d):
    error = d[key]
    tab.append([f'{key:d}', f'{error:.2f}'])

fname = path + algo + '_errors'
tab = Table(tab)
tab.write()
tab.latex(fname + '_tex.txt')

fig, ax = plt.subplots()
ax.plot(d.keys(), d.values(), 'o')
ax.set_xlabel(r'$\log_{10}(h)$')
ax.set_ylabel(r'$\epsilon$')
fig.savefig(fname + '.pdf')
