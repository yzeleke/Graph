/****************************************************************************************
 *  Name:   Yegeta Zeleke
 *  File:   Graph.h
*****************************************************************************************/
#ifndef _GRAPH_H_INCLUDE
#define _GRAPH_H_INCLUDE

//Include the header file from list.h
#include "List.h"

// Define constant value for infinity and NIL-2
#define UNDEF -1 //negative time for time not defined
#define NIL 0		// undefined perrent
//define color macros
#define WHITE 'w'
#define GREY 'g'
#define BLACK 'b' 

// Graph
typedef struct GraphObj *Graph; 

	/*newGraph()
	pre: none
	post: constructor for the Graph type */
Graph newGraph(int n); 

/*  freeGraph()
	pre: none
	post: destructor for graph object realloc memory */
void freeGraph(Graph *pG);

	/* getOrder 
	pre: none
	post: this function returns the number of vertices on a*/
int getOrder(Graph G); 

	/*getSize(Graph G)
	pre: none
	post: returns the number of edges of the graph  */
int getSize(Graph G); 


	/* 	getParent
	pre: 1 <= u <= getOrder(G)
	returns the parent of vertex u in the Breadth-First tree created by BFS() */
int getParent(Graph G, int u);

	/* getDiscover()
	pre: 1 <= u <= getOrder(G)
	return: the approximate discovery time of a given vertex
	*/
int getDiscover(Graph G, int u);

	/* getFinish()
	pre: 1 <= u <= getOrder(G)
	return: the approximate finish time of a given vertex
	*/
int getFinish(Graph G, int u);


	// makeNull()
	/* pre: none 
	// post: deletes all edges of G, reset G*/
void makeNull(Graph G);
	
	// addArc()
	// pre: 1 <= u <= getOrder(G) && 1 <= v <= getOrder(G)
	// post:  inserts a new directed edge from u to v, i.e. v is added to the adjacency
void addArc(Graph G, int u, int v);

	// addEdge()
	// pre: 1 <= u <= getOrder(G) && 1 <= v <= getOrder(G)
	// post: inserts a new edge that join u to v
void addEdge(Graph G, int u, int v);



	// DFS ()
	// pre: none 
	// post: runs the DFS  on the Graph G, change the colors,parent and dicovery time and finish time fields
void DFS(Graph G, List S);

	//DFS Visit
//static void visit(Graph G, List S, int u, int *time);

/***********other Functions**************/
Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out , Graph G);

	// printGraph()
	// pre: none 
	// post: prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif
