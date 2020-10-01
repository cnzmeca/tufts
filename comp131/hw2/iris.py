import numpy as np
import sys

def sigmoid(x):
        return np.divide(1, (1 + np.exp(-x)))

def sigmoid_deriv(x):
	return np.multiply(x, (1 - x))

# Reads and formats data
def read_data():
	f = open(sys.argv[1])
	raw_data = f.readlines()
	f.close()
	
	features = []
	labels = []
	for d in raw_data:
		features.append([float(x) for x in d.split(",")[:-1]])
		label = d.split(",")[-1].strip()
		if (label == "Iris-setosa"):
			labels.append(0)
		elif (label == "Iris-versicolor"):
			labels.append(1)
		else:
			labels.append(2)
	return np.array(features), np.array(labels)

# Params
input_nodes = 4
hidden_nodes = 2
output_nodes = 3
iterations = 1000

# Normalize data
x,y = read_data()
x = np.divide(x - np.mean(x, 0), np.std(x))

# Train/test division
x_train = x[::2]
y_train = y[::2]
x_val = x[1::2]
y_val = y[1::2]
size = len(y_train)

# Initialize layers with uniform random weights between -1 and 1
first_layer = 2 * np.random.rand(input_nodes, hidden_nodes) - 1
second_layer = 2 * np.random.rand(hidden_nodes, output_nodes) - 1

# Train layers using feed forward and back propogation
for i in range(iterations):	
	hidden_values = sigmoid(np.dot(x_train, first_layer))
	output_values = sigmoid(np.dot(hidden_values, second_layer))
	
	output_error = np.zeros([size, output_nodes])
	for j in range(size):
		if (0 == y_train[j]):
			output_error[j, 0] = 1 - output_values[j, 0]
			output_error[j, 1] = 0 - output_values[j, 1]
			output_error[j, 2] = 0 - output_values[j, 2]
		elif (1 == y_train[j]):
			output_error[j, 0] = 0 - output_values[j, 0]
                        output_error[j, 1] = 1 - output_values[j, 1]
                        output_error[j, 2] = 0 - output_values[j, 2]
		else:
			output_error[j, 0] = 0 - output_values[j, 0]
                        output_error[j, 1] = 0 - output_values[j, 1]
                        output_error[j, 2] = 1 - output_values[j, 2]
	output_delta = np.multiply(sigmoid_deriv(output_values), output_error)
	
	hidden_error = np.dot(output_delta, second_layer.T)
	hidden_delta = np.multiply(sigmoid_deriv(hidden_values), hidden_error)
	first_layer += np.dot(x_train.T, hidden_delta)
	second_layer += np.dot(hidden_values.T, output_delta)

# Predict validation data using trained layers
pred = np.argmax(sigmoid(np.dot(sigmoid(np.dot(x_val, first_layer)), second_layer)), 1)
correct = 0
for i in range(size):
	if (y_val[i] == pred[i]):
		correct += 1
print("Validation accuracy: " + str(correct/float(size)))
print("First layer: ")
print(first_layer)
print("Second layer: ")
print(second_layer)
print("\n")


# Gardener input for testing
while (True):
	test1 = float(raw_input("Enter sepal length in cm: "))
	test2 = float(raw_input("Enter sepal width in cm: "))
	test3 = float(raw_input("Enter sepal length in cm: "))
	test4 = float(raw_input("Enter petal width in cm: "))
	test = np.array([test1, test2, test3, test4])
	print("\n")
	print(test)
	guess = np.argmax(sigmoid(np.dot(sigmoid(np.dot(test, first_layer)), second_layer)))

	if (guess == 0):
		print("Iris-setosa")
	elif (guess == 1):
		print("Iris-versicolor")
	else:
		print("Iris-virginica")

	print("\n")
