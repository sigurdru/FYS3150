import sys
from formats import Matrix

def mat_for_tridiag():
    N = 5
    l = [[0 for _ in range(N)] for _ in range(N)]
    for i in range(N-1):
        l[i][i] = 2
        l[i+1][i] = -1
        l[i][i+1] = -1
    l[N-1][N-1] = 2
    l = [[str(e) for e in row] for row in l]
    mat = Matrix(l)
    fname = 'mat_for_tridiag.tex'
    mat.latex(fname)

def vec_from_list(l, fname):
    l = [[str(e)] for e in l]
    mat = Matrix(l)
    mat.latex(fname)

def mat_for_2D():
    # initial
    l = [
        [0, 0, 0, 0, 0],
        [0, 1, 2, 3, 0],
        [0, 4, 5, 6, 0],
        [0, 7, 8, 9, 0],
        [0, 0, 0, 0, 0]
    ]
    l = [[str(e) for e in row] for row in l]
    mat = Matrix(l)
    fname = 'init_for_2D.tex'
    mat.latex(fname)

    # after one time step
    l = [
        [0,   0,   0,   0, 0],
        [0,   5,   4,  -5, 0],
        [0,  -2,   5,  -8, 0],
        [0, -25, -14, -35, 0],
        [0,   0,   0,   0, 0]
    ]
    l = [[str(e) for e in row] for row in l]
    mat = Matrix(l)
    fname = 'fin1_for_2D.tex'
    mat.latex(fname)

    # after two time steps
    l = [
        [0,   0,   0,   0, 0],
        [0, -31, -18,  27, 0],
        [0, -16, -75, -14, 0],
        [0, 143, -12, 201, 0],
        [0,   0,   0,   0, 0]
    ]
    l = [[str(e) for e in row] for row in l]
    mat = Matrix(l)
    fname = 'fin2_for_2D.tex'
    mat.latex(fname)

mat_for_tridiag()
mat_for_2D()
ls = [
    [1, 2, 3, 4, 6],
    [6, 11, 14, 14, 10],
    [0, 1, 2, 3, 4, 5, 3, 2, 1, 4, 6],
    [1., 1., 2., 3., 4., -1., 5., 2., 9., 2., 2.],
    [1, 14, -10, 18, 4, 2],
    [1, 4, 2, 6, 4, 2],
    [1, 6, 14, 4, 2, 2],
    [1, 4, 2, 6, 4, 2]
]
fnames = [
    'vec_for_tridiag.tex',
    'sol_for_tridiag.tex',
    'vec_for_ForwardEuler.tex',
    'sol_for_ForwardEuler.tex',
    'vec_for_BackwardEuler.tex',
    'sol_for_BackwardEuler.tex',
    'vec_for_CrankNicolson.tex',
    'sol_for_CrankNicolson.tex'
]
for l, fname in zip(ls, fnames):
    vec_from_list(l, fname)
