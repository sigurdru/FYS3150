import subprocess
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

class Parameters:
    def __init__(self, Nx, Nt, dt, method, num_cores=1):
        self.Nx = Nx
        self.Nt = Nt
        self.dt = dt
        self.method = method
        self.num_cores = num_cores

    def create_filename(self):
        """Create a filename based on the parameters to the simulation.

        Returns:
            fname (str): the filename (without filetype)

        """
        import math
        Nx = self.Nx
        Nt = self.Nt
        dt = self.dt
        method = self.method
        fname = f'{method}-Nt{Nt}-dt{dt}-Nx{Nx}'
        fname = fname.replace('.', '_')
        return fname

    def produce_params_list(self):
        """Return a list of the parameters for the simulation.
        Returns:
            parameter (list): a list of all the parameters
        """
        return [self.Nx, self.Nt, self.dt, self.method]

if __name__ == '__main__':
    Nx = 2
    Nt = 4
    dt = 6
    method = "ForwardEuler"
    params = Parameters(Nx, Nt, dt, method)
    print(params.create_filename())
    # run_simulation(parameters_list(params), params.create_filename())
