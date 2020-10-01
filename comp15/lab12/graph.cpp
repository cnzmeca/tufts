#include <iostream>
#include <queue>

#include "graph.h"

using namespace std;
/* 
 * Create two dynamic arrays, the adjacency
 * matrix to store the graph and the marked
 * set --- initialized to false for all to start.
 * The adjacent matrix is all false:  it is an
 * empty graph.
 */
Graph::Graph()
{
        allocateArrays();

        //
        // Initialize for empty graph
        //
        for (int row = 0; row < NODE_COUNT; ++row) {
                for (int col = 0; col < NODE_COUNT; ++col) {
                        adjacencyMatrix[row][col] = false;
                }
                markedVertices[row] = false;
        }
}

/* 
 * This constructor accepts an adjacency matrix to be used
 * to initialize the graph.
 */
Graph::Graph(bool adjM[NODE_COUNT][NODE_COUNT])
{
        allocateArrays();

        //
        // Initialize from provided initial adjacency matrix
        //
        for (int row = 0; row < NODE_COUNT; ++row) {
                for (int col = 0; col < NODE_COUNT; ++col) {
                        adjacencyMatrix[row][col] = adjM[row][col];
                }
                markedVertices[row] = false;
        }
}

/* 
 * Allocates the adjacency matrix (a 2-D array) and 
 * the array for the marked set.
 *
 * Note:  The storage is left uninitialized.
 */
void Graph::allocateArrays()
{
        adjacencyMatrix = new bool * [NODE_COUNT];
        markedVertices  = new bool   [NODE_COUNT];

        for (int i = 0; i < NODE_COUNT; ++i)
                adjacencyMatrix[i] = new bool [NODE_COUNT];
}

/*
 * TODO:  Fill this in AFTER you get the searches done, if you have time
 */
Graph::~Graph()
{
       	for (int i = 0; i < NODE_COUNT; ++i)
                delete [] adjacencyMatrix[i];
	delete [] adjacencyMatrix;
	delete [] markedVertices;
}

/*
 * If v1 and v2 are in bounds, add the edge and return true.
 * If edge has been previously added, it's added again.
 * if out of bounds, return false.
 */
bool Graph::createEdge(int v1, int v2)
{
        if (v1 >=0 and v1 <= NODE_COUNT and v2 >= 0 and v2 <= NODE_COUNT) {
                adjacencyMatrix[v1][v2] = true;
                adjacencyMatrix[v2][v1] = true;
                return true;
        } else {
                return false;
        }
}

/*
 * Return true if there is an edge between
 * v1 and v2
 */
bool Graph::isAdjacent(int v1, int v2)
{
        return adjacencyMatrix[v1][v2];
}

/*
 * marks a vertex true.
 */
bool Graph::markVertex(int v)
{
        if (v >= 0 and v <= NODE_COUNT) {
                markedVertices[v] = true;
                return true;
        }
        return false;
}



bool Graph::isMarked(int v)
{
        return markedVertices[v];
}

/*
 * Unmark all vertices.
 */
void Graph::unmarkAll()
{
        for (int i = 0; i < NODE_COUNT; ++i)
                markedVertices[i] = false;
}


/*
 * BREADTH FIRST SEARCH
 */
void Graph::BFS()
{
        unmarkAll();
	
	int start_node = 0;
	
	queue<int> q;
	
	markVertex(start_node);
	q.push(start_node);	
	
	while (!q.empty())
	{
		cout << q.front();
		for (int i = 0; i < NODE_COUNT; i++)
		{
			if (!isMarked(i) && isAdjacent(q.front(),i))
			{
				markVertex(i);
				q.push(i);
			}
		}
		q.pop();
	}
	
}


/*
 * DEPTH FIRST SEARCH
 */
void Graph::DFS()
{
	unmarkAll();

	int start_node = 0;

	DFS(start_node);
}

void Graph::DFS(int vertex)
{
	markVertex(vertex);
	cout << vertex;
		
	for (int i = 0; i < NODE_COUNT; i++)
	{
		if (!isMarked(i) && isAdjacent(vertex,i))
		{
			DFS(i);
		}
	}
}
