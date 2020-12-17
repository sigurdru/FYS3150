import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from numba import jit
import sys, os

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')
path = '../output/'
path_plots = '../output/plots'

L = 1.0
colors = [
    '#ff5733',
    '#ffb533',
    '#73f939',
    '#4285f3',
    '#c669f1',
    '#fa477d'
]

def read_data(fname):
    """
    Args:
        fname (str): name of file containing the desired data

    Returns:
        df (pandas.DataFrame): the calculated values

    """
    df = pd.read_csv(os.path.join(path, fname + '.csv'), header=None)
    return df

def plot_evolution(params, fname):
    """The function plots and saves the figure

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    N_fourier = 200
    df = read_data(fname)
    NumRows = len(df.loc[:,0])
    NumCols = len(df.loc[0,:])
    xa = np.linspace(0, L, NumCols-1)
    exact = Exact1D(N_fourier, 1.0)
    fig, ax = plt.subplots()
    title = f'{params.method}, ' + r'$N_x = 10^{' + f'{params.Nx}' + r'}$'
    title += r', $\Delta t = 10^{-' + f'{params.dt}' + r'}$'
    title += f'\n{N_fourier} Fourier addends'
    for i in range(NumRows):
        t = df.loc[i, 0]
        analytical = exact(xa, t)
        color = colors[i]
        label = f'$t = {t:.3f}$'
        linestyle = '-o' if params.Nx <= 1 else '-'
        ax.plot(xa, df.loc[i, 1:], linestyle, color=color, label=label)
        ax.plot(xa, analytical, linestyle='--', color=color)
    xlabel = '$x$'
    ylabel = '$u(x, t)$'
    set_ax_info(ax, title, xlabel, ylabel)
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))

def set_ax_info(ax, title, xlabel, ylabel):
    """Write title and labels on an axis with the correct fontsizes.

    Args:
        ax (matplotlib.axis): the axis on which to display information
        title (str): the desired title on the axis
        xlabel (str): the desired lab on the x-axis
        ylabel (str): the desired lab on the y-axis

    """
    ax.set_title(title, fontsize=20)
    ax.legend(fontsize=15)
    ax.set_xlabel(xlabel, fontsize=20)
    ax.set_ylabel(ylabel, fontsize=20)
    ax.tick_params(axis='both', which='major', labelsize=15)

class Exact1D:
    def __init__(self, N_fourier, L):
        """Represent the exact solution to the diffusion equation with a fourier sum.

        Args:
            N_fourier (int): the number of addends to include in the fourier sum
            L (float): the length of the integration interval

        """
        self.N_fourier = N_fourier
        self.L = L
        self.n = np.arange(1, N_fourier+1)
        self.fourier_coeffs = 2*(np.pi*self.n*np.cos(np.pi*self.n)\
                                - np.sin(np.pi*self.n))/(np.pi*np.pi*self.n*self.n)
        assert len(self.fourier_coeffs) == N_fourier

    def __call__(self, x_arr, t):
        """Description

        Args:
            x (float or np.1darray):
                the position(s) at which to evaluate the analytical function
            t (float): the time at which to evaluate the analytical function

        Returns:
            value (float): the function value

        """
        value = np.zeros_like(x_arr)
        for i in range(len(x_arr)):
            x = x_arr[i]
            value[i] = x/L
            C = self.n*np.pi/L
            value[i] += np.sum(self.fourier_coeffs*np.exp(-C*C*t)*np.sin(C*x))
        return value


if __name__ == "__main__":
    """
    TESTING
    """
    print('Running plot')
    # df = read_data("ForwardEuler-Nt5_0-dt6_0-Nx2_0")
    # length = len(df.loc[:,0])
    # for i in range(length):
        # plt.plot(df.loc[i,1:], label='t = %f' %(df.loc[i,0]))
    # plt.legend()
    # plt.show()
