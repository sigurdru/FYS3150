import matplotlib.pyplot as plt
import sys
import pandas as pd

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern')

n, fname = sys.argv[1:]
n = int(n)
h = 1/(n-1)
df = pd.read_csv(fname)
x = df['x'].values
comp = df['computed'].values
exact = df['exact'].values

fig, ax = plt.subplots()
ax.set_title(f'h = {h:.1e}')
ax.plot(x, comp, label='Computed')
ax.plot(x, exact, label='Exact')
ax.legend()
fig.tight_layout()
fig.savefig(f'../output/plot_{n}.pdf')
