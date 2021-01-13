//Yegeta Zeleke
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "List.h"

//macro definitions
#define False 0
#define True 1
//structs
//private NodeObj type



//Constructor-Destructors----------------------------------------
///newList()
// Returns reference to new empty List object. 
Node newNode(int data){
	 Node node;
	 node = malloc(sizeof(NodeObj));
	 node->data = data;
	 node->next = NULL;
	 node->prev =  NULL;
	 return (node);
}


List newList(void){
	 List tempList;
	 tempList = malloc(sizeof(ListObj));
	 tempList->front = tempList->cursor = tempList->back = NULL; 
	 tempList->length= 0;
	 tempList->index = -1;
	 return(tempList);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL){
	if(pL !=NULL && *pL!= NULL){
		
		while(length(*pL)!=0){
			deleteFront(*pL);
		}
		
		free(*pL);
		*pL = NULL;
		
	}
}

void freeNode(Node* pN){
	
	if(pN !=NULL && *pN!= NULL){
		
		free(*pN);
		*pN = NULL;
	}
}


// Access functions -----------------------------------------------------------
//Returns number of element in this list
int length(List L){
	if (L==NULL)
		return 0;
	return L->length;
}
//return the Index of the cursor element in this list, or returns -1 if the cursor element is undefined.
int getIndex(List L){
	if(L->cursor!=NULL)
		return L->index;
	else
		return -1;
}

