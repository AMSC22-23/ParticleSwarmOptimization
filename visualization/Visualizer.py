import os
import glob
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from multiprocessing import Pool

# Rosenbrock function
#f = lambda x, y: (1-x)**2 + 100*(y-x**2)**2

# Ackley function
#f = lambda x, y: -20*np.exp(-0.2*np.sqrt(0.5*(x**2+y**2))) - np.exp(0.5*(np.cos(2*np.pi*x)+np.cos(2*np.pi*y))) + np.e + 20
def f(x, y):
    return -20*np.exp(-0.2*np.sqrt(0.5*(x**2 + y**2))) - np.exp(0.5*(np.cos(2*np.pi*x) + np.cos(2*np.pi*y))) + np.e + 20

def plot_surface_2d(iter, x_lim, y_lim, title,path_to_save, csv_files):
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(1, 1, 1)
    x = np.linspace(x_lim[0], x_lim[1], 100)
    y = np.linspace(y_lim[0], y_lim[1], 100)
    X, Y = np.meshgrid(x, y)
    Z = f(X, Y)
    ax.contourf(X, Y, Z, 20, cmap='bwr')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_xlim(x_lim)
    ax.set_ylim(y_lim)
    ax.set_title(title)

    #Particles position on the surface
    for csv in os.listdir(csv_files):
        data = np.genfromtxt(csv_files+csv, delimiter=',', usecols=(0, 1))
        ax.scatter(data[iter, 0], data[iter, 1], c='black',marker='.', s=120)

    plt.savefig(path_to_save+"frame_" + str(iter) +".png")
    plt.close()

def helper(args):
    return plot_surface_2d(*args)

def gif(folder, out_path):
    files = os.path.join(folder, '*.png')
    img, *imgs = [Image.open(file) for file in sorted(glob.glob(files))]
    img.save(fp=out_path, format='GIF', append_images=imgs,
             save_all=True, duration=300, loop=1)

# x_lim, y_lim , title , path to save , path to particle data
# plot_surface_2d([30, -30], [30,-30],"Ackley function", "visualization/frames/", "data/")

if __name__ == '__main__':
    args = [(i, [30, -30], [30,-30], "Ackley function", "visualization/frames/", "data/") for i in range(200)]
    with Pool() as p:
        p.map(helper, args)

# input folder, output folder 
gif("visualization/frames/", "visualization/animation.gif")