import numpy as np
from sklearn.linear_model import LogisticRegression as logr
from sklearn.model_selection import cross_val_score as cvs
from sklearn.model_selection import cross_val_predict as cvp
from sklearn.metrics import mean_squared_error as mse

TRAIN = "../../data/trainset.csv"
GENDER = "../../data/gender.csv"
YEAR = "../../data/release-year.csv"

ROW = 943
COL = 1681

def read_csv(filename):
	data = []
	with open(filename, "r") as file:
		for line in file.readlines():
			try:
				data.append(map(int, line.strip().split(",")))
			except:
				pass
	return data

def make_matrix(l):
	matrix = np.full((ROW, COL), 0)
	for d in l:
		matrix[d[0]][d[1]] = d[2]
	return matrix

if __name__ == "__main__":
	train = read_csv(TRAIN)
	gender = read_csv(GENDER)
	year = read_csv(YEAR)

	X1 = make_matrix(train)
	X2 = X1.T
	Y1 = np.asarray(gender).T[0]
	Y2 = np.asarray(year).T[0]
	
	clf1 = logr()
	scores = cvs(clf1, X1, Y1, cv=10)
	print("Min CV error: {}".format(1 - max(scores)))

	clf2 = logr(solver="saga", multi_class="multinomial")
	pred = cvp(clf2, X2, Y2, cv=10)
	mse1 = mse(Y2, pred)
	mse2 = mse(Y2, np.full_like(Y2, np.mean(Y2)))
	print("Regression MSE: {}".format(mse1))
	print("Naive MSE: {}".format(mse2))
