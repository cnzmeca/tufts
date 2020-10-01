import sys
import numpy as np
import random
import csv
import math
import matplotlib.pyplot as plt

def read_data(D):
	d = []
	l = []
	for i in range(D):
		with open(str(i+1)) as f:
			for word in f.readline().split():
				d.append(i)
				l.append(word)
	v = np.array(list(set(l)))
	w = [dict([(y,x) for x,y in enumerate(v)])[z] for z in l]
	return d, w, v

def get_documents(D):
	docs = []
	for i in range(D):
                with open(str(i+1)) as f:
			docs.append(f.readline().split())
	return docs

def read_csv():
	index = []
	with open("index.csv") as f:
		read = csv.reader(f, delimiter = ",")
		for row in read:
			index.append(int(row[1]))
	return index

def make_cd(d, z, D, K):
	cd = np.zeros((D, K))
	for i in range(len(d)):
		cd[d[i], z[i]] += 1
	return cd

def make_ct(z, w, K, V):
	ct = np.zeros((K, V))
	for i in range(len(w)):
		ct[z[i], w[i]] += 1
	return ct

def sigmoid(x):
        return np.divide(1, (1 + np.exp(-x)))

def blr(y_train, x_train, a):
        w = np.zeros(len(x_train[0]))
        for k in range(100):
		s = sigmoid(np.dot(x_train, w))
		r = np.diag(s * (1 - s))
                sn = np.linalg.inv(np.dot(np.transpose(x_train), np.dot(r, x_train)) + ((a + .000000001) * np.identity(len(w))))
                w = w - np.dot(sn, (np.dot(np.transpose(x_train), s - np.transpose(y_train)) + (a * w)))

	return w

def model_selection(y_train, x_train):
	a = 1
	for l in range(10):
		w = blr(y_train, x_train, a)
		s = sigmoid(np.dot(x_train, w))
                r = np.diag(np.transpose(s) * (1 - s))
		lam = np.real(np.linalg.eigvals(np.dot(np.transpose(x_train), np.dot(r, x_train))))
		gam = np.sum(np.divide(lam, lam + a))
		a = gam/np.linalg.norm(w, ord = 2)
	return a

def blr_error(y_train, x_train, y_test, x_test):
	x_train = np.append(x_train, np.transpose(np.array([np.ones(len(x_train))])), axis=1)
        x_test = np.append(x_test, np.transpose(np.array([np.ones(len(x_test))])), axis=1)
        a = model_selection(y_train, x_train)
        w = blr(y_train, x_train, a)
        y_pred = []
        for x in x_test:
        	prob = np.dot(np.transpose(w), x)
                if prob >= .5:
                	y_pred.append(1)
                else:
                        y_pred.append(0)
        error = np.mean(np.absolute(np.array(y_pred) - y_test))
	return error

def build_bags(y_train, x_train):
	words0 = []
	words1 = []
	for i in range(len(y_train)):
		if y_train[i] == 0:
			for x in x_train[i]:
				words0.append(x)
		else:
			for x in x_train[i]:
                                words1.append(x)
	bag0 = {}
	bag1 = {}
	for w in words0:
		if w not in bag0:
			bag0[w] = 0
		bag0[w] += 1.0/len(words0)
	for w in words1:
                if w not in bag1:
                        bag1[w] = 0
                bag1[w] += 1.0/len(words1)

	return bag0, bag1

def bow_error(y_train, x_train, y_test, x_test):
	bag0, bag1 = build_bags(y_train, x_train)
	y_pred = []
	for x in x_test:
		probs0 = []
		probs1 = []
		for word in x:
			try:
				probs0.append(bag0[word])
			except KeyError:
				pass
			try:
				probs1.append(bag1[word])
			except KeyError:
				pass
		perp0 = np.exp(-np.log(probs0).sum()/float(len(x)))
		perp1 = np.exp(-np.log(probs1).sum()/float(len(x)))
		if perp0 > perp1:
			y_pred.append(0)
		else:
			y_pred.append(1)
	error = np.mean(np.absolute(np.array(y_pred) - y_test))
	return error

def task1():
	a = .1
	b = .01
	K = 20
	D = 200
	d, w, v = read_data(D)	
	V = len(set(w))
	z = np.random.randint(0, K, len(w))
	cd = make_cd(d, z, D, K)
	ct = make_ct(z, w, K, V)
	p = np.zeros(K)
	pi = range(len(w))
	random.shuffle(pi)
	for i in range(100):
		for n in range(len(w)):
			word = w[pi[n]]
			topic = z[pi[n]]
			doc = d[pi[n]]
			cd[doc, topic] -= 1
			ct[topic, word] -= 1
			for k in range(K):
				p[k] = ((ct[k, word] + b) * (cd[doc, k] + a) / (b * V + np.sum(ct[k])) / (a * K + np.sum(cd[doc])))
			p = p/np.sum(p)
			topic = np.random.choice(k + 1, p=p)
			z[pi[n]] = topic
			cd[doc, topic] += 1
			ct[topic, word] += 1
	with open("topicwords.csv", "w") as f:
		for k in range(K):
			freq = v[np.argsort(ct[k])[:-6:-1]]
			f.writelines(",".join(freq) + "\n")
	return cd

def task2(cd):
	y = np.array(read_csv())
	D = len(cd)
	docs = np.array(get_documents(D))
	blr_means = []
	blr_stds = []
	bow_means = []
	bow_stds = []
	for n in range(1, 121):
		print(n)
		blr_errors = []
		bow_errors = []
		for i in range(30):
			i_train = np.array(random.sample(range(D), int(D * .6)))
			i_test = np.setdiff1d(range(D), i_train)
			e1 = blr_error(y[i_train][:n], cd[i_train][:n], y[i_test], cd[i_test])
			e2 = bow_error(y[i_train][:n], docs[i_train][:n], y[i_test], docs[i_test])
			blr_errors.append(e1)
			bow_errors.append(e2)
		blr_means.append(np.mean(blr_errors))
		blr_stds.append(np.std(blr_errors))
		bow_means.append(np.mean(bow_errors))
		bow_stds.append(np.std(bow_errors))
	plt.ylabel("Error")
        plt.xlabel("Training set size")
        plt.title("LDA")
        plt.errorbar(range(1, 121), blr_means, yerr = blr_stds)
        plt.show()

	plt.ylabel("Error")
        plt.xlabel("Training set size")
        plt.title("Bag of Words")
        plt.errorbar(range(1, 121), bow_means, yerr = bow_stds)
        plt.show()
	return

cd = task1()
task2(cd)

