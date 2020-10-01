import sys
import math

# Reads data into a 2d list
def read_data(filename):
        file = open(filename, 'r')
        data = []
        for line in file.readlines():
                data.append(line.strip('\n').split('\t'))
        file.close()
        return zip(*data)

# Given a training matrix and a test vector, labels using 1NN and 3NN
def label(train, test):
        results = []
        for i in range (1, len(train)):
                dist = distance(train[i][1:len(train)], test[1:len(test)])
                results.append((dist, train[i][0][:3]))
        results.sort()

        with open('hwk1p3a-1NNoutput.txt', 'a') as file:
                file.write('{}\t{}\n'.format(test[0], results[0][1]))

        aml = 0
        for i in range(0,3):
                if results[i][1] == 'AML':
                        aml += 1
        with open('hwk1p3a-3NNoutput.txt', 'a') as file:
                if aml >= 2:
                        file.write('{}\t{}\n'.format(test[0], 'AML'))
                else:
                        file.write('{}\t{}\n'.format(test[0], 'ALL'))

# Distance equation
def distance(v1, v2):
        dist = 0
        for i in range(len(v1)):
                dist = dist + ((float(v1[i]) - float(v2[i])) ** 2)
        return math.sqrt(dist)

def main(argv):
        data = read_data(argv[1])
        for i in range(0, 5):
                for j in range(0, 10):
                        vec = [e for k, e in enumerate(range(1, len(data)))
			if k not in range((10 * i),(10 * (i + 1)))]
			
                        train_data = [data[k] for k in vec]
			if (10 * i + j + 1) > 48:
                        	sys.exit()
			test_data = data[10 * i + j + 1]
                        label(train_data, test_data)

if __name__ == '__main__':
        main(sys.argv)
