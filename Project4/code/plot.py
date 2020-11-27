import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy.stats as stats
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

def plot_comparison(params, fname, data):
    Cycle = data['Cycle'].to_numpy()
    T = data['Temperature'][0]
    E = data['MeanEnergy'].to_numpy()
    Cv = data['HeatCapacity'].to_numpy()
    chi = data['MagneticSusceptibility'].to_numpy()
    Mabs = data['Magnetization_Abs'].to_numpy()
    E_teo, Mabs_teo, chi_teo, Cv_teo = theoretical_values(T)

    if params.random_init:
        title = 'Random'
        lim = 100
        color = colors['blue']
    else:
        title = 'Ordered'
        lim = len(Cycle)-1
        color = colors['red']

    Last_index = len(Cycle) - 1
    fig, axs = plt.subplots(2, 2)
    title += ' configuration\n'
    fig.suptitle(title + f'{params.L}x{params.L} spins, $T = {params.T}$')
    color = colors['blue'] if params.random_init else colors['red']

    # expectation value for energy
    axs[0][0].set_title(r'$\left<E\right>$')
    axs[0][0].plot(Cycle, E, label="Computed", color=color)
    axs[0][0].plot(
        [Cycle[0], Cycle[Last_index]],
        [E_teo, E_teo],
        '--', color=colors['green'],
        label="Theoretical"
    )
    axs[0][0].set(ylabel='unitmaddafakka')

    # heat capacity
    axs[1][0].set_title(r'$\left<C_V\right>$')
    axs[1][0].plot(Cycle, Cv, color=color, label="Computed")
    axs[1][0].plot(
        [Cycle[0], Cycle[Last_index]],
        [Cv_teo, Cv_teo],
        '--', color=colors['green'],
        label="Theoretical"
    )
    axs[1][0].set(ylabel='unitmaddafakka')

    # magnetic susceptibility
    axs[0][1].set_title(r'$\chi$')
    axs[0][1].plot(Cycle, chi, color=color, label="Computed")
    axs[0][1].plot(
        [Cycle[0], Cycle[Last_index]],
        [chi_teo, chi_teo],
        '--', color=colors['green'],
        label="Theoretical"
    )
    axs[0][1].set(ylabel='unitmaddafakka')

    # mean magnetization
    axs[1][1].set_title(r'$\left<|M|\right>$')
    axs[1][1].plot(Cycle, Mabs, color=color, label="Computed")
    axs[1][1].plot(
        [Cycle[0], Cycle[Last_index]],
        [Mabs_teo, Mabs_teo],
        '--', color=colors['green'],
        label="Theoretical"
    )
    axs[1][1].set(ylabel='unitmaddafakka')

    for ax in axs.flat:
        ax.set(xlabel='Number of Monte Carlo cycles')
        ax.legend()
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '_comp.pdf'))

def plot_expectation_values(params_list, fname, dfs):
    assert (len(params_list) == len(dfs) == 2)
    fig, axs = plt.subplots(2, 2)
    # loop through, first random, then ordered
    for i, data in enumerate(dfs):
        params = params_list[i]
        Cycle = data['Cycle'].to_numpy()
        T = data['Temperature'][0]
        E = data['MeanEnergy'].to_numpy()
        Cv = data['HeatCapacity'].to_numpy()
        chi = data['MagneticSusceptibility'].to_numpy()
        Mabs = data['Magnetization_Abs'].to_numpy()

        if params.random_init:
            label = 'Random'
            color = colors['blue']
        else:
            label = 'Ordered'
            color = colors['red']
        style = '--'

        fig.suptitle(f'{params.L}x{params.L} spins, $T = {params.T}$')
        axs[0][0].set_title(r'$\left<E\right>$')
        axs[0][0].plot(Cycle, E, style, color=color, label=label)
        axs[0][0].set(ylabel='unitmaddafakka')

        axs[1][0].set_title(r'$\left<C_V\right>$')
        axs[1][0].plot(Cycle, Cv, style, color=color, label=label)
        axs[1][0].set(ylabel='unitmaddafakka')

        axs[0][1].set_title(r'$\chi$')
        axs[0][1].plot(Cycle, chi, style, color=color, label=label)
        axs[0][1].set(ylabel='unitmaddafakka')

        axs[1][1].set_title(r'$\left<|M|\right>$')
        axs[1][1].plot(Cycle, Mabs, style, color=color, label=label)
        axs[1][1].set(ylabel='unitmaddafakka')

    for ax in axs.flat:
        ax.set(xlabel='Number of Monte Carlo cycles')
        ax.legend()
        ax.grid(True)
    fig.tight_layout()
    fname = '-'.join(fname.split('-')[:-1])
    fig.savefig(os.path.join(path, fname + '-ExpVals.pdf'))

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

