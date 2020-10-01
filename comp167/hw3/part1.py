import sys
import collections as cols
import matplotlib.pyplot as plt
import networkx as nx
import random as rand

def create_graph(filename):
        file = open(filename, 'r')
        edges = []
        for line in file.readlines():
                edges.append(line.strip('\n').split('\t'))
        file.close()

        G = nx.Graph()
        G.add_weighted_edges_from(edges)
        return G

def a(G):
	degrees = sorted(cols.Counter([d for n, d in G.degree()]).items())
	x, y = zip(*degrees)
	plt.plot(x, y)	
	plt.xscale('symlog', linthreshx=0.01)
	plt.yscale('symlog', linthreshy=0.01)
	plt.xlabel('Degree')
	plt.ylabel('# of Occurences')
	plt.show()

def b(G):
	coeffs = nx.clustering(G)
	with open('coeffs.txt', 'w') as f:
		for x, y in coeffs.items():
			f.write('{}\t{}\n'.format(x, y))

def c(G):
	tris = nx.triangles(G)
	total = 0
	for x,y in tris.items():
		total += y
	print('#Triangles: {}'.format(total/3))
	
def d_and_e(G):
	sample = G.copy()
	sample.remove_nodes_from(rand.sample(sample.nodes(), 4001))
	sps = dict(nx.shortest_path_length(sample))
	
	lengths = cols.Counter()
	for n1, dic in sps.items():
		for n2, d in dic.items():
			lengths[d] += .5

	x, y = zip(*(lengths.items()))
	plt.plot(x, y)
	plt.xlabel('Shortest Path Length')
	plt.ylabel('# of Occurences')
        plt.show()

# argv[1] is weighted edge list	
def main(argv):
	G = create_graph(argv[1])
	a(G)
	b(G)
	c(G)
	d_and_e(G)

if __name__ == '__main__':
        main(sys.argv)
