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
    lattice = lattice.reshape(-1, num_spins, num_spins)
    return lattice

def plot_exp_val(fname):
    data = read_exp_val_file(fname)
    keys = ['Cycle', 'Temperature', 'Energy', 'HeatCapacity',
            'MagneticSusceptibility', 'Magnetization_Abs']
    Cycle = data[keys[0]]
    # T = data[keys[1]]
    E = data[keys[2]]
    Cv = data[keys[3]]
    chi = data[keys[4]]
    Mabs = data[keys[5]]
    plt.plot(Cycle, E, label = r'$\left<E\right>$')
    plt.plot(Cycle, Cv, label = r'$\left<C_V\right>$')
    plt.plot(Cycle, chi, label = r'$\chi$')
    plt.plot(Cycle, Mabs, label = r'$\left<|M|\right>$')
    plt.xlabel('Number of Monte Carlo cycles')
    


# def plot_lattice(fname, num_spins):
#     pass

# N_args = len(sys.argv)
# if (N_args == 2):
#     fname_exp_val = sys.argv[1]
# elif (N_args == 4):
#     fname_exp_val = sys.argv[1]
#     fname_lattice = sys.argv[2]
#     num_spins = int(sys.argv[3])

plot_exp_val("test_exp.csv")

plt.legend()
plt.show()