// front()
// Returns the value at the front of L
// Pre: length()>0
int front(List L){
	if(L==NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(L->length<=0){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	return (L->front->data);
		
}

// back()
// Returns the value at the front of L
// Pre: length()>0
int back(List L){
	if(L==NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(L->length<=0){
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return (L->back->data);
}

//getElement()
//Return cursor element in this list.
//pre: length()>0, getIndex()>=0
int getElement(List L){
	if(L->length>0 && getIndex(L)>=0)
		return (L->cursor->data);
	else{
		printf("List Error: calling getElement() length(L)<=0 or getIndex()<0 \n");
		exit(1);
	}
}

//returns true if this List and L are the same integer
//sequance. The cursor is ignored in both lists.
int equals(List A, List B){
	int flag =1;
	Node N = NULL;
	Node M = NULL;
	if(A==NULL || B==NULL){
		printf("List Error: calling equals() on NULL List reference");
		exit(1);
	}
	N= A->front;
	M= B->front;
	if(length(A) != length(B)){return 0;}// they have different size	
	while(flag && N!=NULL){
		flag = (N->data == M->data);
		N = N->next;
		M= M->next;
	}
	freeNode(&N);
	freeNode(&M);
	return flag;
}

// Manipulation procedures ---------------------------------------------------- 

//re-set this List to the empty state.
void clear(List L){
	if(L!=NULL){
		Node temp;
		while(L->length>0){
			temp = L->front;
			L->front=(L->front)->next;
			freeNode(&temp);
			L->length= L->length-1;
		}
		L->length =0;
	
	}
}

// moveTo(i) : if 0=<i<=length()-1, moves the cursor to the element
// 		   at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i){
	if(i>=0 && i<= length(L)-1){
		L->cursor=L->front;
		L->index =0;
		while(getIndex(L) <i ){ // move to the left
			moveNext(L);
		}
		while(getIndex(L)>i ) //move to the right
			movePrev(L);
		
	}else{
		L->cursor=NULL;
		L->index =-1;
	}
}

// if 0<getIndex()<=length()-1 moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor become undefined.
//If getIndex()==-1, cursor remains undefined. this operatin is equivalent
//to moveTo(getIndex()-1).
void movePrev(List L){
		if(getIndex(L)>0 && getIndex(L)<=length(L)-1){
			L->cursor= L->cursor->prev;
			L->index--;
		}else{
			L->cursor=NULL;
			L->index =-1;
		}
}

// void moveNext() // If 0<=getIndex()<length()-1, moves the cursor one step toward the 
// back of the list. If getIndex()==length()-1, cursor becomes 
// undefined. If getIndex()==-1, cursor remains undefined. This 
// operation is equivalent to moveTo(getIndex()+1). 
void moveNext(List L){
	if(getIndex(L)>=0 && getIndex(L)<length(L)-1){
        L->cursor= L->cursor->next;
        L->index++;
	}
    else {
        L->cursor=NULL;
	    L->index=-1;
	}
}

// Inserts new element before front element in this List
void prepend(List L, int data){
	Node tempNode = newNode(data);
    
    if(length(L)==0){
		L->cursor=L->front=L->back=tempNode;
		L->index=0;
		L->length++;
		} // if the list is empty
	else{ // if list is non empty
		tempNode->prev=NULL;
    	tempNode->next=L->front;
	    L->front->prev=tempNode;
      	L->front = tempNode;
	  	L->length++;
	}


}

// Inserts new element after back element in this List. 
void append(List L, int data){
	Node tempNode = newNode(data);
    if(length(L)==0){
		L->cursor= tempNode;
		L->front=tempNode;
		L->back=tempNode;
		L->index=0;
		L->length= L->length+1;
		} // List is empty, create new node
    else{
       	tempNode->prev= L->back;
       	tempNode->next=NULL;
       	L->back->next=tempNode;
       	L->back = tempNode;
		L->length++;
    }
	

}	

// Inserts new element before cursor element in this 
// List. Pre: length()>0, getIndex()>=0 
void insertBefore(List L, int data){
	if(length(L)>0 && getIndex(L)>=0){
         Node insertNode = newNode(data);
         Node temp = L->cursor->prev;
         insertNode->prev = L->cursor->prev;
         insertNode->next = L->cursor;
         L->cursor->prev= insertNode;
         temp->next= insertNode;
         L->index++;
         L->length++;
	
		 

	
    }else{
        printf("List Error: InsertBefore() called for length<=0 or getIndex(L)<0");
		exit(1);
	}
}

// Inserts new element after cursor element in this 
// List. Pre: length()>0, getIndex()>=0 
void insertAfter(List L, int data){
	if(length(L)>0 && getIndex(L)>=0){
         Node insertNode = newNode(data);
         //Node temp = L->cursor->next;
         insertNode->prev = L->cursor;
         insertNode->next = L->cursor->next;
         L->cursor->next= insertNode;
         L->cursor->next->prev= insertNode;
         L->index++;
         L->length++;
		 
		
		 
		
    }else {
         printf("List Error: InsertAfter() called for length<=0 or getIndex()<0");
		 exit(1);
	}
}

// Deletes the front element in this List. Pre: length()>0 
void deleteFront(List L){
	    if (L == NULL)
    {
        printf("List Error: deleteFront() called on NULL List reference\n");
        exit(1);
    }

	if(length(L)>1){
		Node temp = L->front->next;
		freeNode(&(L->front));
		temp->prev= NULL;		
		L->front = temp;
		L->length--;
    }else if( length(L) == 1){
		 freeNode(&(L->front));
         L->front=L->back=L->cursor=NULL;
         L->length--;
    }else{
        printf("List Error: deleteFront() called for length<=0 ");
		exit(1);
	}
}

// Deletes the back element in this List. Pre: length()>0 
void deleteBack(List L){
    if(length(L)>1){
         Node temp = L->back->prev;
		// freeNode(&(L->back));
         temp->next= NULL;
         L->back = temp;
         L->length--;
    }else if( length(L) == 1){
		freeNode(&(L->back));
        L->front=L->back=L->cursor=NULL;
		L->index= -1;
        L->length--;
    }else{
         printf("List Error: deleteBack() called for length<=0 ");	
		 exit(1);
	}
}

 // Deletes cursor element in this List. Cursor is undefined after this 
 // operation. Pre: length()>0, getIndex()>=0 
void delete(List L){
	if(length(L)>0 && getIndex(L)>=0){
		Node left = L->cursor->prev;
		Node right = L->cursor->next;
		left->next = right;
		right->prev = left;
		freeNode(&(L->cursor));
		L->index=-1;
		L->length--;
		freeNode(&(right));
		freeNode(&(left));
	}else{
		printf("List Error: delete() called for length<=0 or on undefined cursor");
		exit(1);
	}
}
 
// Other operations ----------------------------------------------------------- 
void printList(FILE* out, List L){
	Node N= NULL;
	if( L==NULL ){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
		}
	for(N = L->front; N != NULL; N = N->next){
		fprintf(out,"%d ", N->data);
		}
	freeNode(&N);
} 

// Returns a new list representing the same integer sequence as this 
// list. The cursor in the new list is undefined, regardless of the 
// state of the cursor in this List. This List is unchanged. 
List copyList(List L){
	List copyList = newList();
    Node N= L->front;
    while(N!=NULL){
        append(copyList,N->data);
        N=N->next;
    }
	if(L->front!=NULL){ //dammy assingment to clear the Node memory
		N = L->front;
		freeNode(&N);
	}
    return copyList;
}
Node copyNode(Node N){
	Node temp = newNode(N->data);
	temp->next = N->next;
	temp->prev= N->prev;
 
    return temp;
}

