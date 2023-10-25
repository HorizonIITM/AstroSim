import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import numpy as np

file_path = "3BC.txt"

with open(file_path, 'r') as file:
    lines = file.readlines()

num_bodies = int(len(lines[0].strip().split(','))) //3
num_points = int(len(lines))

data = np.zeros((num_bodies, num_points, 3))

for i, line in enumerate(lines):
    values = line.strip().split(',')
    for j in range(num_bodies):
        X, Y, Z = map(float, values[j * 3: (j + 1) * 3])
        data[j, i :] = [X, Y, Z]

plt.style.use('dark_background')
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.grid(False)
ax.axis('off')

for i in range(num_bodies):
    ax.plot(data[i, :, 0], data[i, :, 1], data[i, :, 2], label=f'Body {i+1}')

ax.legend()
plt.show()

