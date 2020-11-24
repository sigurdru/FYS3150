import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys, os

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

lattice = read_lattice_file('test_lattice.csv', 2)
print(lattice)
