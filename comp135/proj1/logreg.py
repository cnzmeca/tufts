import sys
import matplotlib.pyplot as plt
import numpy as np
import random as rand
import pickle

class MyLogisticReg:
    def __init__(self, fts, low, hi, grad, reg, step, term):
        self.w0 = 0
        self.w_vec = np.full((fts), 0, dtype=float)
        self.low = low
        self.hi = hi
        self.grad = grad
        self.reg = reg
        self.step = step
        self.term = term

    def fit(self, X, Y):
        obj = []
        while True:
            # Gets gradient based on GD or SGD
            if (self.grad == 'SGD'):
                S = rand.sample(list(range(0, X.shape[0])), 10)
                obj += [self.L(X[S], Y[S])]
                grad = self.gradient(X[S], Y[S])
            else:
                obj += [self.L(X, Y)]
                grad = self.gradient(X, Y)

            #Updates W and W0
            self.w_vec -= (self.step * grad[0])
            self.w0 -= (self.step * grad[1])
                
            # Calculates termination condition
            diff = (np.sum(np.absolute(grad[0])) +
            np.absolute(grad[1]))/(grad[0].shape[0] + 1)
            if (diff < self.term):
                # Returns objective vector and random feature W
                return (obj, np.absolute(self.w_vec[-1]))

    # eta formula
    def eta(self, X):
        eta = np.sum(X * self.w_vec, axis=1) + self.w0
        return eta

    # log-likelihood formula
    def a(self, X, Y):
        a = (Y * self.eta(X)) - np.log(1 + np.exp(self.eta(X)))
        return a

    # Loss function formula
    def L(self, X, Y):
        L = (-(np.sum(self.a(X, Y)))
        + (self.reg * self.w_vec * self.w_vec.T))/(X.shape[0])
        return L

    # Hardcoded gradient formula
    def gradient(self, X, Y):
        N = X.shape[0]
        u = np.exp(self.eta(X))/(1 + np.exp(self.eta(X)))
        dw0 = -np.sum(Y - u)
        dw_vec = (-np.sum(((X.T * (Y - u))), axis=1)
        + (2 * self.reg * self.w_vec))
        return (dw_vec/N, dw0/N) 


    def predict(self, X):
        eta = self.eta(X)
        Ypred = np.zeros_like(eta)
        # Predicts low if eta <= 0 and hi if eta > 0
        for i in range(0, eta.shape[0]):
            if (eta[i] <= 0):
                Ypred[i] = self.low
            else:
                Ypred[i] = self.hi
        return Ypred

def evaluate(Ytest, Ypred):
    error = 1 - (np.sum(np.equal(Ytest, Ypred).astype(np.float))/Ytest.size)
    return error

# Reads in data given file name
def read(filename):
    with open(filename, 'r') as file:
        data = []
        for line in file.readlines():
            data.append(line.strip('\n').split(','))
    return np.array([map(float, x) for x in data[1:]])

# Converts labels from original to binary and stores original labels as low + hi
def binarize(Y):
    low = np.amin(Y)
    hi = np.amax(Y)
    for i in range(0, Y.shape[0]):
        if (Y[i] == low):
            Y[i] = 0
        else:
            Y[i] = 1
        return (Y, low, hi)

def ex1(X, Y, argv):
        Xtrain = np.copy(X)
        Ytrain = np.copy(Y)

        (Ytrain, low, hi) = binarize(Ytrain)

        model = MyLogisticReg(X.shape[1], low, hi, argv[3],
        float(argv[4]), float(argv[5]), float(argv[6])) 
        obj = model.fit(Xtrain, Ytrain)[0]
    
        # Plots iteration number vs objective vector
        plt.plot(range(0, len(obj)), obj)
        plt.xlabel('Iteration #')
        plt.ylabel('Objective')
        plt.title(argv[4])
        plt.show()

def ex2(X, Y, argv):
    # Regularizer values
    regs = [0, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100, 1000]
    errs = []
    rands = []
    S = rand.sample(list(range(0, X.shape[0])), int(X.shape[0] * .7))
    S2 = [i for i in range(0, X.shape[0]) if i not in S]

    Xtrain = X[S]
    Xtest = X[S2]
    Ytrain = Y[S]
    Ytest = Y[S2]

    (Ytrain, low, hi) = binarize(Ytrain)

    # Calculates error and random feature weight for each reg value
    for i in range(0, len(regs)):
        model = MyLogisticReg(X.shape[1], low, hi, argv[3], regs[i],
        float(argv[5]), float(argv[6]))
        random = model.fit(Xtrain, Ytrain)[1]
        Ypred = model.predict(Xtest)
        error = evaluate(Ytest, Ypred)
        errs += [error]
        rands += [random]

    # Plots regularizer value vs error logarithmically
    plt.plot(regs, errs)
    plt.xlabel('Regularizer Values')
    plt.ylabel('% Error')
    plt.xscale('symlog', linthreshx=0.01)
    plt.title(argv[1])
    plt.show()

    # Plots regularizer value vs random feature weight logarithmically
    plt.plot(regs, rands)
    plt.xlabel('Regularizer Values')
    plt.ylabel('Random Feature weight')
    plt.xscale('symlog', linthreshx=0.01)
    plt.title(argv[1])
    plt.show()

def ex3(X, Y, argv):
    Xtrain = np.copy(X)
    Ytrain = np.copy(Y)

    (Ytrain, low, hi) = binarize(Ytrain)
    
    model = MyLogisticReg(X.shape[1], low, hi, argv[3],
    float(argv[4]), float(argv[5]), float(argv[6]))
    model.fit(Xtrain, Ytrain)
    
    # Pickles model
    if (argv[1] == "titanic.train.csv"):
        pickle.dump(model, open("titanic_classifier.pkl", "wb"))    
    else:
        pickle.dump(model, open("mnist_classifier.pkl", "wb"))  

def ex4(X, Y, argv):
    k = argv[7]
    errs = []
    # k fold cross validation
    for i in range(10):
        S = range(X.shape[0])[i::10]
        S2 = [n for n in range(X.shape[0]) if n not in S]
    
        Xtrain = X[S2]
        Xtest = X[S]
        Ytrain = Y[S2]
        Ytest = Y[S]

        (Ytrain, low, hi) = binarize(Ytrain)

        model = MyLogisticReg(X.shape[1], low, hi, argv[3],
        float(argv[4]), float(argv[5]), float(argv[6]))
        model.fit(Xtrain, Ytrain)
        Ypred = model.predict(Xtest)
        error = evaluate(Ytest, Ypred)
        errs += [error]

    # Prints error as mean +/- std
    errs = np.array(errs)   
    avg = np.mean(errs)
    std = np.std(errs)
    print('Error: {} +/- {}'.format(avg, std))

def main (argv):
    data = read(argv[1])
    X = data[:,1:]
    Y = data[:,0]
    if ((argv[2]) == "True"):
        X /= np.amax(X)

    ex1(X, Y, argv)
    ex2(X, Y, argv)
    ex3(X, Y, argv)
    ex4(X, Y, argv) 

if __name__ == '__main__':
    main(sys.argv)
