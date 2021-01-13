/****************************************************************************************
 *  Name:   Yegeta Zeleke
 *  File:   Graph.h
*****************************************************************************************/
//Include library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//Include the header file from list.h
#include "List.h"
#include "Graph.h"



// Graph
/** Graph Object **/
typedef struct GraphObj
{
    int size;               // Total number of edges on the graph
    int order;              // total number of vertices on the graph
    char *color;            // color to keep track of the visited vertices
    int  *parent;           // Parent of each vertices
    List *adj;         		// Adjacency Lists
    int  *finish;       	// finish time
	int  *disc;              // discovery time
} GraphObj;


	/*newGraph()
	pre: none
	post: constructor for the Graph type , Graph with n vertice */
Graph newGraph(int n){
	Graph temp = malloc(sizeof(GraphObj));
	assert(temp!=NULL);
	if(n<1){
		printf("Graph.c Error newGraph called on vertices size less than 1");
		exit(1);
	}
	temp->size = 0;
	temp->order=n;
	
	temp->color = calloc((n+1), sizeof(char));   //each memory allocation of size char // used for char array
	
    assert(temp->color != NULL);
    temp->adj = calloc((n+1), sizeof(List));	//each adjacent of size vertices
	
    assert(temp->adj != NULL); //stop if adj is equal to NULL, null pointer referenced
    temp->finish = calloc((n+1), sizeof(int)); // array size defined by vertice size
	
	assert(temp->adj != NULL); //stop if adj is equal to NULL, null pointer referenced
    temp->disc = calloc((n+1), sizeof(int)); // array size defined by vertice size

    
    temp->parent = calloc((n+1), sizeof(int));
	
    assert(temp->parent != NULL);
	
	 //initialze the Graph fields to nill, color to white and distance to infinity
	   for (int i = 1; i <=n; ++i)
		{
			temp->adj[i] = newList();				//create a new list for every vertice
			temp->disc[i] = UNDEF	;				//set the discovery time to undefined
			temp->finish[i] = UNDEF	;				//set the finish time to undefined
			temp->color[i]    = WHITE;              // Not visted yet
			temp->parent[i]   = NIL;              // undefined Parent
		}

    return temp;
	
}

/*  freeGraph()
	pre: none
	post: destructor for graph object realloc memory */
void freeGraph(Graph *pG){
	if ( pG != NULL && *pG != NULL )
    {
        // start by freeing each list(vertice)
		int i;
        for (i = 1; i <=getOrder(*pG); i++)
        {
            freeList(&(*pG)->adj[i]);	//free all List of adj
        }
		free((*pG)->finish);
		free((*pG)->disc);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->adj); 			//free the whole array memory reserve
        free(*pG); 					// and finally free the graph itself
        *pG = NULL;
    }
}

	/* getOrder 
	pre: none
	post: this function returns the number of vertices on a*/
int getOrder(Graph G){
	if (G == NULL) //throw an error message if G is Null pointer
    {
        printf("Graph: getOrder() called on a NULL Graph reference\n");
        exit(1);
    }
   // otherwise return the order
    return G->order;
}

	/*getSize(Graph G)
	pre: none
	post: returns the number of edges of the graph  */
int getSize(Graph G){
	if (G == NULL) //throw an error message if G is Null pointer
    {
        printf("Graph: getSize() called on a NULL Graph reference\n");
        exit(1);
    }
   // otherwise return the order
    return G->size;
}


	/* 	getParent
	pre: 1 <= u <= getOrder(G)
	returns the parent of vertex u in the Breadth-First tree created by BFS() */
int getParent(Graph G, int u){
	if (G == NULL) //throw an error message if G is Null pointer
    {
        printf("Graph: getParent() called on a NULL Graph reference\n");
        exit(1);
    }
	else if(1 >u || u> getOrder(G)){ 			// check if precondition is satisfied
		if ( u < 1 )
		{
			printf("Graph: getParent() called on vertex less than 1\n");
			exit(1);
		}
		else 
		{
			printf( "Graph: getParent() called with a vertex greater than getOrder(G)\n");
			exit(1);
		}
	}else   // otherwise all pre conditions satisfied   
		return G->parent[u];
}

	/* getDiscover()
	pre: 1 <= u <= getOrder(G)
	return: the approximate discovery time of a given vertex
	*/
int getDiscover(Graph G, int u){
		if (G == NULL) //throw an error message if G is Null pointer
    {
        printf("Graph: getDiscover() called on a NULL Graph reference\n");
        exit(1);
    }
	else if(1 >u || u> getOrder(G)){ 			// check if precondition is satisfied
		if ( u < 1 )
		{
			printf("Graph: getDiscover() called on vertex less than 1\n");
			exit(1);
		}
		else 
		{
			printf( "Graph: getDiscover() called with a vertex greater than getOrder(G)\n");
			exit(1);
		}
	}else   // otherwise all pre conditions satisfied   
		return G->disc[u];
}

	/* getFinish()
	pre: 1 <= u <= getOrder(G)
	return: the approximate finish time of a given vertex
	*/
