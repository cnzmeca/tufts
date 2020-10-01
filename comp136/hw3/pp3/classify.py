import csv
import numpy as np
import matplotlib.pyplot as plt
import math
from sklearn.gaussian_process import GaussianProcessClassifier as GPC
from sklearn.gaussian_process.kernels import RBF

def read_data(filename):
        data = []
        with open(filename) as csvfile:
                reader = csv.reader(csvfile, quoting=csv.QUOTE_NONNUMERIC)
                for row in reader:
                        data.append(row)
        return np.array(data)

def sigmoid(x):
	return np.divide(1, (1 + np.exp(-x)))

def gen(x_train, x_test, y_train, y_test):
	n = float(len(y_train))
	n1 = float(sum(y_train))
	n2 = float(n - n1)
	xc1 = x_train[np.nonzero(y_train)[0], :]
	xc2 = x_train[np.where(y_train == 0)[0], :]
	u1 = np.mean(xc1, axis = 0) 
	u2 = np.mean(xc2, axis = 0)
	ut1 = np.transpose(u1)
	ut2 = np.transpose(u2)
	s1 = np.outer(np.sum((xc1 - u1), axis = 0), np.sum((xc1 - u1), axis = 0)) / n1
	s2 = np.outer(np.sum((xc2 - u2), axis = 0), np.sum((xc2 - u2), axis = 0)) / n2
	s = (n1 * s1 + n2 * s2) / n
	si = np.linalg.inv(s + (.000000001 * np.identity(len(s))))
	w = np.dot(si, (u1 - u2))
	w0 = (np.dot(ut2, np.dot(si, u2)) - np.dot(ut1, np.dot(si, u1))) / 2
	
	y_pred = []
	for x in x_test:
		prob = sigmoid(np.dot(np.transpose(w), x) + w0)
		if prob >= .5:
			y_pred.append(1)
		else:
			y_pred.append(0)
	
	error = np.mean(np.absolute(np.array(y_pred) - np.transpose(y_test)[0]))
	return error

def dis(x_train, x_test, y_train, y_test, a):
	x_train = np.append(x_train, np.transpose(np.array([np.ones(len(x_train))])), axis=1)
	x_test = np.append(x_test, np.transpose(np.array([np.ones(len(x_test))])), axis=1)
	
	w = np.zeros(len(x_train[0]))
	for k in range(10):
		s = sigmoid(np.dot(x_train, w))
		r = np.diag(np.transpose(s) * (1 - s))
		sn = np.linalg.inv(np.dot(np.transpose(x_train), np.dot(r, x_train)) + (a * np.identity(len(w))))
		w = w - np.dot(sn, (np.dot(np.transpose(x_train), s - np.transpose(y_train)[0]) + (a * w)))
	y_prob = []
	for x in x_test:
		e = np.dot(np.transpose(x), np.dot(sn, x))
		u = np.dot(np.transpose(w), x)
		prob = sigmoid(u/((1 + (math.pi * e / 8))**(1/2)))
		y_prob.append(prob)

	y_pred = []
	for y in y_prob:
		if y >= .5:
			y_pred.append(1)
		else:
			y_pred.append(0)
	error = np.mean(np.absolute(np.array(y_pred) - np.transpose(y_test)[0]))
	return error

def task1(feature_sets, label_sets):
	sets = ["A", "B", "crashes", "diabetes", "ionosphere"]
	for i in range(5):
		n = len(label_sets[i])
		m = np.linspace(10, .6 * n, num = 10, dtype = int)
		div = int(n * .4)
		x_train = feature_sets[i][div:]
                x_test = feature_sets[i][:div]
                y_train = label_sets[i][div:]
                y_test = label_sets[i][:div]
	
		gen_errors = []
		dis_errors = []	
		for j in range(10):
			gen_errors.append(gen(x_train[:m[j]-1], x_test, y_train[:m[j]-1], y_test))
			dis_errors.append(dis(x_train[:m[j]-1], x_test, y_train[:m[j]-1], y_test, .0000000001))
		plt.legend()
                plt.ylabel("Error")
                plt.xlabel("M value")
                plt.title(sets[i])
                plt.plot(m, gen_errors, label = "Generative")
                plt.plot(m, dis_errors, label = "Discriminative")
		plt.show()
	return

