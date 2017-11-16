/*
 *
 * List ADT that takes the form of a doubly linked-list for integers. Includes a
 *    "cursor" which can travel both ways through the list, and can be "undefined" 
 *    (That is to say not on the list). The list has a front node and a back node,
 *    the first and last nodes in the list, respectivly. The index of the list spans
 *    0 to n-1, with n being the length of the list.    
 *
 */

/*
 * List.c
 * The header for an integer List ADT
 *
 * Adapted from Queue.c supplied by Prof. Tantalo
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

/*
 * structs
 */

//creates type node
typedef struct NodeObj
{
   //Feilds
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

//creates pointer for node type
typedef NodeObj* Node;

//create List type
typedef struct ListObj
{
   //Feilds
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;

/*
 * constructors/deconstructers
 */

//node constructer
Node newNode(int data)
{
   Node n=malloc(sizeof(NodeObj));
   n->data=data;
   n->prev=NULL;
   n->next=NULL;
   return(n);
}

//Frees all the memory allocated to a given node
void freeNode(Node* node)
{
   if(node!=NULL && *node!=NULL)
   {
      free(*node);
      *node=NULL;
   }
}

//List constructer
List newList(void)
{
   List L;
   L=malloc(sizeof(ListObj));
   L->front=NULL;
   L->back=NULL;
   L->cursor=NULL;
   L->index=-1;
   L->length=0;
   return(L);
}

//Frees all he memory allocated in List
void freeList(List* List)
{
   if(List!=NULL && *List!=NULL)
   {
      while(!isEmpty(*List))
      {
         deleteFront(*List);
      }
      free(*List);
      *List=NULL;
   }
}

/*
 *
 * Access Functions
 *
 */

//returns element at front of List
//Pre-condition: length>0
int front(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List))
   {
      printf("ERROR: Access Function getFront(); list is empty");
      exit(1);
   }
   return(List->front->data);
}

//returns element at the back of List
//Pre-condition: length>0
int back(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling getBack() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List))
   {
      printf("ERROR: Access Function getBack); list is empty");
      exit(1);
   }
   return(List->back->data);
}

//returns the element pointed at by the cursor
//Pre-condition: length>0
int getElement(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling getBack() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List))
   {
      printf("ERROR: Access Function getBack(); list is empty");
      exit(1);
   }
   if(List->cursor != NULL)
	   return(List->cursor->data);
   return 99;
}

//returns List length
int length(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling getLength() on NULL List reference\n");
      exit(1);
   }
   return (List->length);
}

//returns the index of the list at which the cusor lies
//if the cursor is undefined return -1
int getIndex(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling getIndex() on NULL List reference\n");
      exit(1);
   }
   if(List->cursor==NULL)
      List->index=-1;
   return (List->index);
}

//returns 1 if List is empty(length=0), returns 0 otherwise
int isEmpty(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   if(List->length==0)
      return (1);
   return (0);
}

//checks that both given Lists have same integer sequence, cursor ignored
//returns 1 if true, 0 if false
int equals(List List1, List List2)
{
   if(List1==NULL||List2==NULL)
   {
      printf("List Error: called wquals() on NULL reference\n");
      exit(1);
   }
   if(List1->length!=List2->length)
      return (0);
   Node m=List2->front;
   for(Node n=List1->front;n!=NULL;n=n->next)
   {
      if(m==NULL)
         return (0);
      if(m->data!=n->data)
         return (0);
      m=m->next;
   }
//   if(m!=NULL)
//      return (0);
   return (1);
}

/*
 *
 * Manipulation Functions
 *
 */

