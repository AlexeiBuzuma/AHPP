#!/usr/bin/env python3
import ctypes
import pylab
import matplotlib.pylab as plt
from tqdm import tqdm
import numpy as np

# for information about cache type this "sudo dmidecode -t cache"

N = 20
buffer_size = 256 * 1024 
offset = 1 * 1024 * 1024

mproc = ctypes.CDLL('./array.so')


def convert_to_mem(size_of_matrix):
    bytes = size_of_matrix ** 2
    bytes *= 4.

    return bytes / (1024 * 1024)


def test_array():
    test_array_c = mproc.investigate_time_of_passing_through_array
    test_array_c.restype = ctypes.c_double

    y = []
    x = []
    for n in tqdm(range(1, N)):
        y.append(n)
        x.append(test_array_c(buffer_size, offset, n))
    
    fig = plt.figure()
    plot = fig.add_subplot(1, 1, 1)
    plot.plot(y, x,
             linestyle=":",
             marker="h",
             color="m",
             markerfacecolor="c")
    plot.grid()
    
    fig.savefig("results/array_accessing.png")
    plt.close(fig)


def test_matrix(number_of_repetitions=10, size_of_matrix=10000, step=500):
    test_matrix_c = mproc.processing_of_double_pointer_matrix
    test_matrix_c.restype = ctypes.c_double

    xlist = list(range(1, size_of_matrix, step))
    experimet_results = []

    for index in tqdm(range(number_of_repetitions)):
        y = []
        for x in xlist:
            y.append(test_matrix_c(x, 0))

        experimet_results.append(y)

    ylist = np.array([0.] * len(xlist))
    for l in experimet_results:
        ylist += np.array(l)

    ylist /= len(experimet_results)

    xlist = list(map(convert_to_mem, xlist))

    fig = plt.figure(figsize=(22, 17))
    plot = fig.add_subplot(1,1,1)

    plot.plot(xlist, ylist, 
             linestyle=":",
             marker="h",
             color="m",
             markerfacecolor="c")

    plot.set_xlabel("Size of matrix in Megabytes")
    plot.set_ylabel("Time of accessing to matrix")
    
    plot.grid()
    fig.savefig("results/matrx_accessing_{}.png".format(size_of_matrix))
    plt.close(fig)


def density_of_accessing(picture_name):
    
    coordinats = []
    with open("matrix_processing_result.log") as file:
        for line in file:
            coordinats.append(list(map(int, line.split() )))

    xlist, ylist = zip(*coordinats)
    xlist = np.array(xlist)
    ylist = np.array(ylist)

    heatmap, xedges, yedges = np.histogram2d(xlist, ylist, bins=150)
    extent = [xedges[0], xedges[-1], yedges[0], yedges[-1]]

    plt.clf()
    plt.cla()
    plt.imshow(heatmap, extent=extent)

    plt.savefig(picture_name)


def test_matrix_accessing_distribution():
    test_matrix_c = mproc.processing_of_double_pointer_matrix
    test_matrix_c.restype = ctypes.c_double

    xlist = [200, 1000, 2500, 5000]
    for x in tqdm(xlist):
        test_matrix_c(x, 1)
        density_of_accessing("results/matrx_accesing_distribution_{}.png".format(x))


if __name__ == '__main__':
    print("--> Test array accessing ...")
    test_array()

    print("--> Test matrix [13000x13000] accessing ...")
    test_matrix(size_of_matrix=13000)

    print("--> Test matrix [5000x5000] accessing ...")
    test_matrix(number_of_repetitions=20, size_of_matrix=5000, step=200)

    print("--> Test matrix accessing distribution ...")
    test_matrix_accessing_distribution()

    print("Completed successfully")
    print("Check the result images in 'result' folder")
