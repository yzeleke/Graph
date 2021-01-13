/****************************************************************************************
 *  Name:   Yegeta Zeleke
 *  File:   GraphTest.c
*****************************************************************************************/

//-----------------------------------------------------------------------------
//
// GraphTest.c
// 
// This is a supper fancy test client that calculates the Radius and Diameter of 
// the graph. This program call each program and test the graph file
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  int i, n=10;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,10);
   addArc(G, 1,3);
   addArc(G, 2,3);
   addArc(G, 3,5);
   addArc(G, 5,7);
   addArc(G, 2,4);
   addArc(G, 1,8);
   addArc(G, 7,3);
   addArc(G, 9,9);
   addArc(G, 4,6);
   addArc(G, 4,4);
   addArc(G, 8,5);
   addArc(G, 8,1);
   
     DFS(G, S);
   fprintf(stdout, "\nDFS\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
  

   // Print adjacency list representation of G
   printf("printGraph(G)\n");
   printGraph(stdout, G);	//test printGraph
   
	//test order
   printf("The order of Graph G is :%d \n",getOrder(G));
   
   //test size()
   printf("The size of the Graph G is : %d\n",getSize(G));
   
   //test getperent() on root
   printf("The perent of the root of the graph is: %d\n", getParent(G,1));
   
   //test getdiscover() on root
   printf("The discovery time of the root is: %d\n",getDiscover(G,1));
   
   //test getFinish() on root
    printf("The finish time of the root is : %d\n",getFinish(G,1));
	
	//test transpose() and printGraph on G
	Graph trans =transpose(G);
	printf("transpose(G)\n");
	printGraph(stdout,trans);
	
	//test copyGraph()
	Graph cp = copyGraph(G);
	printf("cp = copyGraph(G) test\n");
	printGraph(stdout,cp);
	

   // Free objects 
   freeGraph(&T);
   freeGraph(&C);
   freeGraph(&trans);
   freeGraph(&cp);
   freeGraph(&G);
   
   freeList(&S);
 

   return(0);
}