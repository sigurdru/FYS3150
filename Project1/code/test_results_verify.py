import sys
import numpy as np
import pandas as pd

fname = sys.argv[1] + '.txt'
df = pd.read_csv(fname)
comp = df['computed'].values
exact = df['exact'].values

np.testing.assert_allclose(comp, exact, 
        err_msg=f'The results in {fname} are not correct.')
