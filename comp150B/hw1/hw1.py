import numpy as np
import scipy.special as sp
import matplotlib.pyplot as plot
from scipy.stats import norm

def draw_GP_prior_samples_at_x_grid(x_grid_G, mean_func, cov_func, random_seed=42, n_samples=5):
    # Mean and covariance calculation
    mean = mean_func(x_grid_G)
    cov = cov_func(x_grid_G, x_grid_G)

    # Use consistent random number generator for reproducibility
    prng = np.random.RandomState(int(random_seed))
    f_SG = prng.multivariate_normal(mean, cov, n_samples)
    return f_SG

def draw_GP_posterior_samples_at_x_grid(x_train_N, y_train_N, x_grid_G, mean_func, cov_func,
    sigma=0.1, random_seed=42, n_samples=5):
    # Mean and convariance calculation
    kxa = cov_func(x_train_N, x_grid_G)
    kax = cov_func(x_grid_G, x_train_N)
    kaa = cov_func(x_grid_G, x_grid_G)
    kxx = cov_func(x_train_N, x_train_N)
    inv = np.linalg.inv(kxx + np.identity(len(x_train_N)) * (sigma**2))
    mean = np.matmul(np.matmul(kax, inv), y_train_N) + 5
    cov = kaa - np.matmul(kax, np.matmul(inv, kxa))
   

    # Use consistent random number generator for reproducibility
    prng = np.random.RandomState(int(random_seed))
    f_SG = prng.multivariate_normal(mean, cov, n_samples)
    return f_SG

def sqexp_kernel_func(x1, x2):
    lx1 = len(x1)
    lx2 = len(x2)
    mat = np.zeros((lx1, lx2))
    for i in range(lx1):
        for j in range(lx2):
            mat[i, j] = np.exp(-((x1[i] - x2[j])**2)/(2*l*l))
    return mat	

def matern_kernel_func(x1, x2):
    lx1 = len(x1)
    lx2 = len(x2)
    mat = np.zeros((lx1, lx2))
    for i in range(lx1):
        for j in range(lx2):
            # Small number added to avoid NaNs on diagonal
            temp = (((2 * v)**.5) * abs(x1[i] - x2[j]) / l) + .000000000001
            mat[i, j] = (2**(1 - v)) * (temp**v) * sp.kv(v, temp) / sp.gamma(v)
    return mat 

def zero_mean_func(x):
    return np.zeros(len(x))

# Hyperparameters
lvals = [.25, 1, 4]
vvals = [.5, 2, 8]

# Gridpoints
x_grid_G = np.linspace(-20, 20, 201)

# Training data
x_train_N = np.asarray([-2.,    -1.8,   -1.,  1.,  1.8,     2.])
y_train_N = np.asarray([-3.,  0.2224,    3.,  3.,  0.2224, -3.])

# Graph prior samples using sqexp and l values
for i in range(len(lvals)):
    l = lvals[i]
    f_SG = draw_GP_prior_samples_at_x_grid(x_grid_G, zero_mean_func, sqexp_kernel_func)
    plot.subplot(131+i)
    for j in range(len(f_SG)):
        plot.plot(x_grid_G, f_SG[j,:])
    plot.title("l = " + str(l))
plot.show()

# Graph prior samples using matern and l and v values
for i in range(len(lvals)):
    l = lvals[i]
    for j in range(len(vvals)):
        v = vvals[j]
        f_SG = draw_GP_prior_samples_at_x_grid(x_grid_G, zero_mean_func, matern_kernel_func)
        plot.subplot(331 + (3 * i) + j)
        for k in range(len(f_SG)):
            plot.plot(x_grid_G, f_SG[k,:])
        plot.title("l = " + str(l) + ", v = " + str(v))
plot.show()

# Graph posterior samples using sqexp and l values
for i in range(len(lvals)):
    l = lvals[i]
    f_SG = draw_GP_posterior_samples_at_x_grid(x_train_N, y_train_N, x_grid_G, zero_mean_func,
        sqexp_kernel_func)
    plot.subplot(131+i)
    for j in range(len(f_SG)):
        plot.plot(x_grid_G, f_SG[j,:])
    plot.title("l = " + str(l))
plot.show()

# Graph posterior samples using matern and l and v values
for i in range(len(lvals)):
    l = lvals[i]
    for j in range(len(vvals)):
        v = vvals[j]
        f_SG = draw_GP_posterior_samples_at_x_grid(x_train_N, y_train_N, x_grid_G, zero_mean_func,
        matern_kernel_func)
        plot.subplot(331 + (3 * i) + j)
        for k in range(len(f_SG)):
            plot.plot(x_grid_G, f_SG[k,:])
        plot.title("l = " + str(l) + ", v = " + str(v))
plot.show()
