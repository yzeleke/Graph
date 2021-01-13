//---------------------------------------------------------------
//List.h
//Header file for List ADT
//---------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

//struct definition----------------------------------------------
typedef struct NodeObj{
   	int data;
	struct NodeObj* next;
 	struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//Private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;
//Explore type---------------------------------------------------
typedef struct ListObj* List;
typedef struct NodeObj* Node;

//Constructor-Destructors----------------------------------------

// Node()
// return new empty node
Node newNode(int data);

///newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);

// freeNode()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeNode(Node* pL);


// Access functions -----------------------------------------------------------
//Returns number of element in this list
int length(List L);

//return the Index of the cursor element in this list, or returns -1 if the cursor element is undefined.
int getIndex(List L);

// front()
// Returns the value at the front of L
// Pre: length()>0
int front(List L);

// back()
// Returns the value at the front of L
// Pre: length()>0
int back(List L);

//getElement()
//Return cursor element in this list.
//pre: length()>0, getIndex()>=0
int getElement(List L);

//returns true if this List and L are the same integer
//sequance. The cursor is ignored in both lists.
int equals(List A, List B); 
 
// Manipulation procedures ---------------------------------------------------- 

//re-set this List to the empty state.
void clear(List L); 

// moveTo(i) : if 0<i<=length()-1, moves the cursor to the element
// 		   at index i, otherwise the cursor becomes undefined.
void moveTo(List L, int i); 

// if 0<getIndex()<=length()-1 moves the cursor one step toward the
// front of the list. If getIndex()==0, cursor become undefined.
//If getIndex()==-1, cursor remains undefined. this operatin is equivalent
//to moveTo(getIndex()-1).
void movePrev(List L); 

// void moveNext() // If 0<=getIndex()<length()-1, moves the cursor one step toward the 
// back of the list. If getIndex()==length()-1, cursor becomes 
// undefined. If getIndex()==-1, cursor remains undefined. This 
// operation is equivalent to moveTo(getIndex()+1). 
void moveNext(List L); 

// Inserts new element before front element in this List
void prepend(List L, int data); 

// Inserts new element after back element in this List. 
void append(List L, int data); 

// Inserts new element before cursor element in this 
// List. Pre: length()>0, getIndex()>=0 
void insertBefore(List L, int data); 

// Inserts new element after cursor element in this 
// List. Pre: length()>0, getIndex()>=0 
void insertAfter(List L, int data); 

// Deletes the front element in this List. Pre: length()>0 
void deleteFront(List L); 

// Deletes the back element in this List. Pre: length()>0 
void deleteBack(List L); 

 // Deletes cursor element in this List. Cursor is undefined after this 
 // operation. Pre: length()>0, getIndex()>=0 
void delete(List L); 
 
// Other operations ----------------------------------------------------------- 
void printList(FILE* out, List L); 

// Returns a new list representing the same integer sequence as this 
// list. The cursor in the new list is undefined, regardless of the 
// state of the cursor in this List. This List is unchanged. 
List copyList(List L); 
#endif