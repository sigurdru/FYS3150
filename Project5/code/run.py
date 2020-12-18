import argparse
import produce_results

parser = argparse.ArgumentParser(
    description='Solve numerically the 1D and 2D diffusion equation'\
        + ' and plot the results along with the analytic Fourier solution.',
    formatter_class=argparse.ArgumentDefaultsHelpFormatter
)

parser.add_argument('-r', '--results',
    type=str,
    choices=['1D', '2D', 'all'],
    help='The part for which to produce results. '\
            +'"all" will produce all the results in the report.'
)

parser.add_argument('-Nc', '--num-cores',
    type=int,
    default=8,
    help='The number of cores two use in a 2D simulation.'
)

params = parser.add_argument_group('simulation parameters')
params.add_argument('-Nx',
    type=float,
    default=1.0,
    help='The number of integration points'
)
params.add_argument('-Nt',
    type=float,
    default=1.0,
    help='The number of time steps'
)
params.add_argument('-dt',
    type=float,
    default=0.0,
    help='The step size in time'
)
params.add_argument('-m',
    type=str,
    choices=["ForwardEuler", "BackwardEuler", "CrankNicolson", "TwoDimensions"],
    default='ForwardEuler',
    help='The method you want to use'
)

args = parser.parse_args()

if args.results:
    if args.results == '1D':
        produce_results.compare_one_dimensional()
    elif args.results == '2D':
        produce_results.compare_two_dimensional(args.num_cores)
    else:
        produce_results.compare_one_dimensional()
        produce_results.compare_two_dimensional(args.num_cores)
else:
    params = produce_results.Parameters(
        args.Nx,
        args.Nt,
        args.dt,
        args.method,
        args.num_cores
    )
    produce_results.run_simulation(params, params.create_filename())
    produce_results.plot_solution(params, params.create_filename())
