import numpy as np
import matplotlib.pyplot as plt
from plot import read_data

df = read_data('test2D')
fig, axes = plt.subplots(ncols=2)
Nx = 100
x = np.linspace(0, 1, Nx+1)
X, Y = np.meshgrid(x, x)
Nt = 1_000
for i in range(2):
    row = df.loc[i*Nx/4].to_numpy()
    t = row[0]
    temp = row[1:]
    temp = temp.reshape(Nx+1, Nx+1)
    ax = axes[i]
    step = 10
    ax.contourf(X[::step], Y[::step], temp[::step])
fig.savefig('../output/test2Dplot.pdf')
