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

def create_anno_dict(filename):
	file = open(filename, 'r')
	annos = {}
	for line in file.readlines():
		entry = line.strip('\n').split('\t')
		annos[entry[0]] = entry[1:]
	file.close()
	
	return annos

def a(prot, G, annos):
	votes = cols.Counter()
	for n, w in G[prot].items():
		for l in annos[n]:
			votes[l] -= 1
	winner = (sorted([(y, x) for x, y in votes.items()]))
	if not winner:
		return '00'
	return winner[0][1]

def b(prot, G, annos):
        votes = cols.Counter()
        for n, w in G[prot].items():
                for l in annos[n]:
        		votes[l] -= float(w['weight'])
	winner = (sorted([(y, x) for x, y in votes.items()]))
        if not winner:
                return '00'
	return winner[0][1]

def c(G, annos):
	a_right = 0
	b_right = 0
	for node in G.nodes():
		if a(node, G, annos) in annos[node]:
			a_right += 1
		if b(node, G, annos) in annos[node]:
			b_right += 1
	print ('Majority Vote: {}%\nWeighted Majority Vote: {}%'.format(
	float(a_right)/5001.0, float(b_rightI/5001.0)))

# argv[1] is weighted edge list and argv[2] is MIPS annotation dictionary
def main(argv):
        G = create_graph(argv[1])
	annos = create_anno_dict(argv[2])
	c(G, annos)

if __name__ == '__main__':
        main(sys.argv)
