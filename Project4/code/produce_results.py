import subprocess
import plot

def run_simulation(params, fname):
    """Run the c++ simultion with the input given as argument to this function.

    Args:
        params (Parameters): an instance containing the parameters for this simulation
        fname (str): the filename used for saving data and plots

    """
    print(f'Simulating...\n    Result file: {fname}')
    command = ['./main.exe']
    command += [str(arg).lower() for arg in params.params()] + [fname]
    subprocess.call(command)

def task_results(task):
    """Produce the results for a given task, optionally all of them.

    Args:
        task (str): the task for which to produce results

    """
    if task == 'all':
        results_c()
        results_d_and_e()
        # results_f()
    elif task == 'c':
        results_c()
    elif task == 'de':
        results_d_and_e()
    elif task == 'f':
        results_f()

def results_c():
    """Compute and plot the mean energy, mean magnetization, the specific heat
    capacity and the susceptibility as functions of number of Monte Carlo
    cycles using periodic boundary conditions for 2x2 spins with a temperature
    T=1.0 (in units of kT/J)

    """
    L = 2
    T = 1
    dT = 0.0
    NT = 1
    N = 100_000
    random_inits = [True, False]
    write_during = True
    for random_init in random_inits:
        params = Parameters(L, T, dT, NT, N, random_init, write_during)
        fname = 'c/' + params.create_filename()
        run_simulation(params, fname)
        results = plot.read_exp_val_file(fname)
        plot.plot_comparison(params, fname, results)
    # Run comparison as a function of temperature    
    dT = 0.01
    NT = 240
    N = 1_000_000
    random_inits = True
    write_during = False
    num_cores = 4
    params = Parameters(L, T, dT, NT, N, random_init, write_during, num_cores)
    fname = 'c/' + params.create_filename()
    run_simulation(params, fname)
    results = plot.read_exp_val_file(fname)
    plot.plot_comparison2(params, fname, results)

def results_d_and_e():
    """Simulate a square lattice with L=20 spins and plot mean energy and
    magnetization as functions of the number of Monte Carlo cycles. Do this
    both for T=1.0 and T=2.4 with ordered and random start configurations. Plot
    also a histogram showing the probability of finding the system in a state
    with total energy E.

    """
    L = 20
    Ts = [1, 2.4]
    dT = 0.0
    NT = 1
    N_carl = 200_000
    random_inits = [True, False]
    write_during = True
    for T in Ts:
        dfs = []
        params_list = []
        for random_init in random_inits:
            params = Parameters(L, T, dT, NT, N_carl, random_init, write_during)
            params_list.append(params)
            fname = 'de/' + params.create_filename()
            run_simulation(params, fname)
            results = plot.read_exp_val_file(fname)
            dfs.append(results)
        plot.plot_expectation_values(
            params_list,
            fname,
            [df.iloc[:100_000] for df in dfs]
        )
        plot.plot_number_of_flips(
            params_list,
            fname,
            [df.iloc[:100_000] for df in dfs]
        )
        plot.plot_probability_of_energy(
            params_list,
            fname,
            [df.iloc[100_000:] for df in dfs]
        )

def results_f():
    """Run the simulation for various values of L and a range of temperatures
    and plot the various expectation values as functions of T.

    """
    Ls = [40, 60, 80, 100]
    T = 2.0
    dT = 0.04
    NT = 14
    N_carl = 1_000_000
    random_init = True
    write_during = False
    num_cores = 4
    params_list = []
    df_list = []
    for L in Ls:
        params = Parameters(
            L, T, dT, NT, N_carl,
            random_init, write_during, num_cores
        )
        fname = 'f/' + params.create_filename()
        run_simulation(params, fname)
        results = plot.read_exp_val_file(fname)
        params_list.append(params)
        df_list.append(results)
        plot.plot_expectation_vs_temp(params, fname, results)
    plot.plot_percentage_of_accepted_flips(params_list, df_list)

class Parameters:
    def __init__(self, L, T, dT, NT, N_carl, random_init, write_during,
            num_cores=1
        ):
        self.L = L
        self.T = T
        self.dT = dT
        self.NT = NT
        self.N_carl = N_carl
        self.random_init = random_init
        self.write_during = write_during
        self.num_cores = num_cores

    def create_filename(self):
        """Create a filename based on the parameters to the simulation.

        Returns:
            fname (str): the filename (without filetype)

        """
        import math
        L = self.L
        T = self.T
        dT = self.dT
        NT = self.NT
        N_carl = int(math.log10(self.N_carl))
        random_init = self.random_init
        fname = f'L{L}-T{T}-dT{dT}-NT{NT}-N{N_carl}-Random{random_init}'
        fname = fname.replace('.', '_')
        return fname

    def params(s):
        """Return a list of the parameters for the simulation.

        Returns:
            parameter (list): a list of all the parameters

        """
        return [s.L, s.T, s.dT, s.NT, s.N_carl,
                s.random_init, s.write_during, s.num_cores]

if __name__ == '__main__':
    L = 2
    T = 1
    dT = 0.1
    NT = 5
    N_carl = 10_000
    random_init = True
    plot_spin = True
    params = Parameters(L, T, dT, NT, N_carl, random_init, plot_spin)
    print(params.create_filename())
