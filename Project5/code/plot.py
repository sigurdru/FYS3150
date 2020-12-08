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


def read_data(fname):
    """
    Args:
        fname (str): name of file containing the desired data

    Returns:
        df (pandas.DataFrame): the expectation values

    """
    df = pd.read_csv(os.path.join(path, fname + '.csv'), header=None)
    return df


if __name__ == "__main__":
    df = read_data("ForwardEuler-Nt5_0-dt6_0-Nx2_0")
    length = len(df.loc[:,0])
    for i in range(length):
        plt.plot(df.loc[i,1:], label='t = %f' %(df.loc[i,0]))
    plt.legend()
    plt.show()
