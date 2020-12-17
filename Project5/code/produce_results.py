import subprocess, math
import plot

def run_simulation(params, fname):
    """
    Run the c++ simultion with the input given as argument to this function.
    Args:
        params (Parameters): an instance containing the parameters for this simulation
        fname (str): the filename used for saving data and plots
    """
    print(f'Simulating...\n    Result file: {fname}')
    command = ['./main.exe']
    parameter_list = params.produce_params_list()
    command += [str(arg) for arg in parameter_list] + [fname]
    subprocess.call(command)

def plot_solution(params, fname):
    plot.plot_evolution(params, fname)

def compare_one_dimensional():
    """Run the 1D simulation with all algorithms and compare results to analytical.

    """
    methods = ['ForwardEuler', 'BackwardEuler', 'CrankNicolson']
    Nxs = [10, 100]
    dts = [0.4, 0.5]
    for dti in dts:
        for method in methods:
            for Nx in Nxs:
                dt = dti/Nx**2
                Nt = int(0.5/dt)
                params = Parameters(Nx, Nt, dt, method)
                fname = params.create_filename()
                run_simulation(params, fname)
                plot.plot_evolution(params, fname)
                plot.plot_evolution_error(params, fname)

class Parameters:
    def __init__(self, Nx, Nt, dt, method, num_cores=1):
        assert isinstance(Nx, int)
        assert isinstance(Nt, int)
        assert isinstance(dt, float)
        assert isinstance(method, str)
        assert isinstance(num_cores, int)
        self.Nx = Nx
        self.Nt = Nt
        self.dt = dt
        self.method = method
        self.num_cores = num_cores

    def create_filename(self):
        """
        Create a filename based on the parameters to the simulation.
        """
        Nx = self.Nx
        Nt = self.Nt
        dt = self.dt
        method = self.method
        fname = f'{method}-Nt{Nt}-dt{dt}-Nx{Nx}'
        fname = fname.replace('.', '_')
        return fname

    def produce_params_list(self):
        """
        parameter (list): a list of all the parameters
        """
        return [self.Nx, self.Nt, self.dt, self.method, self.num_cores]

if __name__ == '__main__':
    """
    TESTING
    """
    compare_one_dimensional()