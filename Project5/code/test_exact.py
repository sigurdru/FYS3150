import numpy as np
import matplotlib.pyplot as plt
from plot import Exact1D

L = 1.0
exact = Exact1D(200, L)
x = np.linspace(0, 1, 101)
y = exact(x, 0)
fig, ax = plt.subplots()
ax.plot(x, y)
fig.savefig('../output/test_analytic.pdf')
