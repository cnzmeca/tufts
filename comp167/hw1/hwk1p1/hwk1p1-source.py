import sys
import math

# Reads data into a 2d list
def read_data(filename):
        file = open(filename, 'r')
	data = []
	for line in file.readlines():
		data.append(line.strip('\r\n').split('\t'))
	file.close()
	return zip(*data)

# Given a training matrix and a test vector, labels using 1NN and 3NN
def label(train, test):
	results = []
	for i in range (1, len(train)):
		dist = distance(train[i][1:len(train)-1], test[1:len(test)-1])
		results.append((dist, train[i][-1]))
	results.sort()
	print('{}\n\n\n\n'.format(results))

	with open('hwk1p1-1NNoutput.txt', 'a') as file:
		file.write('{}\t{}\n'.format(test[0], results[0][1]))
	
	smokers = 0
	for i in range(0,3):
		if results[i][1] == 'CurrentSmoker':
			smokers += 1	
	with open('hwk1p1-3NNoutput.txt', 'a') as file:
		if smokers >= 2:
			file.write('{}\t{}\n'.format(test[0], 'CurrentSmoker'))
		else:
			file.write('{}\t{}\n'.format(test[0], 'NeverSmoker'))
	
# Distance equation
def distance(v1, v2):
	dist = 0
	for i in range(len(v1)):
		dist = dist + ((float(v1[i]) - float(v2[i])) ** 2)
	return math.sqrt(dist)
		
def main(argv):
	test_data = read_data(argv[1])
	train_data = read_data(argv[2])

	for i in range(1, len(test_data)):
		label(train_data, test_data[i])

if __name__ == '__main__':
        main(sys.argv)
