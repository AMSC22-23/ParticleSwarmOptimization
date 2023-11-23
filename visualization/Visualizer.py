import os
import glob
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

f = lambda x, y: (1-x)**2 + 100*(y-x**2)**2

def plot_surface_2d(f, x_lim, y_lim, iter, title,path_to_save, csv_files):
    for i in range(iter):

        fig = plt.figure(figsize=(10, 10))

        ax = fig.add_subplot(1, 1, 1)
        x = np.linspace(x_lim[0], x_lim[1], 100)
        y = np.linspace(y_lim[0], y_lim[1], 100)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        ax.contourf(X, Y, Z, 20, cmap='RdGy')
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_xlim(x_lim)
        ax.set_ylim(y_lim)
        ax.set_title(title)

        #Particles position on the surface
        for csv in os.listdir(csv_files):
            data = np.genfromtxt(csv_files+csv, delimiter=',', usecols=(0, 1))
            ax.scatter(data[i, 0], data[i, 1], c='black',marker='.', s=120)

        plt.savefig(path_to_save+"frame_" + str(i) +".png")
        plt.close()

def gif(folder, out_path):
    files = os.path.join(folder, '*.png')
    img, *imgs = [Image.open(f) for f in sorted(glob.glob(files))]
    img.save(fp=out_path, format='GIF', append_images=imgs,
             save_all=True, duration=200, loop=0)

# f, x_lim, y_lim, nb iter , title , path to save , path to particle data
plot_surface_2d(f, [10,-10], [10,-10], 100,"Rosenbrock function", "visualization/frames/", "data/")

# input folder, output folder 
gif("visualization/frames/", "visualization/animation.gif")