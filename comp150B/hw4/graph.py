import numpy as np
import matplotlib.pyplot as plot

ae = []
vae = []
ae.append(np.loadtxt(open('report/VAE-arch=[32]-lr=0.001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))
ae.append(np.loadtxt(open('report/VAE-arch=[128]-lr=0.001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))
ae.append(np.loadtxt(open('report/VAE-arch=[512]-lr=0.001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))
vae.append(np.loadtxt(open('report/VAE-arch=[32]-lr=0.0001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))
vae.append(np.loadtxt(open('report/VAE-arch=[128]-lr=0.0001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))
vae.append(np.loadtxt(open('report/VAE-arch=[512]-lr=0.0001_perf_metrics.csv', "rb"), delimiter=",", skiprows=1, usecols=(0, 1, 2, 3, 4, 5, 6)))


# Problem 1A
fig1, ax1= plot.subplots(1, 3)
for i in range(3):
    x = ae[i][:, 0]
    train = ae[i][:, 3]
    test = ae[i][:, 6]
    ax1[i].plot(x, train, 'b-', label='train')    
    ax1[i].plot(x, test, 'r--', label='test')
    ax1[i].legend()
    ax1[i].set_title("BCE vs Epoch")
plot.show()


# Problem 1B
fig2, ax2= plot.subplots(1, 3)
for i in range(3):
    x = ae[i][:, 0]
    train = ae[i][:, 2]
    test = ae[i][:, 5]
    ax2[i].plot(x, train, 'b-', label='train')
    ax2[i].plot(x, test, 'r--', label='test')
    ax2[i].legend()
    ax2[i].set_title("L1 Error vs Epoch")
plot.show()  

# Problem 2A
fig3, ax3= plot.subplots(1, 3)
for i in range(3):
    x = vae[i][:, 0]
    train = vae[i][:, 3]
    test = vae[i][:, 6]
    ax3[i].plot(x, train, 'b-', label='train')
    ax3[i].plot(x, test, 'r--', label='test')
    ax3[i].legend()
    ax3[i].set_title("BCE vs Epoch")
plot.show()   

# Problem 2B
fig4, ax4= plot.subplots(1, 3)
for i in range(3):
    x = vae[i][:, 0]
    train = vae[i][:, 2]
    test = vae[i][:, 5]
    ax4[i].plot(x, train, 'b-', label='train')
    ax4[i].plot(x, test, 'r--', label='test')
    ax4[i].legend()
    ax4[i].set_title("L1 Error vs Epoch")
plot.show()  
