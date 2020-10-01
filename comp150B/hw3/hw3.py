import copy
import numpy as np
import matplotlib.pyplot as plot
import scipy as sp
import autograd as ag
import autograd.scipy as ag_sp
import autograd.numpy as ag_np
import random

# Network functions
def initialize_nn_params(architecture, prng):
    nn_params = []
    for n_in, n_out in zip(architecture[:-1], architecture[1:]):
        nn_params.append(
            dict(
                w = np.asmatrix(prng.normal(0, 1, (n_in, n_out))),
                b = np.asmatrix(prng.normal(0, 1, (n_out)))
            ))
    return nn_params

def initialize_sigmas(architecture, prng):
    nn_params = []
    for n_in, n_out in zip(architecture[:-1], architecture[1:]):
        nn_params.append(
            dict( 
                w = np.asmatrix(prng.normal(1, 0, (n_in, n_out))),
                b = np.asmatrix(prng.normal(1, 0, (n_out)))
            ))
    return nn_params

def feed_forward(x, nn_params, activation_func):
    for layer_id, layer_dict in enumerate(nn_params):
        if layer_id == 0:
            if x.ndim > 1:
                in_arr = x
            else:
                if x.size == nn_params[0]['w'].shape[0]:
                    in_arr = x[ag_np.newaxis,:]
                else:
                    in_arr = x[:,ag_np.newaxis]
        else:
            in_arr = activation_func(out_arr)
        out_arr = ag_np.dot(in_arr, layer_dict['w']) + layer_dict['b']
    return ag_np.squeeze(out_arr)

def update_model(grad, nn_params, step_size):
    for i in range(len(nn_params)):
        nn_params[i]['w'] = nn_params[i]['w'] + np.multiply(step_size, grad[i]['w'])
        nn_params[i]['b'] = nn_params[i]['b'] + np.multiply(step_size, grad[i]['b'])
    return nn_params

def flatten(nn_params):
    vec = []
    for i in range(len(nn_params)):
        vec = [*vec, *(np.asarray(nn_params[i]['w'])).flatten()]
        vec = [*vec, *(np.asarray(nn_params[i]['b'])).flatten()]
    return np.asarray(vec)

def tanh(x):
    return ag_np.tanh(x)

def elbo_est(x, y, architecture, means, sigmas, n_samples, prng):
    total = 0
    for i in range(n_samples):
        nn_params = initialize_nn_params(architecture, prng)
        log_prior = np.sum(sp.stats.norm.logpdf(flatten(nn_params), 0, 1))
        log_likely = np.sum(sp.stats.norm.logpdf(y, feed_forward(x, nn_params, tanh), .1))
        log_q = np.sum(sp.stats.norm.logpdf(flatten(nn_params), flatten(means), np.power(flatten(sigmas), 2)))
        elbo = log_q - log_likely - log_prior
        total = total + elbo 
    return total / n_samples

def elbo_grad_est(x, y, architecture, means, sigmas, n_samples, prng):
    step = .001
    mean_grads = initialize_sigmas(architecture, prng)
    sigma_grads = initialize_sigmas(architecture, prng)
    for i in range(len(means)):
        mw_layer = means[i]['w']
        mb_layer = means[i]['b']
        sw_layer = sigmas[i]['w']
        sb_layer = sigmas[i]['b']
        for j in range(mw_layer.shape[0]):
            for k in range(mw_layer.shape[1]):
                means2 = copy.deepcopy(means)
                means2[i]['w'][j, k] = means2[i]['w'][j, k] + step
                est1 = elbo_est(x, y, architecture, means, sigmas, n_samples, prng)
                est2 = elbo_est(x, y, architecture, means2, sigmas, n_samples, prng)
                mean_grads[i]['w'][j, k] = (est2 - est1)/step
        for j in range(sw_layer.shape[0]):
            for k in range(sw_layer.shape[1]):
                sigmas2 = copy.deepcopy(sigmas)
                sigmas2[i]['w'][j, k] = sigmas2[i]['w'][j, k] + step
                est1 = elbo_est(x, y, architecture, means, sigmas, n_samples, prng)
                est2 = elbo_est(x, y, architecture, means, sigmas2, n_samples, prng)
                sigma_grads[i]['w'][j, k] = (est2 - est1)/step
        for j in range(mb_layer.shape[1]):
            means2 = copy.deepcopy(means)
            means2[i]['b'][0, j] = means2[i]['b'][0, j] + step 
            est1 = elbo_est(x, y, architecture, means, sigmas, n_samples, prng)
            est2 = elbo_est(x, y, architecture, means2, sigmas, n_samples, prng)
            mean_grads[i]['b'][0, j] = (est2 - est1)/step
        for j in range(sb_layer.shape[1]):
            sigmas2 = copy.deepcopy(sigmas)
            sigmas2[i]['b'][0, j] = sigmas2[i]['b'][0, j] + step       
            est1 = elbo_est(x, y, architecture, means, sigmas, n_samples, prng)
            est2 = elbo_est(x, y, architecture, means, sigmas2, n_samples, prng)
            sigma_grads[i]['b'][0, j] = (est2 - est1)/step

    return mean_grads, sigma_grads

