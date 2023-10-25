import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys

n = len(sys.argv)

filename = "conservation_h.txt"
if(n>1):
    filename = sys.argv[1]

data = pd.read_csv(filename);
if(len(data)==0):
    exit(-1)
plt.figure(1)
x=np.transpose(np.linspace(1,len(data),num=len(data)))

plt.plot(x,data["h_x"])
plt.plot(x,data["h_y"])
plt.plot(x,data["h_z"])
plt.legend(["h_x","h_y","h_z"])
plt.xlabel("Iteration")
plt.ylabel("Angular momentum")
plt.grid()
plt.show()

