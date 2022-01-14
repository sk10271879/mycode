import numpy as np
import matplotlib.pyplot as plt

x=np.arange(-1.0,1.0,0.002)
y0=np.exp(x)+np.power(x,2)+x**3

plt.plot(x,y0)
y1=x

plt.plot(x,y1)
s=[0.1, 0.2, 0.3, 0.4, ]
t=[-0.2, -0.3, -0.4, -0.5, ]
plt.scatter(s,t)
plt.savefig("plot.png")
plt.show()
