using namespace std;

template<typename T>
struct ListNode {
   T data; // each listNode contains a character
   ListNode<T>* nextPtr; // pointer to next node
   ListNode(T _data = 0, ListNode<T>* p = nullptr): data(_data), nextPtr(p){}
   T operator*() const {return data;}
   friend bool operator==(const ListNode& lhs, const ListNode& rhs){
       return lhs.data == rhs.data;
   }
}; // end structure listNode

template<typename T>
using ListNodePtr = ListNode<T>*;

template<typename T, typename Reference, typename Pointer>
struct node_wrap_base:public iterator<input_iterator_tag, T, ptrdiff_t, Pointer, Reference>{
};

template <typename T>
struct node_wrap:public node_wrap_base<T, T&, T*>{
    ListNode<T>* ptr;
    node_wrap(ListNode<T>* p = nullptr):ptr(p){}

    void incr(){ptr = ptr->nextPtr;}

    T& operator*(){return ptr->data;}
    T* operator->(){return ptr;}

    node_wrap& operator++(){incr(); return *this;}
    node_wrap operator++(int){node_wrap tmp = *this; incr(); return *this;}

    bool operator== (const node_wrap& i)const{return ptr == i.ptr;}
    bool operator!= (const node_wrap& i)const{return ptr != i.ptr;}
};

template <typename T>
struct LinkedList{
    node_wrap<T>* start;
    LinkedList(node_wrap<T>* p = nullptr): start(p){}
    node_wrap<T> begin(){return *start;}
    node_wrap<T> end(){return node_wrap<T>(nullptr);}
};

template <typename T>
bool operator==(const T& node, T val){
    return node.data == val;
}

template <typename T>
bool operator!=(const T& node, T val){
    return !(node.data == val);
}

// insert a new value into the list in sorted order
template <typename T>
void Insert( LinkedList<T> StartPtr, T value )
{
    ListNodePtr<T> *sPtr = &(StartPtr.start->ptr);
    ListNodePtr<T> newPtr; // pointer to new node
    ListNodePtr<T> previousPtr; // pointer to previous node in list
    ListNodePtr<T> currentPtr; // pointer to current node in list

    newPtr = (ListNodePtr<T>) malloc( sizeof( ListNode<T> ) );

    if ( newPtr != NULL ) { // is space available
        newPtr->data = value; // place value in node
        newPtr->nextPtr = NULL; // node does not link to another node

        previousPtr = NULL;
        currentPtr = *sPtr;

        // loop to find the correct location in the list
        while ( currentPtr != NULL && value > currentPtr->data ) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }

        // insert new node at beginning of list
        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else { // insert new node between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf( "%c not inserted. No memory available.\n", value );
    }
}

// delete a list element
template<typename T>
T Delete( LinkedList<T> StartPtr, T value )
{
    ListNodePtr<T> *sPtr = &(StartPtr.start->ptr);
    ListNodePtr<T> previousPtr; // pointer to previous node in list
    ListNodePtr<T> currentPtr; // pointer to current node in list
    ListNodePtr<T> tempPtr; // temporary node pointer

    // delete first node
    if ( value == ( *sPtr )->data ) {
        tempPtr = *sPtr; // hold onto node being removed
        *sPtr = ( *sPtr )->nextPtr; // de-thread the node
        free( tempPtr ); // free the de-threaded node
        return value;
    }
    else {
        previousPtr = *sPtr;
        currentPtr = ( *sPtr )->nextPtr;

        // loop to find the correct location in the list
        while ( currentPtr != NULL && currentPtr->data != value ) {
            previousPtr = currentPtr; // walk to ...
            currentPtr = currentPtr->nextPtr; // ... next node
        }

        // delete node at currentPtr
        if ( currentPtr != NULL ) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free( tempPtr );
            return value;
        }
    }

    return '\0';
}

// return 1 if the list is empty, 0 otherwise
template <typename T>
int isEmpty( ListNodePtr<T> sPtr )
{
    return sPtr == NULL;
}

template<typename T>
void printList( LinkedList<T> StartPtr )
{
    ListNodePtr<T> ptr = StartPtr.start->ptr;
    // if list is empty
    if ( isEmpty( ptr ) ) {
        puts( "List is empty.\n" );
    }
    else {
        puts( "The list is:" );

        // while not the end of the list
        while ( ptr != nullptr ) {
            cout << ptr->data << " --> ";
            ptr = ptr->nextPtr;
        }

        puts( "NULL\n" );
    }
}

template <typename T>
void findList(LinkedList<T> StartPtr, const T& val){
    auto it = find(StartPtr.begin(), StartPtr.end(), val);
    if(it != StartPtr.end()){
        cout << val << ": Found\n\n";
    }else{
        cout << val << ": Not found\n\n";
    }

}

template <typename T>
void test_linklist(T head, initializer_list<T> l, T val){
    ListNode<T> x(head);
    node_wrap<T> s(&x);
    LinkedList<T> List(&s);
    for(auto it: l){
        Insert(List, it);
    }
    printList(List);
    auto it =find(List.begin(), List.end(), val);
    if(it == List.end()){
        Insert(List, val);
    }else{
        Delete(List, val);
    } 
    printList(List);
}