def task2(feature_sets, label_sets):
	sets = ["A", "B", "crashes", "diabetes", "ionosphere"]
        for i in range(5):
		x = feature_sets[i]
		y = label_sets[i]
		x = np.append(x, np.transpose(np.array([np.ones(len(x))])), axis=1)
		a = 1
		for l in range(10):
			w = np.zeros(len(x[0]))
        		for k in range(10):
                		s = sigmoid(np.dot(x, w))
                		r = np.diag(np.transpose(s) * (1 - s))
                		sn = np.linalg.inv(np.dot(np.transpose(x), np.dot(r, x)) + ((a + .000000001) * np.identity(len(w))))
                		w = w - np.dot(sn, (np.dot(np.transpose(x), s - np.transpose(y)[0]) + (a * w)))
			
			lam = np.real(np.linalg.eigvals(np.dot(np.transpose(x), np.dot(r, x))))
			gam = 0	
			for d in range(len(lam)):
				gam += lam[d]/float(lam[d] + a)
			a = gam/np.linalg.norm(w, ord = 2)
		
		n = len(label_sets[i])
                m = np.linspace(10, .6 * n, num = 10, dtype = int)
                div = int(n * .4)
                x_train = feature_sets[i][div:]
                x_test = feature_sets[i][:div]
                y_train = label_sets[i][div:]
                y_test = label_sets[i][:div]

                dis_errors = []
                for j in range(10):
                        dis_errors.append(dis(x_train[:m[j]-1], x_test, y_train[:m[j]-1], y_test, a))
                plt.legend()
                plt.ylabel("Error")
                plt.xlabel("M value")
                plt.title(sets[i])
                plt.plot(m, dis_errors, label = "MS Discriminative")
                plt.show()
	return 

def task3(feature_sets, label_sets):
	sets = ["A", "B", "crashes", "diabetes", "ionosphere"]
	kernel = 1.0 * RBF(1.0)
        for i in range(5):
		n = len(label_sets[i])
                m = np.linspace(10, .6 * n, num = 10, dtype = int)
                div = int(n * .4)
                x_train = feature_sets[i][div:]
                x_test = feature_sets[i][:div]
                y_train = label_sets[i][div:]
                y_test = label_sets[i][:div]
		gpc_errors = []
                for j in range(10):
			gpc = GPC(kernel=kernel, random_state=0)
			gpc.fit(x_train[:m[j]-1], np.ravel(y_train[:m[j]-1]))
			gpc_errors.append(1 - gpc.score(x_test, np.ravel(y_test)))
                	
		plt.legend()
                plt.ylabel("Error")
                plt.xlabel("M value")
                plt.title(sets[i])
                plt.plot(m, gpc_errors, label = "GPC")
                plt.show()



        return 

if __name__ == "__main__":
	feature_sets = []
	label_sets = []

	feature_sets.append(read_data("A.csv"))
	feature_sets.append(read_data("B.csv"))
	feature_sets.append(read_data("crashes.csv"))
	feature_sets.append(read_data("diabetes.csv"))
	feature_sets.append(read_data("ionosphere.csv"))

	label_sets.append(read_data("labels-A.csv"))
	label_sets.append(read_data("labels-B.csv"))
	label_sets.append(read_data("labels-crashes.csv"))
	label_sets.append(read_data("labels-diabetes.csv"))
	label_sets.append(read_data("labels-ionosphere.csv"))

	task1(feature_sets, label_sets)
        task2(feature_sets, label_sets)
        task3(feature_sets, label_sets)
