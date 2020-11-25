import numpy as np

energy_array = np.array([-8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, -8])
magnetic_array = np.array([4, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -4])
iters = 16
num_spins = 4

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
    Z = partition_function(T)
    E = 0
    M = 0
    E2 = 0
    M2 = 0
    # Find expected energy as a function of temperature
    for i in range(iters):
        Ei = energy_array[i]
        Mi = magnetic_array[i]
        Pi = probability(Ei, T)
        E += Ei*Pi
        E2 += Ei**2*Pi
        M += abs(Mi)*Pi
        M2 += Mi**2*Pi
    E /= (Z * num_spins)
    M /= (Z * num_spins)
    E2 /= (Z * num_spins**2)
    M2 /= (Z * num_spins**2)
    chi = (M2 - M**2)*num_spins/T
    Cv = (E2 - E**2)*num_spins/(T**2)
    return E, M, chi, Cv
