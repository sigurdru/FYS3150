import matplotlib.pyplot as plt
import numpy as np
import sys

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern')

n, fname = sys.argv[1:]
n = int(n)
x = np.zeros(n)
comp = np.zeros(n)
exact = np.zeros(n)
with open(fname, 'r') as infile:
    header = infile.readline()
    h = float(header)
    for i, line in enumerate(infile):
        x_val, c, e = [float(num) for num in line.split()]
        x[i] = x_val
        comp[i] = c
        exact[i] = e

fig, ax = plt.subplots()
ax.set_title(f'h = {h:.1e}')
ax.plot(x, comp, label='Computed')
ax.plot(x, exact, label='Exact')
ax.legend()
fig.tight_layout()
fig.savefig(f'../Project1/output/plot_{n}.pdf')
