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
    num_spins = 4
    Z = partition_function(T)
    E = -32*(np.sinh(8/T))/Z/num_spins
    M = 8*(2+np.exp(8/T))/Z/num_spins
    chi = 32/Z/T*((1 + np.exp(8/T)) - 2/Z*(2+np.exp(8/T))**2)
    Cv = (32/T * (1 + np.exp(8/T))/Z - 64/T *(2 + np.exp(8/T))**2/Z/Z)
    return E, M, chi, Cv