int getFinish(Graph G, int u){
	if (G == NULL) //throw an error message if G is Null pointer
    {
        printf("Graph: getFinish() called on a NULL Graph reference\n");
        exit(1);
    }
	else if(1 >u || u> getOrder(G)){ 			// check if precondition is satisfied
		if ( u < 1 )
		{
			printf("Graph: getFinish() called on vertex less than 1\n");
			exit(1);
		}
		else 
		{
			printf( "Graph: getFinish() called with a vertex greater than getOrder(G)\n");
			exit(1);
		}
	}else   // otherwise all pre conditions satisfied   
		return G->finish[u];
}




	// makeNull()
	/* pre: none 
	// post: deletes all edges of G, reset G*/
void makeNull(Graph G){
   if (G == NULL)
    {
        printf( "Graph.c: makeNull() A Null pointer dereferenced. makeNull(G) was called on a Null pointer\n");
        exit(1);   
	}
    // G is not null, so now initialize to NULL
    for (int i = 1; i <= getOrder(G); i++)
    {
		G->color[i]    = WHITE;
        G->parent[i]   = NIL;
        clear(G->adj[i]); // clear the array list[i]
		freeList(&(G->adj[i]));
        G->disc[i] = UNDEF; // set discovery time back to undefined 
		G->finish[i] =UNDEF;
    }
	G->order  = 0; //set vertix size to zero
    G->size   = 0;  // no vertex hence no edge    
	
}


	// addEdge()
	// pre: 1 <= u <= getOrder(G) && 1 <= v <= getOrder(G)
	// post: inserts a new edge that join u to v and v to you
void addEdge(Graph G, int u, int v){
	if (G == NULL)
		{
        printf("Graph: addEdge() called on a NULL Graph reference\n");
        exit(1);
	}else if(1 >u || u> getOrder(G)){ 
		if ( u < 1 ){		
			printf("Graph: addEdge() called on vertex u less than 1\n");
			exit(1);
		}else {
			printf( "Graph: addEdge() called with a vertex u greater than getOrder(G)\n");
			exit(1);
		}
    }else if(1 >v || v> getOrder(G)){ 
		if ( v< 1 ){		
			printf( "Graph: addEdge() called on vertex  v less than 1\n");
			exit(1);
		}else {
			printf("Graph: addEdge() called with a vertex  v greater than getOrder(G)\n");
			exit(1);
		}
    }else{ // all conditions meet
		addArc(G, v, u);
		addArc(G, u, v);
		
	}
    
}

	// addArc()
	// pre: 1 <= u <= getOrder(G) && 1 <= v <= getOrder(G)
	// post:  inserts a new directed edge from u to v, i.e. v is added to the adjacency
void addArc(Graph G, int u, int v){
	
	//check for preconditions
	if (G == NULL)
		{
			printf( "Graph: PostARC() called on a NULL Graph reference\n");
			exit(1);
	}else if(1 >u || u> getOrder(G)){ 
		if ( u < 1 ){		
			printf("Graph: PostARC() called on vertex u less than 1\n");
			exit(1);
		}else {
			printf("Graph: PostARC() called with a vertex u greater than getOrder(G)\n");
			exit(1);
		}
    }else if(1 >v || v> getOrder(G)){ 
		if ( v< 1 ){		
			printf("Graph: PostARC() called on vertex  v less than 1\n");
			exit(1);
		}else {
			printf("Graph: PostARC() called with a vertex  v greater than getOrder(G)\n");
			exit(1);
		}
    }else{ 			// All pre-conditions are satisfied
	

			//run insertion sort
		if(length(G->adj[u])==0){
			append(G->adj[u],v);
			++G->size;
		}
		else{
			if(v>back(G->adj[u])){  //check if v is greater than element at the back of the list
					append(G->adj[u],v);
					++G->size;
			}else if (v< front(G->adj[u])){ // compare v with the front
					prepend(G->adj[u],v);
					++G->size;
			}else{ // V lies somewhere in between the list therefore traverse through the list
				moveTo(G->adj[u],0);	//move the cursor to index 0
				while (getIndex(G->adj[u])<length(G->adj[u])-1 && v>getElement(G->adj[u])){
					moveNext(G->adj[u]);
				} 
				if(v!=getElement(G->adj[u])){
					insertBefore(G->adj[u],v);
					++G->size;
				}
			}
		}
	}
}
//
//
//
//
//// visit
void visit(Graph G, List S, int u, int *time){
	if (G==NULL){
		printf("Visit called on Graph  G with Null pointer, Null pointer dereferenced");
		exit(1);
	}
	if(S==NULL){
		printf("Visit called on List S with Null pointer, Null pointer dereferenced");
		exit(1);
	}
	
	//precondition satisfied
	int temp; 									// temp vertex
	
	G->disc[u]=((*time)+1);						// set the discovery time
	G->color[u]=GREY;							// now the vertex is discovered set the color on grey
	*time = *time +1;
	
	
	
	for(moveTo(G->adj[u], 0); getIndex(G->adj[u])!=-1; moveNext(G->adj[u])){
		temp=getElement(G->adj[u]);					 // get the vertex in adjecency list of U
		if(G->color[temp]==WHITE){ 					// if the vertex hasnt been visited before
			G->parent[temp]=u;						// set the perrent  and visit temp
			visit(G, S, temp, &(*time));
		}else continue;								// other wise skip to the next iteration
	}
	
	
	G->color[u]=BLACK;	// recursion bottoms out... the vertex doesnt have parrent, set to finish
	G->finish[u]=(++(*time));
	insertAfter(S,u); 							// append the finished vertex to the stack
	
}

	// DFS ()
	// pre: length = order
	// post: runs the DFS  on the Graph G, change the colors,parent and dicovery time and finish time fields
