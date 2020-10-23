import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import sys

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')

fname, N, dt, = sys.argv[1:]
dt = float(dt)
N = int(N)
print_step = int(0.01/dt)
N_lines = int(N/print_step)-1

fig = plt.figure
ax = plt.axes(projection='3d')

title = "Orbit"
ax.set_title(title, fontsize=20)
ax.set_xlabel('Position x [AU]', fontsize=20)
ax.set_ylabel('Position y [AU]', fontsize=20)
ax.set_zlabel('Position z [AU]', fontsize=20)

file_position = '../output/'+fname+'.xyz'
infile = open(file_position, 'r')

line = infile.readline()
data = line.split()
num_bodies = int(data[0])
infile.readline()

x_positions = [np.zeros(N_lines) for _ in range(num_bodies)]
y_positions = [np.zeros(N_lines) for _ in range(num_bodies)]
z_positions = [np.zeros(N_lines) for _ in range(num_bodies)]
names = []

for i in range(num_bodies):
    line = infile.readline()
    data = line.split()
    names.append(data[0])
    x_positions[i][0] = float(data[1])
    y_positions[i][0] = float(data[2])
    z_positions[i][0] = float(data[3])

for i in range(1, N_lines):
    infile.readline()
    infile.readline()
    for j in range(num_bodies):
        line = infile.readline()
        data = line.split()
        x_positions[j][i] = float(data[1])
        y_positions[j][i] = float(data[2])
        z_positions[j][i] = float(data[3])

infile.close()

for i in range(num_bodies):
    ax.scatter3D(x_positions[i][0], y_positions[i][0], z_positions[i][0])
    ax.plot3D(x_positions[i][1:], y_positions[i][1:], z_positions[i][1:], label = names[i])
ax.legend(fontsize=15)
ax.tick_params(axis='both', which='major', labelsize=15)
# fig.tight_layout()
plt.show()
# fig.savefig(fname.replace('csv', 'pdf'))
