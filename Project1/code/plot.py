import matplotlib.pyplot as plt
import sys
import pandas as pd

plt.style.use('seaborn')
# plt.rc('text', usetex=True)
# plt.rc('font', family='Computer Modern')

exp, fname = sys.argv[1:]
exp = int(exp)
n = 10**exp + 1
h = 1/(n-1)
df = pd.read_csv(fname + '.txt')
x = df['x'].values
comp = df['computed'].values
exact = df['exact'].values

fig, ax = plt.subplots()
title = f'$h = {h:.1e}'.replace('1.0e', r'10^{') + '}$'
title = title.replace('-0', '-')
ax.set_title(title)
ax.plot(x, comp, label='Computed')
ax.plot(x, exact, ':', label='Exact')
ax.legend()
fig.tight_layout()
fig.savefig(fname + '.pdf')
