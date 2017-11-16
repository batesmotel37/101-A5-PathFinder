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
 * List.h
 * The header for an integer List ADT
 *
 * Adapted from Queue.c supplied by Prof. Tantalo
 */

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

//create List type
typedef struct ListObj* List;

//constructor
List newList(void);

//Frees all he memory allocated in List
void freeList(List* List);

/*
 *
 * Access Functions
 *
 */

//returns element at front of List
//Pre-condition: length>0
int getFont(List List);

//returns element at the back of List
//Pre-condition: length>0
int getBack(List List);

//returns the element pointed at by the cursor
//Pre-condition: length>0
int getElement(List List);

//returns List length
int getLength(List List);

//returns the index of the list at which the cusor lies
//if the cursor is undefined return -1
int getIndex(List List);

//returns 1 if List is empty(length=1), returns 0 otherwise
int isEmpty(List List);

//checks that both given Lists have same integer sequence, cursor ignored
//returns 1 if true, 0 if false
int equals(List List1, List List2);

/*
 *
 * Manipulation Functions
 *
 */

//empties list of all elements
void clear(List List);

//points cursor at the index specified
void moveTo(List List, int i);

//points cursor to element of list previous to the cursor's current position
void movePrev(List List);

//points cursor to element of list next to the cursor's current position
void moveNext(List List);

//insert data before the front of the list
void prepend(List List, int data);

//insert data after the back of the list
void append(List List, int data);

//insert data before the cursor
//Pre-condition: length>0 && index>=0
void insertBefore(List List, int data);

//insert data after the cursor
//Pre-condition: length>0 && index>=0
void insertAfter(List List, int data);

//delete element at the front of the list
//Pre-condition: length>0
void deleteFront(List List);

//delete back element of the List
//Pre-condition: lengh>0
void deleteBack(List List);

//delete the element that is pointed at by the cursor
//Pre-condition: length>0 && index>=0
void delete(List List);

/*
 *
 * Other Functions
 *
 */

//prints out list as a single string with one " " between each integer
void printList(FILE* output, List List);

//creates new List with identical contents to given List, new cursor is undef
List copy(List L);

#endif
