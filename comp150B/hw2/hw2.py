import copy
import numpy as np
import matplotlib.pyplot as plot
import autograd
from autograd.scipy import stats as ag_stats
import autograd.numpy as ag_np
import random

# Network functions
def initialize_nn_params(architecture, prng):
    nn_params = []
    for n_in, n_out in zip(architecture[:-1], architecture[1:]):
        nn_params.append(
            dict(
                w = prng.normal(0, 1, (n_in, n_out)),
                b = prng.normal(0, 1, (n_out))
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

# Activation functions
def relu(x):
    return ag_np.maximum(0, x)

def tanh(x):
    return ag_np.tanh(x)

def sqexp(x):
    return ag_np.exp(-ag_np.power(x,2))

# Energy calculations
def calc_kinetic_energy(momentum):
    total = 0
    for i in range(len(momentum)):
        total += np.sum(np.power(momentum[i]['w'], 2))
        total += np.sum(np.power(momentum[i]['b'], 2))
    return total / 2

def calc_potential_energy(nn_params):
    x_train_N = ag_np.asarray([-2.,    -1.8,   -1.,  1.,  1.8,     2.])
    y_train_N = ag_np.asarray([-2.,  1.2224,    4.,  4.,  1.2224, -2.])
    total = 0
    for i in range(len(nn_params)):
        total += ag_np.sum(ag_stats.norm.logpdf(nn_params[i]['w']))
        total += ag_np.sum(ag_stats.norm.logpdf(nn_params[i]['b']))    
    y = feed_forward(x_train_N, nn_params, tanh)
    total += ag_np.sum(ag_stats.norm.logpdf(y_train_N, y, .1)) 
    return -total

def calc_grad_potential_energy(nn_params):
    g = autograd.grad(calc_potential_energy)
    return g(nn_params)

# Update functions
def update_momentum(momentum, nn_params, step_size, full_step):
    if(full_step):
        div = 1
    else:  
        div = 2
 
    for i in range(len(nn_params)):
        grad = calc_grad_potential_energy(nn_params)
        momentum[i]['w'] = momentum[i]['w'] - step_size * grad[i]['w'] / div
        momentum[i]['b'] = momentum[i]['b'] - step_size * grad[i]['b'] / div
    return momentum

def update_model(momentum, nn_params, step_size):
    for i in range(len(nn_params)):
        nn_params[i]['w'] = nn_params[i]['w'] + np.multiply(step_size, momentum[i]['w'])
        nn_params[i]['b'] = nn_params[i]['b'] + np.multiply(step_size, momentum[i]['b'])
    return nn_params

def negate_momentum(momentum):
    for i in range(len(momentum)):
        momentum[i]['w'] = -momentum[i]['w']
        momentum[i]['b'] = -momentum[i]['b']
    return momentum

# HMC functions
def make_proposal(cur_nn_params, cur_momentum, n_leapfrog_steps, step_size): 
    prop_nn_params = copy.deepcopy(cur_nn_params)
    prop_momentum = copy.deepcopy(cur_momentum)
   
    prop_momentum = update_momentum(prop_momentum, prop_nn_params, step_size, False)
    for i in range(n_leapfrog_steps):
        prop_nn_params = update_model(prop_momentum, prop_nn_params, step_size)
        if i < (n_leapfrog_steps - 1):
            prop_momentum = update_momentum(prop_momentum, prop_nn_params, step_size, True)
        else:
            prop_momentum = update_momentum(prop_momentum, prop_nn_params, step_size, False)
    prop_momentum = negate_momentum(prop_momentum) 
    return prop_nn_params, prop_momentum

def run_HMC_sampler(architecture, n_hmc_iters, random_seed=42):
    n_leapfrog_steps = 1
    step_size = .01

    # Create random-number-generator with specific seed for reproducibility
    prng = np.random.RandomState(int(random_seed))

    # Set initial bnn params
    cur_bnn_params = initialize_nn_params(architecture, prng)
    cur_potential_energy = calc_potential_energy(cur_bnn_params)

    bnn_samples = list()
    potentials = list()
    kinetics = list()

    n_accept = 0
    for t in range(n_hmc_iters):
        cur_momentum_vec = initialize_nn_params(architecture, prng)
        cur_kinetic_energy = calc_kinetic_energy(cur_momentum_vec)

        # Create PROPOSED configuration
        prop_bnn_params, prop_momentum_vec = make_proposal(cur_bnn_params, cur_momentum_vec,
         n_leapfrog_steps, step_size)
        
        prop_potential_energy = calc_potential_energy(prop_bnn_params)
        prop_kinetic_energy = calc_kinetic_energy(prop_momentum_vec)

        accept_proba = np.exp(cur_potential_energy + cur_kinetic_energy - prop_potential_energy - prop_kinetic_energy)
        
        # Draw random value from (0,1) to determine if we accept or not
        if prng.rand() < accept_proba:
            # If here, we accepted the proposal
            n_accept += 1
            cur_bnn_params = prop_bnn_params
            cur_potential_energy = prop_potential_energy
            cur_kinetic_energy = prop_kinetic_energy
 
        # Update list of samples from "posterior"
        bnn_samples.append(cur_bnn_params)
        potentials.append(cur_potential_energy)
        kinetics.append(cur_kinetic_energy)       

        # Print some diagnostics every 50 iters
        if t < 5 or ((t+1) % 50 == 0) or (t+1) == n_hmc_iters:
            accept_rate = float(n_accept) / float(t+1)
            print("iter %6d/%d | accept_rate %.3f" % (
                t+1, n_hmc_iters, accept_rate))

    return (
        bnn_samples,
        potentials,
        kinetics,
        dict(
            n_accept=n_accept,
            n_hmc_iters=n_hmc_iters,
            accept_rate=accept_rate),
        )

# Parameter definitions
G = 201
x_grid_G = np.linspace(-20, 20, G)
x_train_N = np.asarray([-2.,    -1.8,   -1.,  1.,  1.8,     2.])
y_train_N = np.asarray([-2.,  1.2224,    4.,  4.,  1.2224, -2.])
architectures = [[1, 2, 1], [1, 10, 1], [1, 2, 2, 1], [1, 10, 10, 1]]
activation_funcs = [relu, tanh, sqexp]

def sample_from_prior(x, architecture, activation_func, random_seed=42, num_samples=7):
    samples = np.zeros((num_samples, len(x)))
    prng = np.random.RandomState(int(random_seed))
    for i in range(num_samples):
        nn_params = initialize_nn_params(architecture, prng)
        fx = feed_forward(x, nn_params, activation_func)
        samples[i] = fx
    return samples

# Problem 1 graph
fig1 = plot.figure(1)
for i in range(len(architectures)):
    arch = architectures[i]
    for j in range(len(activation_funcs)):
        func = activation_funcs[j]
        f_SG = sample_from_prior(x_grid_G, arch, func)
        fig1.add_subplot(4, 3, (3 * i + j + 1))
        for k in range(len(f_SG)):
            plot.plot(x_grid_G, f_SG[k,:])
plot.show()

burnin = 250
iters = 1000

# Problem 2a graph
fig2, ax2 = plot.subplots(1, 2, sharey=True)
for i in range(3):
    samples, U, K, info = run_HMC_sampler([1, 1], iters + burnin, 42 * (i + 1))
    ax2[0].plot(range(iters + burnin), U)

ax2[1].plot(range(iters), U[250:])
plot.show()

#Problem 2b graph
fig3, ax3 = plot.subplots(1, 4)
for i in range(4):
    samples, U, K, info = run_HMC_sampler([1, 1], iters + burnin, 42 * (i + 1))
    n_samples = 10
    rands = random.sample(range(burnin, iters + burnin), n_samples)
    for j in range(n_samples):
        nn_params = samples[rands[j]]
        f = feed_forward(x_grid_G, nn_params, tanh)
        ax3[i].plot(x_grid_G, f)
plot.show()

#Problem 2c graph
fig4, ax4 = plot.subplots(1, 4)
for i in range(4):
    samples, U, K, info = run_HMC_sampler([1, 1], iters + burnin, 42 * (i + 1))
    f = np.zeros((G, iters))
    for j in range(iters):
        nn_params = samples[burnin + j]
        f[:, j] = feed_forward(x_grid_G, nn_params, tanh)
    mean = np.mean(f, axis=1)
    std = np.std(f, axis=1)
    ax4[i].plot(x_grid_G, mean)
    ax4[i].fill_between(x_grid_G, mean+std, mean-std, facecolor='blue', alpha=.5)
    ax4[i].fill_between(x_grid_G, mean + 2*std, mean - 2*std, facecolor='blue', alpha=.25)
plot.show()

burnin = 500
iters = 2000

#Problem 3b graph
fig5 = plot.figure(5)
for i in range(3):
    fig5.add_subplot(1, 3, i + 1)
    samples, U, K, info = run_HMC_sampler([1, 10, 1], iters + burnin, 42 * (i + 1))
    n_samples = 10
    rands = random.sample(range(burnin, iters + burnin), n_samples)
    for j in range(n_samples):
        nn_params = samples[rands[j]]
        f = feed_forward(x_grid_G, nn_params, tanh)
        plot.plot(x_grid_G, f)
plot.show()

#Problem 3c graph
fig6, ax6= plot.subplots(1, 3)
for i in range(3):
    samples, U, K, info = run_HMC_sampler([1, 10, 1], iters + burnin, 42 * (i + 1))
    f = np.zeros((G, iters))
    for j in range(iters):
        nn_params = samples[burnin + j]
        f[:, j] = feed_forward(x_grid_G, nn_params, tanh)
    mean = np.mean(f, axis=1)
    std = np.std(f, axis=1)
    ax6[i].plot(x_grid_G, mean)
    ax6[i].fill_between(x_grid_G, mean+std, mean-std, facecolor='blue', alpha=.5)
    ax6[i].fill_between(x_grid_G, mean + 2*std, mean - 2*std, facecolor='blue', alpha=.25)
plot.show()