def plot_number_of_flips(params_list, fname, dfs):
    """Plot the number of accepted flips during the simulation. The input
    arguments are lists of length 2, where one of the simulations was ordered
    and one was random.

    Args:
        params_list (list of Parameters)
        fname (str)
        dfs (list of pandas dataframes)

    """
    assert len(params_list) == len(dfs) == 2
    fig, axes = plt.subplots(1, 2)
    for i in range(len(dfs)):
        ax = axes[i]
        df = dfs[i]
        params = params_list[i]
        config = 'random' if params.random_init else 'ordered'
        color = colors['blue'] if params.random_init else colors['red']
        fig.suptitle(f'{params.L}x{params.L} spins, $T$ = {params.T}')
        df.plot(ax=ax, x='Cycle', y='NumberOfFlips',
            legend=False, color=color)
        ax.set_title(f'{config} configuration'.capitalize())
        ax.set_ylabel('Number of flips, cumulative')
    fname = '-'.join(fname.split('-')[:-1])
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '-NumFlips.pdf'))

def plot_probability_of_energy(params_list, fname, dfs):
    """Plot the number of accepted flips during the simulation. The input
    arguments are lists of length 2, where one of the simulations was ordered
    and one was random.

    Args:
        params_list (list of Parameters)
        fname (str)
        dfs (list of pandas dataframes)

    """
    assert len(params_list) == len(dfs) == 2
    fig, axes = plt.subplots(1, 2)
    for i in range(len(dfs)):
        ax = axes[i]
        df = dfs[i]
        params = params_list[i]
        config = 'random' if params.random_init else 'ordered'
        color = colors['blue'] if params.random_init else colors['red']
        fig.suptitle(f'{params.L}x{params.L} spins, $T$ = {params.T}')
        energy = df['EnergyPerSpin'].sort_values().to_numpy()
        ax.hist(energy, density=True, bins=20, label='Computed')
        legend_loc = 'best'
        title = f'{config} configuration'.capitalize()
        if params.T != 1:
            T = params.T
            num_spins = params.L**2
            comp_var = df['HeatCapacity'].iloc[-1]*T*T/num_spins
            std_dev = np.std(energy)
            fit = stats.norm.pdf(energy, np.mean(energy), std_dev)
            ax.plot(
                energy, fit,
                ':', color=colors['red'],
                label='Normal distribution'
            )
            legend_loc = 'upper left'
            title += '\n' + r'$\sigma_E^2 = ' + f'{std_dev**2:.3f}$'
            title += '\n' + r'Computed $\sigma_E^2 = ' + f'{comp_var:.3f}$'
        ax.set_title(title)
        ax.set_xlabel('E')
        ax.set_ylabel('P(E)')
        ax.legend(loc=legend_loc)
    fname = '-'.join(fname.split('-')[:-1])
    fig.tight_layout()
    fig.savefig(os.path.join(path, fname + '-ProbE.pdf'))


path = '../output'
colors = {
    'blue': '#1c518a',  # random configuration
    'red': '#f51b26',   # ordered configuration
    'green': '#20fa24'  # theoretical values
}

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
