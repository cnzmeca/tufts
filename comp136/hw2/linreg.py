import csv
import numpy as np
import matplotlib.pyplot as plt

def read_data(filename):
	data = []
	with open(filename) as csvfile:
		reader = csv.reader(csvfile, quoting=csv.QUOTE_NONNUMERIC)
		for row in reader:
			data.append(row)
	return np.array(data)

def mse(l, train, test, train_regs, test_regs):
	tp = np.matrix.transpose(train)
	i = np.identity(len(train[0]))
	train_t = np.matrix.transpose(train_regs)[0]
	test_t = np.matrix.transpose(test_regs)[0]
	w = np.dot(np.matmul(np.linalg.inv((l * i) + np.matmul(tp, train)), tp), train_t)
	return np.mean(np.square(np.matmul(test, w) - test_t))	

def task1(train_sets, train_regs, test_sets, test_regs):
	sets = ["100-10", "100-100", "1000-100", "forest_fire", "real_estate", "50(1000)-100", "100(1000)-100", "150(1000)-100"]
	print("Lambda\tMSE")
	for i in range(len(train_sets)):
		train_mse = []
		test_mse = []
		for l in range(0, 151):
			train_mse.append(mse(l, train_sets[i], train_sets[i], train_regs[i], train_regs[i]))
			test_mse.append(mse(l, train_sets[i], test_sets[i], train_regs[i], test_regs[i]))
		plt.plot(range(0, 151), train_mse, label = "Train")
		plt.plot(range(0, 151), test_mse, label = "Test")
		plt.legend()
		plt.ylabel("MSE")
		plt.xlabel("Lambda")
		plt.title(sets[i])
		plt.show()

		print(str(np.argmin(test_mse)) + "\t" + str(min(test_mse)))

def task2(train_sets, train_regs, test_sets, test_regs):
	print("Lambda\tMSE")
	for i in range(len(train_sets)):
		mse_folds = []
		for j in range (0, 10):
			test_nums = range(0, len(train_sets[i]))[j::10]
			train_nums = np.setdiff1d(range(0, len(train_sets[i])), test_nums)
			train = np.take(train_sets[i], train_nums, axis = 0)
			test = np.take(train_sets[i], test_nums, axis = 0)
			train_reg = np.take(train_regs[i], train_nums)
			test_reg = np.take(train_regs[i], test_nums)
			
			mses = []
			for l in range(0, 151):
				mses.append(mse(l, train, test, train_reg, test_reg))
			mse_folds.append(mses)
		opt_l = np.argmin(np.sum(mse_folds, axis = 0))
		test_mse = mse(l, train_sets[i], test_sets[i], train_regs[i], test_regs[i])
		print(str(opt_l) + "\t" + str(test_mse))
	return

def task3(train_sets, train_regs, test_sets, test_regs):
	print("Alpha\tBeta\tMSE")
	for i in range(0, 8):
		train = train_sets[i]
		tp = np.matrix.transpose(train)
		r = train_regs[i]
		l = np.linalg.eigvals(np.matmul(tp, train))
		m = 0	
		a = 1
		b = 1
		diff = 1
		while (diff > .0000000001):
			s = np.linalg.inv(a * np.identity(len(train[0])) + b * np.matmul(tp, train))
			m = np.matrix.transpose(b * np.dot(np.matmul(s, tp), r))[0]
			c = np.sum(np.divide(b * l, (a + b * l)))
			newa = c / np.matmul(np.matrix.transpose(m), m)
			newb = 1.0/((1.0/(len(train) - c)) * np.sum(np.square(r - np.dot(m, tp))))
			diff = min(abs(a - newa), abs(b - newb))
			a = newa
			b = newb
		test_mse = np.mean(np.square(np.matmul(test_sets[i], m) - test_regs[i]))
		print(str(np.real(a)) + "\t" + str(np.real(b)) + "\t" + str(np.real(test_mse)))
	return

	

if __name__ == "__main__":
	train_sets = []
	train_sets.append(read_data("train-100-10.csv"))
	train_sets.append(read_data("train-100-100.csv"))	
	train_sets.append(read_data("train-1000-100.csv"))
	train_sets.append(read_data("train-forestfire.csv"))
	train_sets.append(read_data("train-realestate.csv"))
	train_sets.append(train_sets[2][:50])
	train_sets.append(train_sets[2][:100])
	train_sets.append(train_sets[2][:150])

	train_regs = []
	train_regs.append(read_data("trainR-100-10.csv"))
        train_regs.append(read_data("trainR-100-100.csv"))
        train_regs.append(read_data("trainR-1000-100.csv"))
        train_regs.append(read_data("trainR-forestfire.csv"))
        train_regs.append(read_data("trainR-realestate.csv"))
        train_regs.append(train_regs[2][:50])
        train_regs.append(train_regs[2][:100])
        train_regs.append(train_regs[2][:150])
	
	test_sets = []
	test_sets.append(read_data("test-100-10.csv"))
        test_sets.append(read_data("test-100-100.csv"))
        test_sets.append(read_data("test-1000-100.csv"))
        test_sets.append(read_data("test-forestfire.csv"))
        test_sets.append(read_data("test-realestate.csv"))
	test_sets.append(test_sets[2])
	test_sets.append(test_sets[2])
	test_sets.append(test_sets[2])

	test_regs = []
	test_regs.append(read_data("testR-100-10.csv"))
        test_regs.append(read_data("testR-100-100.csv"))
        test_regs.append(read_data("testR-1000-100.csv"))
        test_regs.append(read_data("testR-forestfire.csv"))
        test_regs.append(read_data("testR-realestate.csv"))
        test_regs.append(test_regs[2])
        test_regs.append(test_regs[2])
        test_regs.append(test_regs[2])

	task1(train_sets, train_regs, test_sets, test_regs)
	task2(train_sets, train_regs, test_sets, test_regs)
	task3(train_sets, train_regs, test_sets, test_regs)