//empties list of all elements
void clear(List List)
{
//printf("hi");
   if(List==NULL)
   {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while(!isEmpty(List))
   {
      deleteFront(List);
   }
   List->cursor=NULL;
   List->index=-1;
   List->length=0;
   //for(Node n=List->front)
   //freeList(&List);
}

//points cursor at the index specified
void moveTo(List List, int i)
{
   if(List==NULL)
   {
      printf("List Error: calling moveTo() on NULL List reference\n");
      exit(1);
   }
   if(List->length<i||i<0)
   {
      List->cursor=NULL;
      List->index=-1;
   }
   else
   {
      List->cursor=List->front;
      List->index=0;
      for(int c=0;c<i;c++)
      {
          List->cursor=List->cursor->next;
          List->index++;
      }
   }
}

//points cursor to element of list previous to the cursor's current position
void movePrev(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   moveTo(List,getIndex(List)-1);
}

//points cursor to element of list next to the cursor's current position
void moveNext(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   moveTo(List,getIndex(List)+1);
}

//insert data before the front of the list
void prepend(List List, int data)
{
   if(List==NULL)
   {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node n=newNode(data);
   if(List->front!=NULL)
   {
      List->front->prev=n;
      n->next=List->front;
      List->front=n;
      if(List->cursor!=NULL)
         List->index++;
      List->length++;
   }
   else
   {
      List->front=n;
      List->back=n;
      List->length=1;
   }
}

//insert data after the back of the list
void append(List List, int data)
{
   if(List==NULL)
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node n=newNode(data);
   if(List->back==NULL)
   {
      List->front=n;
      List->back=n;
      List->length=1;
   }
   else
   {
      n->prev=List->back;
      List->back->next=n;
      List->back=n;
      List->length++;
   }
}

//insert data before the cursor
//Pre-condition: length>0 && index>=0
void insertBefore(List List, int data)
{
   if(List==NULL)
   {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List)==1||List->index<0)
   {
      printf("ERROR: Access Function insertBefore; list is empty or cursor is undefined");
      exit(1);
   }
   if(List->cursor==List->front)
      prepend(List,data);
   else
   {
      Node n=newNode(data);
      n->next=List->cursor;
      n->prev=List->cursor->prev;
      List->cursor->prev->next=n;
      List->cursor->prev=n;
      List->length++;
   }
}

//insert data after the cursor
//Pre-condition: length>0 && index>=0
void insertAfter(List List, int data)
{
   if(List==NULL)
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List)==1||List->index<0)
   {
      printf("ERROR: Access Function insertAfter(); list is empty or cursor is undefined");
      exit(1);
   }
   if(List->cursor==List->back)
      append(List,data);
   else
   {
      Node n=newNode(data);
      n->prev=List->cursor;
      n->next=List->cursor->next;
      List->cursor->next->prev=n;
      List->cursor->next=n;
      List->length++;
   }
}

//delete element at the front of the list
//Pre-condition: length>0
void deleteFront(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List)==1)
   {
      printf("ERROR: Access Function deleteFront(); list is empty");
      exit(1);
   }
   Node n=List->front;
   if(length(List)>1)
   {
      List->front=List->front->next;
   }
   else
   {
      List->front=NULL;
      List->back=NULL;
   }
   List->length--;
   freeNode(&n);
}

//delete back element of the List
//Pre-condition: lengh>0
void deleteBack(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List)==1)
   {
      printf("ERROR: Access Function deleteBack(); list is empty");
      exit(1);
   }
   Node n=List->back;
   if(length(List)>1)
   {
      List->back=List->back->prev;
   }
   else
   {
      List->front=NULL;
      List->back=NULL;
   }
   List->length--;
   freeNode(&n);
}

//delete the element that is pointed at by the cursor
//Pre-condition: length>0 && index>=0
void delete(List List)
{
   if(List==NULL)
   {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(isEmpty(List)==1||List->index<0)
   {
      printf("ERROR: Access Function delete(); list is empty or cursor is undefined");
      exit(1);
   }
   Node n=List->cursor;
   if(length(List)>1)
   {
      List->cursor->prev->next=List->cursor->next;
      List->cursor->next->prev=List->cursor->prev;
   }
   else
   {
      List->front=NULL;
      List->back=NULL;
   }
   List->cursor=NULL;
   List->index=-1;
   List->length--;
   freeNode(&n);
}

/*
 *
 * Other Functions
 *
 */

//prints out list as a single string with one " " between each integer
void printList(FILE* output, List List)
{
   Node n=NULL;
   if(List==NULL)
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(n=List->front;n!=NULL;n=n->next)
   {
      fprintf(output,"%d%s",n->data," ");
   }
//   fprintf(output,"\n");
}

//creates new List with identical contents to given List, new cursor is undef
List copyList(List L)
{
   if(L==NULL)
   {
      printf("List Error: calling copy() on NULL List reference\n");
      exit(1);
   }
   List copy=newList();
   for(Node n=L->front;n!=NULL;n=n->next)
      append(copy,n->data);
   return copy;
}

