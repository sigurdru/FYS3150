import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import sys

plt.style.use('seaborn')

def read_xyz_file(fname, N_lines):
    file_position = '../output/positions/' + fname + '.xyz'
    with open(file_position, 'r') as infile:
        line = infile.readline()
        data = line.split()
        num_bodies = int(data[0])
        
        position = np.zeros((num_bodies, N_lines, 3))
        energy = np.zeros((N_lines, 3))
        ang_momentum = np.zeros((N_lines, 3))
        names = []

        energies = infile.readline()
        pot, kin, tot, *ang_mom = energies[:-3].split()
        energy[0] = [pot, kin, tot]
        ang_momentum[0] = [float(e.strip('[').strip(',')) for e in ang_mom]
        
        for i in range(num_bodies):
            line = infile.readline()
            data = line.split()
            names.append(data[0])
            position[i, 0] = [float(val) for val in data[2:5]]
        
        for i in range(1, N_lines):
            infile.readline()   # Read past number of bodies
            energies = infile.readline()
            pot, kin, tot, *ang_mom = energies[:-3].split()
            energy[i] = [pot, kin, tot]
            ang_momentum[i] = [float(e.strip('[').strip(',')) for e in ang_mom]
            for j in range(num_bodies):
                line = infile.readline()
                data = line.split()
                position[j, i] = [float(val) for val in data[2:5]]
        return position, energy, ang_momentum, num_bodies, names

fname = sys.argv[1]
if len(sys.argv) == 3 and sys.argv[2] =='3D':
    plot3D_bool = True
else:
    plot3D_bool = False
out_fname = fname.replace('.', '_')
description, solver_method, dt, N, beta = fname.split('-')
dt = 10**(-int(dt))
N = 10**int(N)
print_step = int(0.01/dt)
N_lines = int(N/print_step)-1

position, energies, ang_momentum, num_bodies, names = read_xyz_file(fname, N_lines)
dt = 0.01
t = np.arange(0, N_lines*dt, dt)

if plot3D_bool:
    fig = plt.figure
    ax = plt.axes(projection='3d')

    title = "Orbit"
    ax.set_title(title, fontsize=20)
    ax.set_xlabel('Position x [AU]', fontsize=20)
    ax.set_ylabel('Position y [AU]', fontsize=20)
    ax.set_zlabel('Position z [AU]', fontsize=20)

    for i in range(num_bodies):
        ax.scatter3D(position[i, 0, 0], position[i, 0, 1], position[i, 0, 2])
        ax.plot3D(
                position[i, 1:, 0], 
                position[i, 1:, 1], 
                position[i, 1:, 2], 
                label = names[i])
    ax.legend(fontsize=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    plt.show()
else:
    plt.rc('text', usetex=True)
    plt.rc('font', family='DejaVu Sans')
    fig, ax = plt.subplots()
    for i in range(num_bodies):
        ax.plot(position[i, 0, 0], position[i, 0, 1], 'o')
        ax.plot(position[i, 1:, 0], position[i, 1:, 1], label = names[i])
    ax.axis('equal')
    title = "Orbit"
    ax.set_title(title, fontsize=20)
    ax.set_xlabel(r'Position $x$, [AU]', fontsize=20)
    ax.set_ylabel(r'Position $y$, [AU]', fontsize=20)
    ax.legend(fontsize=15)
    ax.tick_params(axis='both', which='major', labelsize=15)
    fig.tight_layout()
    fig.savefig('../output/' + out_fname + '.pdf')

plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')
fig, ax = plt.subplots()
ax.plot(t, energies[:, 0], label='Potential')
ax.plot(t, energies[:, 1], label='Kinetic')
ax.plot(t, energies[:, 2], label='Total')
title = 'Energy'
ax.set_title(title, fontsize=20)
ax.set_xlabel(r'Time, [yrs]', fontsize=20)
ax.set_ylabel(r'Energy, [$M_\odot$ AU$^2$/yr$^2$]', fontsize=20)
ax.legend(fontsize=15)
ax.tick_params(axis='both', which='major', labelsize=15)
fig.tight_layout()
fig.savefig('../output/' + out_fname + '_energy.pdf')

plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')
fig, ax = plt.subplots()
ax.plot(t, ang_momentum[:, 0], label='$x$')
ax.plot(t, ang_momentum[:, 1], label='$y$')
ax.plot(t, ang_momentum[:, 2], label='$z$')
# ax.plot(t, np.linalg.norm(ang_momentum, axis=1), ':', label='Size')
ax.set_title('Angular momentum', fontsize=20)
ax.set_xlabel(r'Time, [yrs]', fontsize=20)
ax.set_ylabel(r'Angular momentum, [$M_\odot$ AU$^2$/yr]', fontsize=20)
ax.legend(fontsize=15)
ax.tick_params(axis='both', which='major', labelsize=15)
fig.tight_layout()
fig.savefig('../output/' + out_fname + '_ang_mom.pdf')
