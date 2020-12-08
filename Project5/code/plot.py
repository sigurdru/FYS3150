import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import scipy.stats as stats
import sys
import os

plt.style.use('seaborn')
plt.rc('text', usetex=True)
plt.rc('font', family='DejaVu Sans')
path = '../output/'
path_plots = '../output/plots'

def read_data(fname):
    """
    Args:
        fname (str): name of file containing the desired data

    Returns:
        df (pandas.DataFrame): the expectation values

    """
    df = pd.read_csv(os.path.join(path, fname + '.csv'), header=None)
    return df

def plot_evolution(fname, method):
    df = read_data(fname)
    NumRows = len(df.loc[:,0])
    NumCols = len(df.loc[0,:])
    xa = np.linspace(0,1,NumCols-1)
    fig, ax = plt.subplots()
    ax.set_title(method)
    for i in range(NumRows):
        ax.plot(xa, df.loc[i, 1:], label='t = %f' % (df.loc[i, 0]))
    ax.legend()
    ax.set_xlabel("L")
    ax.set_ylabel("u")
    fig.tight_layout()
    fig.savefig(os.path.join(path_plots, fname + '.pdf'))



if __name__ == "__main__":
    df = read_data("ForwardEuler-Nt5_0-dt6_0-Nx2_0")
    length = len(df.loc[:,0])
    for i in range(length):
        plt.plot(df.loc[i,1:], label='t = %f' %(df.loc[i,0]))
    plt.legend()
    plt.show()
