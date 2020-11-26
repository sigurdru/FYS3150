import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys, os
from analytical_2D import theoretical_values
plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')

def read_exp_val_file(fname):
    """Read from file the expectation values from the Monte Carlo Simulation of
    the ising model.

    Args:
        fname (str): name of file containing the desired data

    Returns:
        df (pandas.DataFrame): the expectation values

    """
    df = pd.read_csv(os.path.join(path, fname + '.csv'))
    return df

def read_lattice_file(fname, num_spins):
    """Read from file the lattice configuration at different times of the
    simulation.

    Args:
        fname (str): name of file containing the desired data
        num_spins (int): the number of spins in each dimension of the lattice

    Returns:
        lattice (np.3darray): the lattice configuration at the different stages
            of the Monte Carlo Simulation.
            Dimensionality: (Stage of simulation, x, y)

    """
    lattice = np.loadtxt(os.path.join(path, fname), delimiter=',')
    cycles = lattice[:, 0]
    lattice = lattice[:, 1:].reshape(-1, num_spins, num_spins)
    return cycles, lattice

def plot_comparison(params, fname, data=None):
    if data is None:
        data = read_exp_val_file(fname)
    Cycle = data['Cycle'].to_numpy()
    T = data['Temperature'][0]
    E = data['MeanEnergy'].to_numpy()
    Cv = data['HeatCapacity'].to_numpy()
    chi = data['MagneticSusceptibility'].to_numpy()
    Mabs = data['Magnetization_Abs'].to_numpy()
    Last_index = len(Cycle)-1
    E_teo, Mabs_teo, chi_teo, Cv_teo = theoretical_values(T)
    fig, axs = plt.subplots(2, 2)
    fig.suptitle('Analytical and computed results for 2x2 lattice (T=%i)' %(T))

    axs[0][0].plot(Cycle, E, label="Computed")
    axs[0][0].plot([Cycle[0], Cycle[Last_index]], [E_teo, E_teo], '--', label="Theoretical")
    axs[0][0].set(ylabel='unitmaddafakka')
    axs[0][0].set_title(r'$\left<E\right>$')

    axs[1][0].plot(Cycle, Cv, label="Computed")
    axs[1][0].plot([Cycle[0], Cycle[Last_index]], [Cv_teo, Cv_teo], '--', label="Theoretical")
    axs[1][0].set_title(r'$\left<C_V\right>$')
    axs[1][0].set(ylabel='unitmaddafakka')

    axs[0][1].plot(Cycle, chi, label="Computed")
    axs[0][1].plot([Cycle[0], Cycle[Last_index]], [chi_teo, chi_teo], '--', label="Theoretical")
    axs[0][1].set_title(r'$\chi$')
    axs[0][1].set(ylabel='unitmaddafakka')

    axs[1][1].plot(Cycle, Mabs, label="Computed")
    axs[1][1].plot([Cycle[0], Cycle[Last_index]], [Mabs_teo, Mabs_teo], '--', label="Theoretical")
    axs[1][1].set_title(r'$\left<|M|\right>$')
    axs[1][1].set(ylabel='unitmaddafakka')

    for ax in axs.flat:
        ax.set(xlabel='Number of Monte Carlo cycles')
        ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '_comp.pdf'))

def plot_expectation_values(fname, data=None):
    if data is None:
        data = read_exp_val_file(fname)
    Cycle = data['Cycle'].to_numpy()
    T = data['Temperature'][0]
    E = data['MeanEnergy'].to_numpy()
    Cv = data['HeatCapacity'].to_numpy()
    chi = data['MagneticSusceptibility'].to_numpy()
    Mabs = data['Magnetization_Abs'].to_numpy()

    fig, axs = plt.subplots(4, 1)
    fig.suptitle('Computed results (T=%i)' %(T))
    axs[0].plot(Cycle, E, label=r'$\left<E\right>$')
    axs[0].set(ylabel='unitmaddafakka')

    axs[1].plot(Cycle, Cv, label=r'$\left<C_V\right>$')
    axs[1].set(ylabel='unitmaddafakka')

    axs[2].plot(Cycle, chi, label=r'$\chi$')
    axs[2].set(ylabel='unitmaddafakka')

    axs[3].plot(Cycle, Mabs, label=r'$\left<|M|\right>$')
    axs[3].set(ylabel='unitmaddafakka')

    for ax in axs.flat:
        ax.set(xlabel='Number of Monte Carlo cycles')
        ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '_ExpVals.pdf'))

def plot_expectation_vs_temp(fname, data=None):
    if data is None:
        data = read_exp_val_file(fname)
    Cycle = data['Cycle'].to_numpy()
    T = data['Temperature'].to_numpy()
    E = data['MeanEnergy'].to_numpy()
    Cv = data['HeatCapacity'].to_numpy()
    chi = data['MagneticSusceptibility'].to_numpy()
    Mabs = data['Magnetization_Abs'].to_numpy()

    fig, axs = plt.subplots(4, 1)
    fig.suptitle('Computed results (iteration=%i)' % (Cycle))
    axs[0].plot(T, E, label=r'$\left<E\right>$')
    axs[0].set(ylabel='unitmaddafakka')

    axs[1].plot(T, Cv, label=r'$\left<C_V\right>$')
    axs[1].set(ylabel='unitmaddafakka')

    axs[2].plot(T, chi, label=r'$\chi$')
    axs[2].set(ylabel='unitmaddafakka')

    axs[3].plot(T, Mabs, label=r'$\left<|M|\right>$')
    axs[3].set(ylabel='unitmaddafakka')

    for ax in axs.flat:
        ax.set(xlabel='Temperature')
        ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '_TempExp.pdf'))

def plot_lattice(fname, num_spins):
    cycles, lattice = read_lattice_file(fname, num_spins)
    Num_lattice = len(lattice)
    Spin_array = np.linspace(0,num_spins-1,num_spins)
    X, Y = np.meshgrid(Spin_array,Spin_array)
    for i in range(Num_lattice):
        plt.contourf(X,Y,lattice[i], colors = ['k', 'w'])
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '_Lattice.pdf'))

def plot_number_of_spins(params_list, fname, dfs):
    assert len(params_list) == len(dfs) == 2
    fig, axes = plt.subplots(1, 2)
    for i in range(len(dfs)):
        ax = axes[i]
        df = dfs[i].loc[:, ['Cycle', 'NumberOfFlips']]
        params = params_list[i]
        df.plot(ax=ax, x='Cycle', y='NumberOfFlips', logx=True, logy=True)
        config = 'random' if params.random_init else 'ordered'
        fig.suptitle(f'{params.L}x{params.L} spins, {config} configuration')
        ax.set_title(f'$T$ = {params.T}')
    fig.savefig(os.path.join(path, fname + '_NumSpins.pdf'))


path = '../output'

# data = read_exp_val_file()
# data.group_by('SystemEnergy').count()

if __name__ == '__main__':
    # plot_comparison('d/L20-T1-dT0_0-NT1-N100000-RandomTrue')
    plot_number_of_spins('d/L20-T1-dT0_0-NT1-N100000-RandomTrue')
    # fname = sys.argv[1]
    # num_spins = sys.argv[2]
    # method = sys.argv[3]
    # if method == 'plot_comparison':
        # plot_comparison(fname)
    # elif method == 'plot_expectation_values':
        # plot_expectation_values(fname)
    # elif method == 'plot_expectation_vs_temp':
        # plot_expectation_vs_temp(fname)
    # elif method == 'plot_lattice':
        # plot_lattice(fname, num_spins)
