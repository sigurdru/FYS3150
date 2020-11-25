import argparse

parser = argparse.ArgumentParser(
    description='Run a simulation with the ising model using the'\
        + ' Metropolis Algorithm',
    formatter_class=argparse.ArgumentDefaultsHelpFormatter
)
parser.add_argument('-t', '--task',
    choices=['all', 'c', 'd', 'e', 'f', 'g'],
    type=str,
    help='Select the results for which task to produce'
)
params = parser.add_argument_group('simulation parameters')
params.add_argument('-L', type=int, default=20,
    help='The number of spins in each dimension'
)
params.add_argument('-T',
    type=float,
    default=1.0,
    help='The starting temperature for the simulation'
)
params.add_argument('-dT',
    type=float,
    default=0.0,
    help='The step size for temperature'
)
params.add_argument('-NT',
    type=int,
    default=0,
    help='The number of different temperatures to run for'
)
params.add_argument('-N',
    type=int,
    default=10_000,
    help='The number of Monte Carlo cycles to run'
)
params.add_argument('-R', '--random',
    action='store_true',
    help='Randomly initialize the spins'
)
args = parser.parse_args()

if bool(args.task):
    produce_results.task_results(args.task)

