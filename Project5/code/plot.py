import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import sys, os, re
from matplotlib import cm

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
    """Read the results om the computation from file.

    Args:
        fname (str): name of file containing the desired data

    Returns:
        df (pandas.DataFrame): the calculated values

    """
    df = pd.read_csv(os.path.join(path, fname + '.csv'), header=None)
    return df

def plot_evolution(params, fname):
    """Plot and save the 1D results along with the analytic Fourier solution.

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    N_fourier = 200
    df = read_data(fname)
    NumRows = len(df.loc[:,0])
    NumCols = len(df.loc[0,:])
    xa = np.linspace(0, L, NumCols-1)
    exact = Exact1D(N_fourier, L)
    fig, ax = plt.subplots()
    linestyle = '-o' if params.Nx <= 10 else '-'
    for i in range(NumRows):
        t = df.loc[i, 0]
        analytical = exact(xa, t)
        color = colors[i]
        label = f'$t = {t:.3f}$'
        ax.plot(xa, df.loc[i, 1:], linestyle, color=color, label=label)
        ax.plot(xa, analytical, linestyle='--', color=color)
    title = f'{params.method}, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:.1e}$'
    title += f'\n{N_fourier} Fourier addends'
    xlabel = '$x$'
    ylabel = '$u(x, t)$'
    set_ax_info(ax, xlabel, ylabel, title)
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))
    plt.close()

def plot_evolution_error(params, fname):
    """Plot and save the error in the solution to the 1D equation.

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
    title += f', $\Delta t = {params.dt:.1e}$'
    title += f'\n{N_fourier} Fourier addends'
    for i in range(len(square_diff_list)):
        title += f'\nMean absolute percentage error: {square_diff_list[i][0]*100:.4f}\% (t={square_diff_list[i][1]})'
    xlabel = '$x$'
    ylabel = r'$u_t - u_c$'
    set_ax_info(ax, xlabel, ylabel, title=title)
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '-Error' + '.pdf'))
    plt.close()



