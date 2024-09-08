import random
import numpy as np


def fixed(d, i, j, v, offsets):
    # For fixed bdries, all cells are valid. Define n so as to allow the
    # usual lower bound inclusive, upper bound exclusive indexing.
    n = d.shape[0]

    res, k = 0, 0
    for p, q in offsets:
        pp, qq = i + p * v, j + q * v
        if 0 <= pp < n and 0 <= qq < n:
            res += d[pp, qq]
            k += 1.0
    return res / k


def periodic(d, i, j, v, offsets):
    # For periodic bdries, the last row/col mirrors the first row/col.
    # Hence the effective square size is (n-1)x(n-1). Redefine n accordingly!
    n = d.shape[0] - 1

    res = 0
    for p, q in offsets:
        res += d[(i + p * v) % n, (j + q * v) % n]
    return res / 4.0


def single_diamond_square_step(d, w, s, avg):
    # w is the dist from one "new" cell to the next
    # v is the dist from a "new" cell to the nbs to average over

    n = d.shape[0]
    v = w // 2

    # offsets:
    diamond = [(-1, -1), (-1, 1), (1, 1), (1, -1)]
    square = [(-1, 0), (0, -1), (1, 0), (0, 1)]

    # (i,j) are always the coords of the "new" cell

    # Diamond Step
    for i in range(v, n, w):
        for j in range(v, n, w):
            d[i, j] = avg(d, i, j, v, diamond) + random.uniform(-s, s)

    # Square Step, rows
    for i in range(v, n, w):
        for j in range(0, n, w):
            d[i, j] = avg(d, i, j, v, square) + random.uniform(-s, s)

    # Square Step, cols
    for i in range(0, n, w):
        for j in range(v, n, w):
            d[i, j] = avg(d, i, j, v, square) + random.uniform(-s, s)


def make_terrain(n, ds, bdry):
    # Returns an n-by-n landscape using the Diamond-Square algorithm, using 
    # roughness delta ds (0..1). bdry is an averaging fct, including the
    # bdry conditions: fixed() or periodic(). n must be 1+2**k, k integer.
    d = np.zeros(n * n).reshape(n, n)

    w, s = n - 1, 1.0
    while w > 1:
        single_diamond_square_step(d, w, s, bdry)

        w //= 2
        s *= ds

    return d


n = 1 + 2**9    # Edge size of the resulting image in pixes
ds = 0.6        # Roughness delta, 0 < ds < 1 : smaller ds => smoother results
bdry = periodic # One of the averaging routines: fixed or periodic

terrain = make_terrain( n, ds, bdry )

import matplotlib.colors
import matplotlib.pyplot as plt

# Create a colormap
tmp = []
for row in np.loadtxt( "data.txt" ):
    tmp.append( [ row[0], row[1:4] ] )
cm = matplotlib.colors.LinearSegmentedColormap.from_list( "geo-smooth", tmp )

# Create an image using the colormap
plt.figure( figsize=( n/100, n/100 ), dpi=100 ) # create n-by-n pixel fig
plt.tick_params( left=False, bottom=False, labelleft=False, labelbottom=False )
plt.imshow( terrain, cmap=cm )

plt.show()                    # Show interactive