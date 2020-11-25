import subprocess
import plot

def create_filename(L, T, dT, NT, N_carl, random_init):
    """Create a filename based on the parameters to the simulation.

    """
    fname = f'L{L}-T{T}-dT{dT}-NT{NT}-N{N_carl}-Random{random_init}'
    fname = fname.replace('.', '_')
    return fname

def run_simulation(*args):
    """Run the c++ simultion with the input given as argument to this function.

    Args:
        L (int): the number of spins in each direction
        T (float): the starting temperature
        dT (float): the step size for temperature
        N_T (int): the number of temperatures with which to run the simulation
        N_carl (int): the number of Monte Carlo cycles
        random_init (bool): initialize the spins randomly
        plot_spin (bool): write and plot the lattice configuration
        fname (str): the filename used for saving data and plots

    """
    subprocess.call(['./main.exe'] + [str(arg).lower() for arg in args[:-1]] + args[-1])

def task_results(task):
    """Produce the results for a given task, optionally all of them.

    Args:
        task (str): the task for which to produce results

    """
    if task == 'all':
        results_c()
        results_d()
        results_e()
        results_f()
        results_g()
    elif task == 'c':
        results_c()
    elif task == 'd':
        results_d()
    elif task == 'e':
        results_e()
    elif task == 'f':
        results_f()
    elif task == 'g':
        results_g()

def results_c():
    """Compute and plot the mean energy, mean magnetization, the specific heat
    capacity and the susceptibility as functions of number of Monte Carlo
    cycles using periodic boundary conditions for 2x2 spins with a temperature
    T=1.0 (in units of kT/J)

    """
    pass

def results_d():
    """Simulate a square lattice with L=20 spins and plot mean energy and
    magnetization as functions of the number of Monte Carlo cycles. Do this
    both for T=1.0 and T=2.4 with ordered and random start configurations

    """
    L = 20
    T = 1
    dT = 1.4
    N_T = 2
    N = 100_000
    random_inits = [True, False]
    plot_spin = False
    for random_init in random_inits:
        fname = create_filename(L, T, dT, N_T, N, random_init)
        run_simulation(L, T, dT, N_T, N, random_init, plot_spin, fname)

if __name__ == '__main__':
    # run_simulation(2, 1, 0.1, 1, 10000, True, True)
    # print(create_filename(2, 1, 0.1, 1, 10000, True))
    results_d()
