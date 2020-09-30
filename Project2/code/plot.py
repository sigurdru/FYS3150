import pandas as pd
import matplotlib.pyplot as plt
import sys

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='Computer Modern')

method, n, omega = sys.argv[1:]
omegas = [0.01, 0.5, 1, 5]
titles = {
    'BB': 'Buckling beam',
    'QM1': 'Quantum mechanics, one electron',
    'QM2': 'Quantum mechanics, two electron',
}

fig, ax = plt.subplots()
title = titles[method] + '\n' + f'n = {n}'
ax.set_title(title, fontsize=20)
ax.set_xlabel(r'$\rho$', fontsize=20)
ax.set_ylabel('Eigenvector', fontsize=20)

if method == 'QM2' and omega == '0':
    for omega in omegas:
        fname = '../output/' + '_'.join([method, n, str(omega)]) + '.csv'

        df = pd.read_csv(fname)
        ax.plot(
            df['rho'], 
            df['eigenvec'], 
            label=f'$\omega_r = {omega:.2f}$, $\lambda_1 = {df["eigenvals"][0]:.3f}$'
        )
    fname = fname[:-6] + fname[-4:]
else:
    fname = '../output/' + '_'.join(sys.argv[1:]) + '.csv'
    df = pd.read_csv(fname)
    ax.plot(
        df['rho'], 
        df['eigenvec'], 
        label=f'Computed, $\lambda_1 = {df["eigenvals"][0]:.3f}$'
    )
    try:
        ax.plot(
            df['rho'], 
            df['analytic_eigenvec'], 
            'r:',
            label=f'Analytic, $\lambda_1 = {df["analytic_eigenvals"][0]:.3f}$'
        )
    except KeyError:
        pass

ax.legend(fontsize=15)
ax.tick_params(axis='both', which='major', labelsize=15)
fig.tight_layout()
fig.savefig(fname.replace('csv', 'pdf'))
