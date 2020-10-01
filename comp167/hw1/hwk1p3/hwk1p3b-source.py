import sys
from scipy.cluster.hierarchy import linkage
from scipy.spatial.distance import pdist

# Reads data into a 2d list
def read_data(filename):
        file = open(filename, 'r')
        data = []
        for line in file.readlines():
                data.append(line.strip('\n').split('\t'))
        file.close()
        return zip(*data[1:])

# Clusters using hierarchy
def cluster(data):
        dists = pdist(data[1:], metric='euclidean')
        cluster = linkage(dists, method='single')
        print('{}'.format(cluster))

def main(argv):
        data = read_data(argv[1])
        cluster(data)
if __name__ == '__main__':
        main(sys.argv)
