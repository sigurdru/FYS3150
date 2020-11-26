import numpy as np

def partition_function(T):
    """
    Finds the analytical partition function for a 2D lattice,
    without an external magnetic field.
    """
    Z = 12 + 4*np.cosh(8/T)
    return Z

def probability(E, T):
    value = np.exp(-E/T)
    return value

def theoretical_values(T):
    beta = 1/T
    num_spins = 4
    Z = partition_function(T)
    E = -32*(np.sinh(8/T))/Z/num_spins
    M = 8*(2+np.exp(8/T))/Z/num_spins
    chi = (32 * beta * (1 + np.exp(8 * beta)) / Z - 64 * beta * (2 + np.exp(8 * beta))**2 / Z**2) / num_spins
    Cv = 1024/T*(3 * np.cosh(8/T) + 1)/T/Z/Z/num_spins
    return E, M, chi, Cv
