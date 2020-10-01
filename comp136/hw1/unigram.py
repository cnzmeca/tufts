import sys
import numpy as np
import matplotlib.pyplot as plt
import math

def read_data(filename):
	ret = []
	with open(filename, "r") as f:
		for l in f.readlines():
			ret += l.split()
	return ret
def vectorize(data, vocab):
	ret = {}
	for w in vocab:
		ret[w] = 0
	for d in data:
		try:
			ret[d] += 1
		except KeyError:
			ret[d] = 1
	return np.array([x[1] for x in ret.items()])

def lookup(vec, vocab):
	ret = {}
	for i in range(len(vocab)):
		ret[vocab[i]] = vec[i]
	return ret

def ML(vec, N):
	return vec / float(N)

def MAP(vec, N, a):
	return (vec + a - 1) / float(N + a.sum() + len(vec))

def Bayes(vec, N, a):
	return (vec + a) / float(N + a.sum())

def perplexity(data, table, N):
	prob = np.zeros(len(data))
	for i in range(len(data)):
		prob[i] = table[data[i]]
	return np.exp(-np.log(prob).sum()/float(N))

def series_mult(x, y):
	ret = 1
	for x in range(x, y):
		ret *= x
	return ret

def log_evidence(vec, N, a):
	ret = 0
	for i in range(len(vec)):
		ret += math.log(series_mult(a, a + vec[i]))
	ret -= math.log(series_mult(a * len(vec), N))
	return ret

def task1(train_data, test_data):
	vocab = sorted(list(set(train_data + test_data)))
	a = np.full(len(vocab), 2)
        size = [5000, 10000, 40000, 160000, 640000]
       	N = len(test_data)
 
	train1 = [] 
	train2 = []
	train3 = []
	test1 = []
	test2 = []
	test3 = []

	for s in size:
		section = train_data[0:s]
                train = vectorize(section, vocab)
			
                method1 = lookup(ML(train, s), vocab)
                method2 = lookup(MAP(train, s, a), vocab)
                method3 = lookup(Bayes(train, s, a), vocab)

		train1.append(perplexity(section, method1, s))
		train2.append(perplexity(section, method2, s))
		train3.append(perplexity(section, method3, s))
	
		test1.append(perplexity(test_data, method1, N))
		test2.append(perplexity(test_data, method2, N))
		test3.append(perplexity(test_data, method3, N))	

	print("Train ML\t")
	print(train1)
	print("Train MAP\t")
	print(train2)
	print("Train Bayes\t")
	print(train3)
	print("Test ML\t")
	print(test1)
	print("Test MAP\t")
	print(test2)
	print("Test Bayes\t")
	print(test3)
	print("\n")

        plt.plot(size, train1, label = "Train ML")
        plt.plot(size, train2, label = "Train MAP")
        plt.plot(size, train3, label = "Train Bayes")
	plt.plot(size, test1, label = "Test ML")
        plt.plot(size, test2, label = "Test MAP")
        plt.plot(size, test3, label = "Test Bayes")
        plt.legend()
        plt.ylabel("Perplexity")
        plt.xlabel("Training Size")
        plt.title("Task 1")
        plt.show()

def task2(train_data, test_data):
	vocab = sorted(list(set(train_data + test_data)))
	alphas = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	s = 5000
	section = train_data[0:s]
        train = vectorize(section, vocab)

	e = []
	p = []

	for a in alphas:
		e.append(log_evidence(train, s, a))
		pred = lookup(Bayes(train, s, np.full(len(train), a)), vocab)
		p.append(perplexity(section, pred, s))

	print("Log evidence\t")
	print(e)
	print("Perplexity\t")
	print(p)
	print("\n")

	plt.plot(alphas, e)
	plt.ylabel("Log evidence")
	plt.xlabel("Alpha")
	plt.title("Task 2 (Evidence)")
	plt.show()

	plt.plot(alphas, p)
        plt.ylabel("Perplexity")
        plt.xlabel("Alpha")
        plt.title("Task 2 (Perplexity)")
	plt.show()

def task3(pg1188, pg345, pg84):
	vocab = sorted(list(set(pg1188 + pg345 + pg84)))
	train = vectorize(pg345, vocab)
	a = np.full(len(vocab), 2)
	s = len(pg345)
	pred = lookup(Bayes(train, s, np.full(len(train), a)), vocab)

	p1 = perplexity(pg1188, pred, len(pg1188))
	p2 = perplexity(pg84, pred, len(pg84))

	print("Page 1188\t")
	print(p1)
	print("Page 84\t")
	print(p2)

if __name__ == "__main__":
	train_data = read_data("training_data.txt")
	test_data = read_data("test_data.txt")
	pg1188 = read_data("pg1188.txt.clean")
	pg345 = read_data("pg345.txt.clean")
	pg84 = read_data("pg84.txt.clean")

	task1(train_data, test_data)
	task2(train_data, test_data)
	task3(pg1188, pg345, pg84)
