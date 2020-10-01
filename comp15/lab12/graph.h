/*
 *  Basic Graph class
 * 
 *  Vertices are represented as integers
 *  The nodes contain no values, but in a real graph, you would 
 *  store information in the nodes.
 *  Having a fixed size of 10 nodes is, of course, very artificial.
 */
#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
        static const int NODE_COUNT = 10;

	Graph();
	Graph(bool adjM[NODE_COUNT][NODE_COUNT]);
        ~Graph();

	bool createEdge(int v1, int v2);
	bool isAdjacent(int v1, int v2);

	void BFS();
	void DFS();

private:
	bool   markVertex(int v);
	bool   isMarked(int v);
	void   unmarkAll();

	void   DFS(int vertex);
        void   allocateArrays();

	bool  *markedVertices;
	bool **adjacencyMatrix;
};

#endif
