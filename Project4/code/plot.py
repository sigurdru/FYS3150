import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys, os
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
    df = pd.read_csv(fname)
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
    lattice = np.loadtxt(fname, delimiter=',')
    cycles = lattice[:, 0]
    lattice = lattice[:, 1:].reshape(-1, num_spins, num_spins)
    return cycles, lattice

def plot_comparison(fname):
    data = read_exp_val_file(fname)
    keys = ['Cycle', 'Temperature', 'Energy', 'HeatCapacity',
            'MagneticSusceptibility', 'Magnetization_Abs']
    Cycle = data[keys[0]]
    T = data[keys[1]][0]
    E = data[keys[2]]
    Cv = data[keys[3]]
    chi = data[keys[4]]
    Mabs = data[keys[5]]
    Last_index = len(Cycle)-1
    E_teo = -1.99598
    Cv_teo = 0.0320823
    Mabs_teo = 0.998661
    chi_teo = 3.9933
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


def plot_expectation_values(fname):
    data = read_exp_val_file(fname)
    keys = ['Cycle', 'Temperature', 'Energy', 'HeatCapacity',
            'MagneticSusceptibility', 'Magnetization_Abs']
    Cycle = data[keys[0]]
    T = data[keys[1]][0]
    E = data[keys[2]]
    Cv = data[keys[3]]
    chi = data[keys[4]]
    Mabs = data[keys[5]]

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

def plot_expectation_vs_temp(fname):
    data = read_exp_val_file(fname)
    keys = ['Cycle', 'Temperature', 'Energy', 'HeatCapacity',
            'MagneticSusceptibility', 'Magnetization_Abs']
    Cycle = data[keys[0]][0]
    T = data[keys[1]]
    E = data[keys[2]]
    Cv = data[keys[3]]
    chi = data[keys[4]]
    Mabs = data[keys[5]]

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

def plot_lattice(fname, num_spins):
    cycles, lattice = read_lattice_file(fname, num_spins)
    Num_lattice = len(lattice)
    Spin_array = np.linspace(0,num_spins-1,num_spins)
    X, Y = np.meshgrid(Spin_array,Spin_array)
    for i in range(Num_lattice):
        plt.contourf(X,Y,lattice[i], colors = ['k', 'w'])
        plt.show()

plot_comparison("../output/2_random_ExpVals.csv")
plt.tight_layout()
plt.show()


# plot_expectation_values("../output/10_random_ExpVals.csv")
# plt.tight_layout()
# plt.show()

# plot_expectation_vs_temp("../output/2_random_ExpVals.csv")
# plt.tight_layout()
# plt.show()

# plot_lattice("../output/10_random_Lattice.csv", 10)
# plt.tight_layout()
# plt.plot()

