/****************************************************************************************
 *  Name:   Yegeta Zeleke
 *  File:   Graph.h
*****************************************************************************************/	


#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Graph.h"
#include "List.h"

// macros
#define MAX 1024

void preCheck(int argc, char const *argv[]){
	// see if program parameters are entered correctly
	
	FILE *in;                   
    FILE *out; 
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    
    in = fopen(argv[1], "r");	
	
    if ( in == NULL ) // can not open the file.
    {
        printf("usage: file read Error: Unable to read from file\n");
        exit(1);
    }

    // File writing error
    out = fopen(argv[2], "w");
    if (out == NULL )
    {
        printf("FindComponents Error: Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
	fclose(in);
	fclose(out);
	
}

int main(int argc, char const *argv[]){
	
	//check precondition
	preCheck(argc,argv);
	//input input output
    FILE *in;     																//read file pointer              
    FILE *out;																	//write to a file pointer
	
	in = fopen(argv[1], "r");													//open for read
    out = fopen(argv[2], "w"); 													//open for write
    	
    int u=1, v=1,i ;  																	 //number of vertex
		
																			     //string tokenizers
	char line[MAX];             
    char *token;
	
	Graph G; 	 																// create an object graph name G
	List S= newList();													// create an object List name VertexList
                     
    // Get the number of vertices in the Graph
    fgets(line, MAX, in);														//read the line of the file and put it on the string Line ; character pointer
    token = strtok(line, "\n");												    //tokenize 

	int toInt = atoi(token);													 //convert character to the equivalent integer
    G = newGraph(toInt);	    												//create a graph with number of vertex read from file which is toInt;
	
	
	int vertex = toInt;
   
   	int exit=0;
    // Frist part of the file : Get the edge lists and populate the Graph ADT
	//Assemble a graph object G using newGraph() and addArc(). 
    while (fgets(line, MAX, in) != NULL && !exit) // read each line from file
    {

			
        token = strtok(line, " ");	//tokenize each character ; remove the space and parse as an array
        u = atoi(token);
		
        token = strtok(NULL, " ");	//skip the spaces
        v = atoi(token);	// get the next number. change the char to int
		
		if( u == 0 && v==0){
			exit =1;
			break;
		}

        // If 0 0 is read first graph done reading
		if (!( u ==0 && v == 0 ))
			addArc(G, u, v); 
        
    }
	//put the DFS order of operation in ascending order.
	for(i=1; i<=vertex; ++i){
    	append(S,i);
    }

	
   
    // Print Graph adjaceny List to file
	//Print the adjacency list representation of G to the output file. 
    fprintf(out, "Adjacency List of G:\n");
    printGraph(out, G);
	//printf("\n");
	
	
	//Run DFS on G and G_transpose, processing the vertices in the second call by decreasing finish times from 
	//the first call. 

	Graph trans=transpose(G);
	DFS(G, S);								// run DFS on G
	DFS(trans, S);							//run DFS on G_transpose
	
	
	
	//Determine the strong components of G. 
	int components =0;
	for(moveTo(S,0);getIndex(S)!=-1;moveNext(S)){
		if(getParent(trans,getElement(S))==NIL)//start of a new connected components
			components++;
	}
	fprintf(out, "\nG contains %d strongly connected components: \n",components);		//print the number of comp in G
	

	
	//Print the strong components of G to the output file in topologically sorted order. 
	List singleComp = newList();
	int compNum=0;
	
	

	moveTo(S,vertex-1);
		
	
	for(int j=length(S)-1;j>=0;){
		prepend(singleComp,getElement(S));
		
		if(getParent(trans,getElement(S))==NIL){
			compNum++;
			fprintf(out, "Component %d: ", compNum);
			printList(out, singleComp);
			fprintf(out, "\n");
			freeList(&singleComp);		//reset the list to empty state
			singleComp = newList();

		}
		moveTo(S,--j);
	}

	
	//free temporary list allocation
	freeList(&singleComp);
	freeList(&S);
	
	//free temporary Graph allocation
	freeGraph(&G);
	freeGraph(&trans);
	
	//close all open files
	fclose(in);
	fclose(out);
}