// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

template<class Node>
struct node_wrap:public iterator<input_iterator_tag, Node>{
    Node* ptr;
    node_wrap(Node*p = nullptr): ptr(p){}

    char operator*(){return ptr->data;}
    Node* operator->(){return ptr;}

    node_wrap& operator++(){ptr = ptr -> nextPtr; return *this;}

    bool operator== (const node_wrap& i)const{return ptr == i.ptr;}
    bool operator!= (const node_wrap& i)const{return ptr != i.ptr;} 
};

template <class Node>
bool operator==(const Node& node, char ch){
    return node.data == ch;
}

template <class Node>
bool operator!=(const Node& node, char ch){
    return !(node.data == ch);
}
// self-referential structure                       
struct listNode {                                      
   char data; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
   listNode(): nextPtr(NULL){}
   friend bool operator==(const listNode& lhs, const listNode& rhs){
       return lhs.data == rhs.data;
   }
}; // end structure listNode                        



typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert( ListNodePtr *sPtr, char value );
char Delete( ListNodePtr *sPtr, char value );
int isEmpty( ListNodePtr sPtr );
void printList( ListNodePtr currentPtr );
void instructions( void );

int main( void )
{ 
    ListNodePtr startPtr = NULL; // initially there are no nodes
    char item[6] = {"abcde"};
    for(int i = 0; i < 5 ;i++){
        insert(&startPtr, item[i]);
    }
    char ch;
    while(cin >> ch){
        node_wrap<ListNode> tmp = find(node_wrap<ListNode>(startPtr), node_wrap<ListNode>(), ch);
        if(tmp->nextPtr != NULL)cout << tmp->data << '\n';
    }
} // end main

// display program instructions to user
void instructions( void )
{ 
    puts( "Enter your choice:\n"
        "   1 to insert an element into the list.\n"
        "   2 to delete an element from the list.\n"
        "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert( ListNodePtr *sPtr, char value )
{ 
    ListNodePtr newPtr; // pointer to new node
    ListNodePtr previousPtr; // pointer to previous node in list
    ListNodePtr currentPtr; // pointer to current node in list

    newPtr = (ListNodePtr) malloc( sizeof( ListNode ) ); // create node

    if ( newPtr != NULL ) { // is space available
        newPtr->data = value; // place value in node
        newPtr->nextPtr = NULL; // node does not link to another node

        previousPtr = NULL;
        currentPtr = *sPtr;

        // loop to find the correct location in the list       
        while ( currentPtr != NULL && value > currentPtr->data ) {
            previousPtr = currentPtr; // walk to ...               
            currentPtr = currentPtr->nextPtr; // ... next node 
        } // end while                                         

        // insert new node at beginning of list
        if ( previousPtr == NULL ) { 
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } // end if
        else { // insert new node between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } // end else
    } // end if
    else {
        printf( "%c not inserted. No memory available.\n", value );
    } // end else
} // end function insert

// delete a list element
char Delete( ListNodePtr *sPtr, char value )
{ 
    ListNodePtr previousPtr; // pointer to previous node in list
    ListNodePtr currentPtr; // pointer to current node in list
    ListNodePtr tempPtr; // temporary node pointer

    // delete first node
    if ( value == ( *sPtr )->data ) { 
        tempPtr = *sPtr; // hold onto node being removed
        *sPtr = ( *sPtr )->nextPtr; // de-thread the node
        free( tempPtr ); // free the de-threaded node
        return value;
    } // end if
    else { 
        previousPtr = *sPtr;
        currentPtr = ( *sPtr )->nextPtr;

        // loop to find the correct location in the list
        while ( currentPtr != NULL && currentPtr->data != value ) { 
            previousPtr = currentPtr; // walk to ...  
            currentPtr = currentPtr->nextPtr; // ... next node  
        } // end while

        // delete node at currentPtr
        if ( currentPtr != NULL ) { 
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free( tempPtr );
            return value;
        } // end if
    } // end else

    return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( ListNodePtr sPtr )
{ 
    return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( ListNodePtr currentPtr )
{ 
    // if list is empty
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty.\n" );
    } // end if
    else { 
        puts( "The list is:" );

        // while not the end of the list
        while ( currentPtr != NULL ) { 
            printf( "%c --> ", currentPtr->data );
            currentPtr = currentPtr->nextPtr;   
        } // end while

        puts( "NULL\n" );
    } // end else
} // end function printList

