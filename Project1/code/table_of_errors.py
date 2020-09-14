import os
import matplotlib.pyplot as plt
from formats import Table
import sys

plt.style.use('seaborn')
# plt.rc('text', usetex=True)
# plt.rc('font', family='Computer Modern')

algo = sys.argv[1]
msg = 'Algoritm must be "fast", "slow" og "LU"'
assert ((algo == 'fast') or (algo == 'slow') or (algo == 'LU')), msg

path = '../output/'

tab = [[r'$\log_{10}(h)$', r'$\epsilon$']]
d = {}

def read(fname):
    with open(fname, 'r') as infile:
        line = infile.readline()
    num = float(line)
    return num

for root, dirs, files in os.walk(path):
    for fname in files:
        if (fname[0:len(algo)] == algo) and (fname[-9:] == 'error.txt'):
            n = int(fname[len(algo) + 1])
            error = read(os.path.join(path, fname))
            d[-n] = error

for key in sorted(d):
    error = d[key]
    tab.append([f'{key:d}', f'{error:.2f}'])

fname = path + algo + '_errors'
tab = Table(tab)
tab.write()
tab.latex(fname + '_tex.txt', complete=False)

fig, ax = plt.subplots()
x = list(d.keys())
y = list(d.values())
ax.set_title(f'Relative errors for the {algo} algorithm', fontsize=20)
ax.plot(x, y, 'o')
ax.set_xlabel(r'$\log_{10}(h)$', fontsize=20)
ax.set_ylabel(r'$\epsilon$', fontsize=20)
ax.tick_params(axis='both', which='major', labelsize=15)
fig.tight_layout()
fig.savefig(fname + '.pdf')
