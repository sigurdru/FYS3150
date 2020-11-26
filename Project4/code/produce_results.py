import subprocess
import plot

def run_simulation(params, fname):
    """Run the c++ simultion with the input given as argument to this function.

    Args:
        params (Parameters): an instance containing the parameters for this simulation
        fname (str): the filename used for saving data and plots

    """
    print(f'Simulating...\n    Result file: {fname}')
    command = ['./main.exe'] + [str(arg).lower() for arg in params.params()] + [fname]
    subprocess.call(command)

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
    L = 2
    T = 1
    dT = 0.0
    N_T = 1
    N = 100_000
    random_inits = [True, False]
    plot_spin = False
    for random_init in random_inits:
        fname = 'c/' + create_filename(L, T, dT, N_T, N, random_init)
        run_simulation(L, T, dT, N_T, N, random_init, plot_spin, fname)
        results = plot.read_exp_val_file(fname)
        plot.plot_comparison(fname, results)

def results_d():
    """Simulate a square lattice with L=20 spins and plot mean energy and
    magnetization as functions of the number of Monte Carlo cycles. Do this
    both for T=1.0 and T=2.4 with ordered and random start configurations

    """
    L = 20
    Ts = [1, 2.4]
    dT = 0.0
    NT = 1
    N_carl = 100_000
    random_inits = [True, False]
    plot_spin = False
    for random_init in random_inits:
        dfs = []
        params_list = []
        for T in Ts:
            params = Parameters(L, T, dT, NT, N_carl, random_init, plot_spin)
            params_list.append(params)
            fname = 'd/' + params.create_filename()
            run_simulation(params, fname)
            results = plot.read_exp_val_file(fname)
            dfs.append(results)
            plot.plot_comparison(params, fname, results)
        plot.plot_number_of_spins(params_list, fname, dfs)

class Parameters:
    def __init__(self, L, T, dT, NT, N_carl, random_init, plot_spin):
        self.L = L
        self.T = T
        self.dT = dT
        self.NT = NT
        self.N_carl = N_carl
        self.random_init = random_init
        self.plot_spin = plot_spin

    def create_filename(self):
        """Create a filename based on the parameters to the simulation.

        Returns:
            fname (str): the filename (without filetype)

        """
        L = self.L
        T = self.T
        dT = self.dT
        NT = self.NT
        N_carl = self.N_carl
        random_init = self.random_init
        fname = f'L{L}-T{T}-dT{dT}-NT{NT}-N{N_carl}-Random{random_init}'
        fname = fname.replace('.', '_')
        return fname

    def params(s):
        """Return a list of the parameters for the simulation.

        Returns:
            parameter (list): a list of all the parameters

        """
        return [s.L, s.T, s.dT, s.NT, s.N_carl, s.random_init, s.plot_spin]

if __name__ == '__main__':
    # run_simulation(2, 1, 0.1, 1, 10000, True, True)
    # print(create_filename(2, 1, 0.1, 1, 10000, True))
    results_d()