//DFS(G) Psuedo Code
	//1. for each vertex u in v[G]
	//2. 	do color[u]<- white
	//3. 		pi[u]<-white
	//4. time<-0
	//5. for each vertex u in v[G]
	//6. 	do if color[u]= white
	//7.		then DFS-visit(u)

void DFS(Graph G, List S){
	//check for preconditions
	if (G == NULL)
	{
		printf( "Graph: DFS() called on Graph G = Null, a NULL Graph reference\n");
		exit(1);
	}
	if (G == NULL){
		printf( "Graph: DFS() called List S = NULL, a NULL Graph reference\n");
		exit(1);
	}
	if(length(S)!=G->order){ 
		printf( "Graph: DFS() called on length(S)!=G->order\n");
		exit(1);
	}
	

	
	int vertex,i;
	for(i=1; i<=getOrder(G); ++i){
		G->color[i]=WHITE;
		G->parent[i]=NIL;
	}
	
	//devide the List in two two, the first part of the list contains the order the second part the stack(finish time)
	
	if(length(S)!=0){
		int time =0,i =1;
		moveTo(S,(length(S)-1));	//move cursor to the End of the List
		while(i<length(S)+1){
			vertex=front(S); //get the front of the queue
			if(G->color[vertex]==WHITE){
				visit(G, S, vertex, &time);	//serve the front of the Queue
				
			}
			//other wise it must have been discovered already so dequeue
			deleteFront(S); // remove the front of the Queue
			i++;
		}
	}

}



// transpose Graph G
Graph transpose(Graph G){
	if (G==NULL){
		printf("Graph: Visit called on Graph  G with Null pointer, Null pointer dereferenced");
		exit(1);
	}
	int j;
	
	Graph trans=newGraph(getOrder(G));
	
	for(int i=1; i<=getOrder(G); i++){
		if(length(G->adj[i])>0){
			for(moveTo(G->adj[i],0),j=1; j<=length(G->adj[i]); ++j,moveNext(G->adj[i])){
				addArc(trans,getElement(G->adj[i]), i); //
				//moveNext(G->adj[i]);
			}
		}
		//otherwise skip to the next iteration
	}
	return trans;
}

//copy Graph 
Graph copyGraph(Graph G){
	if (G==NULL){
		printf("Graph: copyGraph() called on Graph  G with Null pointer, Null pointer dereferenced");
		exit(1);
	}
	
	Graph newCopy=newGraph(G->order);
	
	for(int i=1; i<=G->order; ++i){
		int j=1;
		for(moveTo(G->adj[i],0); j<=length(G->adj[i]);moveNext(G->adj[i]),j++){
			addArc(newCopy, i, getElement(G->adj[i]));
		}
	}
	return newCopy;
}

	// printGraph()
	// pre: none 
	// post: prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
	if (G == NULL)	// check if G is not null
		{
			printf("Error on Graph: printGraph() called on a NULL variable. Null pointer reference\n");
			exit(1);
		}
   // precondition satisfied
    for (int j = 1; j <= getOrder(G); j++) // start from the first vertix and go all the way to the last
    {
        fprintf(out, "%d: ", j);
        printList(out, G->adj[j]);
        fprintf(out, "\n");
    }
}