def plot_evolution_2D(params, fname):
    """The function plots and saves the figures for two dimensions

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    plt.style.use('classic')
    N_fourier = 50
    exact = Exact2D(N_fourier, 1.0)
    df = read_data(fname)
    Nx = params.Nx
    xa = np.linspace(0, L, Nx+1)
    X, Y = np.meshgrid(xa, xa)
    fig = plt.figure()
    xlabel = '$x$'
    ylabel = '$y$'
    zlabel = '$z$'
    k = 0
    step = 10
    for i in range(2):
        for j in range(2):
            ax = fig.add_subplot(2, 2, 1+k, projection='3d')
            if (k == 3):
                k = 4
            row = df.loc[k].to_numpy()
            t = row[0]
            temp_ana = exact(X,Y,t)
            temp = row[1:]
            temp = temp.reshape(Nx+1, Nx+1)
            surf = ax.plot_wireframe(X[1:-1, 1:-1], Y[1:-1, 1:-1], temp_ana[1:-1, 1:-1],
                                alpha=0.3 if k==0 else 0.7, color='black')
            surf = ax.plot_surface(X[1:-1, 1:-1], Y[1:-1, 1:-1], temp[1:-1, 1:-1],
                                alpha=0.6, label = f"t = {t:.3f}", cmap=cm.coolwarm)
            surf._facecolors2d=surf._facecolors3d
            surf._edgecolors2d=surf._edgecolors3d
            ax.legend()
            set_ax_info(ax, xlabel, ylabel, zlabel = zlabel)
            k += 1
    title = f'Forward Euler, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:.1e}' + r'}$'
    title += f'\n{N_fourier} Fourier addends'
    title = title.replace(r'e-0', r'\cdot 10^{-')
    fig.suptitle(title)
    fig.tight_layout(pad=2.5)
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))
    plt.close()



def plot_evolution_2D_error(params, fname):
    """The function plots and saves the figures for two dimensions

    Args:
        params (Parameters): the simulation parameters for the data
        fname (str): name of the file containing the desired data

    """
    plt.style.use('classic')
    N_fourier = 50
    exact = Exact2D(N_fourier, 1.0)
    df = read_data(fname)
    Nx = params.Nx
    xa = np.linspace(0, L, Nx+1)
    X, Y = np.meshgrid(xa, xa)
    fig = plt.figure()
    xlabel = '$x$'
    ylabel = '$y$'
    zlabel = '$z$'
    k = 0
    step = 10
    print('------------------------------')
    for i in range(2):
        for j in range(2):
            ax = fig.add_subplot(2, 2, 1+k, projection='3d')
            if (k == 3):
                k = 4
            row = df.loc[k].to_numpy()
            t = row[0]
            temp_ana = exact(X, Y, t)
            temp = row[1:]
            temp = temp.reshape(Nx+1, Nx+1)
            difference = temp_ana-temp
            surf = ax.plot_surface(X[1:-1, 1:-1], Y[1:-1, 1:-1], difference[1:-1, 1:-1],
                                   alpha=0.6, label=f"t = {t:.3f}", cmap=cm.coolwarm)
            surf._facecolors2d = surf._facecolors3d
            surf._edgecolors2d = surf._edgecolors3d
            ax.legend()
            set_ax_info(ax, xlabel, ylabel, zlabel=zlabel)
            k += 1
            MAPE = 1/(len(temp_ana)**2)*np.sum(np.abs(difference))
            print(f'|MAPE = {MAPE:9.2e}%| t = {t:4.3f}|')
    title = f'Forward Euler, $N_x = {params.Nx}$'
    title += f', $\Delta t = {params.dt:.1e}' + r'}$'
    title += f'\n{N_fourier} Fourier addends'
    title = title.replace(r'e-0', r'\cdot 10^{-')
    fig.suptitle(title)
    fig.tight_layout(pad=2.5)
    fig.savefig(os.path.join(path_plots, fname + '-Error' + '.pdf'))
    plt.close()
    print('------------------------------')



def set_ax_info(ax, xlabel, ylabel, title=None, zlabel=None):
    """Write title and labels on an axis with the correct fontsizes.

    Args:
        ax (matplotlib.axis): the axis on which to display information
        title (str): the desired title on the axis
        xlabel (str): the desired lab on the x-axis
        ylabel (str): the desired lab on the y-axis

    """
    if zlabel == None:
        ax.set_xlabel(xlabel, fontsize=20)
        ax.set_ylabel(ylabel, fontsize=20)
        ax.tick_params(axis='both', which='major', labelsize=15)
        ax.ticklabel_format(style='plain')
    else:
        ax.set_xlabel(xlabel, fontsize=18)
        ax.set_ylabel(ylabel, fontsize=18)
        ax.set_zlabel(zlabel, fontsize=18)
        ax.tick_params(axis='both', which='major', labelsize=12)
        ax.ticklabel_format(style='scientific', scilimits = (-2, 2))
    if title != None:
        # replace calculator notation for standard form and set title
        # match digit followed by e, optional minus and digits
        pattern = r'(\d)e(-?\d+)'
        title = re.sub(pattern, r'\1 \\cdot 10^{\2}', title)
        title = title.replace(r'10^{0', r'10^{')
        title = title.replace(r'10^{-0', r'10^{-')
        ax.set_title(title, fontsize=20)
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
        n = np.arange(1, N_fourier+1)
        self.N, self.M = np.meshgrid(n,n)
        self.Anm = 4/np.pi**2*((np.cos(self.N*np.pi/2) - 1)*((-1)**self.M - 1))/(self.N*self.M)
    def __call__(self, X, Y,t):
        """Description

        Args:
            x (float or np.2darray):
                the position(s) at which to evaluate the analytical function
            y (float or np.2darray):
                the position(s) at which to evaluate the analytical function
            t (float): the time at which to evaluate the analytical function

        Returns:
            value (float): the function value

        """
        value = np.zeros_like(X)
        for i in range(len(X)):
            for j in range(len(Y)):
                x = X[i][j]
                y = Y[i][j]
                value[j][i] = np.sum(self.Anm*np.sin(self.M*np.pi*x)*np.sin(self.N*np.pi*y)*np.exp(-(self.M**2*np.pi**2 + self.N**2*np.pi**2)*t))
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
