import sys
from scipy.cluster.vq import kmeans
from scipy.spatial.distance import euclidean

# Reads data into a 2d list
def read_data(filename):
        file = open(filename, 'r')
        data = []
        for line in file.readlines():
                data.append(line.strip('\n').split('\t'))
        file.close()

        return zip(*data[1:])[1:]

# Clusters using kmeans
def cluster(data):
	centroids = kmeans(data, data[11:36:24])
	
	for i in range(0, len(data)):
		dist1 = euclidean(centroids[0][0], data[i])
		dist2 = euclidean(centroids[0][1], data[i])
		if dist1 > dist2:
			print('{}'.format(i))
		
def main(argv):
        data = read_data(argv[1])
	data = [[float(y) for y in x] for x in data]	
        cluster(data)
if __name__ == '__main__':
        main(sys.argv)
