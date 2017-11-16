/*
 * header file for Graph.c
 * lets other files/programs access Graph.c's methods listed here
 */

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include "List.h"

#define INF -1
#define NIL -2
#define UNDEF -3

//create Graph type
typedef struct GraphObj* Graph;

/*
 * Constructors/Deconstructors
 */

//constructor
Graph newGraph(int n);

//deconstructor- frees graph
void freeGraph(Graph* pG);

/*
 *
 * Access Functions
 *
 */

//returns the number of verticies in G
int getOrder(Graph G);

//returns the number of edges in G
int getSize(Graph G);

//returns the source node of the graph used in BFS()
//returns NIL if BFS() hasn't been called
int getSource(Graph G);

//returns the parent node of u in a BFS-tree
int getParent(Graph G,int u);

//returns the distance from the source vertex to u
//uses BFS-tree to do this
//returns INF if BFS() hasn't been called 
//or if there is no path from source to u
int getDist(Graph G,int u);

//returns the discover time of a given vertex of graph G
//in a DFS-tree
//returns UNDEF if DFS hasn't been called
int getDiscover(Graph G, int u);

//returns the finish time of a given vertex of graph G
//in a DFS-tree
//returns UNDEF if DFS hasn't been called
int getFinish(Graph G,int u);

//appends the shortest path from source to u in G to List L
//appends NIL if no path exists
//pre-condition: getSource(G)!=NULL;//BFS must be called before getPath()
void getPath(List L,Graph G,int u);

/*
 *
 * Manipulation Functions
 *
 */

//deletes all edges in G
//making in a Null Graph
void makeNull(Graph G);

//creates an edge between u and v
//Pre-conditon: 1>=u>=getOrder(G) && 1>=v>=getOrder(G)
void addEdge(Graph G,int u,int v);

//creates a directed edge from u to v
//Pre-conditon: 1>=u>=getOrder(G) && 1>=v>=getOrder(G)
void addArc(Graph G,int u,int v);

//preforms a breadth first search on G with s as its source
//Pre-condition: 1>=s>=getOrder(G)
void BFS(Graph G,int s);

//preforms a depth first search on G with List S used to both tell the
//order by which the verticies of G should be searched
//and then storing the verticies in it according to their finish times
void DFS(Graph G,List S);

/*
 *
 * Other Functions
 *
 */

//returns a transpose of G
//a transpose of a directed graph reverses the direction
//of all edges in the graph
Graph transpose(Graph G);

//returns a copy of the Graph G
Graph copyGraph();

//prints Graph to file out, in adjacency list form
void printGraph(FILE* out, Graph G);

#endif
