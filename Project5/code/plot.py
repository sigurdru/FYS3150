import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
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
    '#fa477d',
    '#000000'
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
    """The function plots and saves the figures

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
    title = f'{params.method}, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:f}$'
    title += f'\n{N_fourier} Fourier addends'
    for i in range(NumRows):
        t = df.loc[i, 0]
        analytical = exact(xa, t)
        color = colors[i]
        label = f'$t = {t:.3f}$'
        linestyle = '-o' if params.Nx <= 10 else '-'
        ax.plot(xa, df.loc[i, 1:], linestyle, color=color, label=label)
        ax.plot(xa, analytical, linestyle='--', color=color)
    xlabel = '$x$'
    ylabel = '$u(x, t)$'
    set_ax_info(ax, xlabel, ylabel, title=title)
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))
    plt.close()

def plot_evolution_error(params, fname):
    """The function plots and saves the error figures

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    N_fourier = 200
    df = read_data(fname)
    NumCols = len(df.loc[0, :])
    NumRows = len(df.loc[:, 0])
    exact = Exact1D(N_fourier, 1.0)
    xa = np.linspace(0, L, NumCols-1)[1:]
    fig, ax = plt.subplots()
    square_diff_list = []
    for i in [1, NumRows-1]:
        t = df.loc[i, 0]
        analytical = exact(xa, t)
        color = colors[i]
        label = f'$t = {t:.3f}$'
        computed = df.loc[i, 2:]
        difference = analytical - computed
        square_diff = 1/len(difference)*sum(abs(difference/analytical))
        square_diff_list.append([square_diff, t])
        ax.plot(xa, difference, color=color, label=label)
    title = f'{params.method}, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:f}$'
    title += f'\n{N_fourier} Fourier addends'
    for i in range(len(square_diff_list)):
        title += f'\nMean absolute percentage error: {square_diff_list[i][0]*100:.4f}\% (t={square_diff_list[i][1]})'
    xlabel = '$x$'
    ylabel = r'$u_t - u_c$'
    set_ax_info(ax, xlabel, ylabel, title=title)
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '-Error' + '.pdf'))


def plot_evolution_2D(params, fname):
    """The function plots and saves the figures for two dimensions

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    N_fourier = 200
    exact = Exact2D(N_fourier, 1.0)
    df = read_data(fname)
    # NumCols = len(df.loc[0, :])
    Nx = params.Nx
    xa = np.linspace(0, L, Nx+1)
    X, Y = np.meshgrid(xa, xa)
    fig = plt.figure()
    xlabel = '$x$'
    ylabel = '$y$'
    zlabel = '$z$'
    for i in range(2):
        for j in range(2):
            ax = fig.add_subplot(2, 2, 1+i+j, projection='3d')
            row = df.loc[i+j].to_numpy()
            t = row[0]
            temp = row[1:]
            temp = temp.reshape(Nx+1, Nx+1)
            step = 10
            ax.plot_surface(X[::step], Y[::step], temp[::step], label=f't={t}')
            set_ax_info(ax, xlabel, ylabel, zlabel = zlabel)
    title = f'Forward Euler, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:f}$'
    title += f'\n{N_fourier} Fourier addends'
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))


def set_ax_info(ax, xlabel, ylabel, title=None, zlabel=None):
    """Write title and labels on an axis with the correct fontsizes.

    Args:
        ax (matplotlib.axis): the axis on which to display information
        title (str): the desired title on the axis
        xlabel (str): the desired lab on the x-axis
        ylabel (str): the desired lab on the y-axis

    """
    if zlabel != None:
        ax.set_xlabel(xlabel, fontsize=15)
        ax.set_ylabel(ylabel, fontsize=15)
        ax.set_zlabel(zlabel, fontsize=15)
        ax.ticklabel_format(style='plain')
        ax.tick_params(axis='both', which='major', labelsize=15)
    if title != None:
        ax.set_title(title, fontsize=20)
        ax.set_xlabel(xlabel, fontsize=20)
        ax.set_ylabel(ylabel, fontsize=20)
        ax.ticklabel_format(style='plain')
        ax.tick_params(axis='both', which='major', labelsize=15)
        ax.legend(fontsize=15)



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


class Exact2D:
    def __init__(self, N_fourier, L):
        """Represent the exact solution to the diffusion equation with a fourier sum
           in two dimensions.

        Args:
            N_fourier (int): the number of addends to include in the fourier sum
            L (float): the length of the integration interval

        """
        self.N_fourier = N_fourier
        self.L = L
        self.n = np.arange(1, N_fourier+1)
        self.fourier_coeffs = 2*(np.pi*self.n*np.cos(np.pi*self.n)
                                 - np.sin(np.pi*self.n))/(np.pi*np.pi*self.n*self.n)
        assert len(self.fourier_coeffs) == N_fourier

    def __call__(self, x_arr, t):
        """Description

        Args:
            x (float or np.1darray):
                the position(s) at which to evaluate the analytical function
            y (float or np.1darray):
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