prng = np.random.RandomState(42)

# Problem 1
x_train_N = np.asarray([-5.0,  -2.50, 0.00, 2.50, 5.0])
y_train_N = np.asarray([-4.91, -2.48, 0.05, 2.61, 5.09])
wms = np.linspace(-3.0, 5.0, 20)
architecture = [1, 1]


"""

# Graph 1a
fig1, ax1 = plot.subplots(1, 4)
for i in range(4):
    elbos = []
    n_samples = np.power(10, i)
    for j in range(len(wms)):
        means = [dict(w = np.asmatrix([wms[j]]), b = np.asmatrix([0.0]))]
        sigmas = [dict(w = np.asmatrix([.1]), b = np.asmatrix([.1]))]
        est = elbo_est(x_train_N, y_train_N, architecture, means, sigmas, n_samples, prng)
        elbos.append(est)
    ax1[i].scatter(wms, elbos)
plot.show()


# Graph 1c
fig2, ax2 = plot.subplots(1, 4)
for i in range(4):
    elbo_grads = []
    n_samples = np.power(10, i)
    for j in range(len(wms)):
        means = [dict(w = np.asmatrix([wms[j]]), b = np.asmatrix([0.0]))]
        sigmas = [dict(w = np.asmatrix([.1]), b = np.asmatrix([.1]))]
        mean_grads, sigma_grads = elbo_grad_est(x_train_N, y_train_N, architecture, means, sigmas, n_samples, prng)
        elbo_grads.append(mean_grads[0]['w'])
    ax2[i].scatter(wms, elbo_grads)
plot.show()

"""

# Problem 2
x_train_N = np.asarray([-2.,    -1.8,   -1.,  1.,  1.8,     2.])
y_train_N = np.asarray([-2.,  1.2224,    4.,  4.,  1.2224, -2.])
x_grid_G = np.linspace(-20, 20, 200)
architecture = [1, 10, 1]

lr = .0000001
iters = 20

"""
# Graph 2a
fig3, ax3 = plot.subplots(1, 3)
for i in range(3):
    elbos = []
    means = initialize_nn_params(architecture, prng)
    sigmas = initialize_sigmas(architecture, prng)
    for j in range(iters):
        print(j)
        est = elbo_est(x_train_N, y_train_N, architecture, means, sigmas, 10, prng)
        mean_grads, sigma_grads = elbo_grad_est(x_train_N, y_train_N, architecture, means, sigmas, 10, prng) 
        means = update_model(mean_grads, means, lr)
        sigmas = update_model(sigma_grads, sigmas, lr)
        elbos.append(est)
    ax3[i].plot(range(iters), elbos)
plot.show()

"""

# Graph 2b
fig4, ax4 = plot.subplots(1, 3)
for i in range(3):
    means = initialize_nn_params(architecture, prng)
    sigmas = initialize_sigmas(architecture, prng)
    for j in range(iters):
        mean_grads, sigma_grads = elbo_grad_est(x_train_N, y_train_N, architecture, means, sigmas, 10, prng)
        means = update_model(mean_grads, means, lr)
        sigmas = update_model(sigma_grads, sigmas, lr)
    y = feed_forward(x_grid_G, means, tanh)
    ax4[i].plot(x_grid_G, np.transpose(y))
    print(y)
plot.show()
    
