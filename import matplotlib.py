import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import numpy as np

file_path = "Circular2B.txt"

with open(file_path, 'r') as file:
    lines = file.readlines()

num_bodies = int(len(lines[0].strip().split(',')))// 3
num_points = int(len(lines))

data = np.zeros((num_bodies, num_points, 3))

for i, line in enumerate(lines):
    values = line.strip().split(',')
    for j in range(num_bodies):
        X, Y, Z = map(float, values[j * 3: (j + 1) * 3])
        data[j, i, :] = [X, Y, Z]

plt.style.use('dark_background')
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def update(frame):
    ax.cla()
    ax.set_xlim([-200, 200])
    ax.set_ylim([-200, 200])
    ax.set_zlim([-200, 200])
    ax.grid(False)
    ax.axis('off')
    colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
    for i in range(num_bodies):
        x = data[i, :frame+1, 0]
        y = data[i, :frame+1, 1]
        z = data[i, :frame+1, 2]
        color = colors [i]
        ax.plot(x, y, z, label=f'Body {i + 1}', c=color)
        ax.scatter(x[-1], y[-1], z[-1], s=5, marker='o', label=f'Body {i + 1}', c=color)

ani = FuncAnimation(fig, update, frames=range(num_points), interval = 1, repeat = False)

ax.legend()
plt.show()
