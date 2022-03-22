//program header
//project4:
//tingjie yu
//date: 11/14/2021
//purpose of code: implementation for FIFOQueueClass

//library includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

template < class NODETYPE >
//Default Constructor. Will properly initialize a queue to
//be an empty queue, to which values can be added.
FIFOQueueClass< NODETYPE >::FIFOQueueClass() {

  head = NULL;
  tail = NULL;
 
}


template < class NODETYPE >
//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
FIFOQueueClass< NODETYPE >::~FIFOQueueClass() {

  clear();

}


template < class NODETYPE >
//Inserts the value provided(newItem) into the queue.
void FIFOQueueClass< NODETYPE >::enqueue(const NODETYPE &newItem) {

  //if insert into empty fifo
  if(tail == NULL) {
  
    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
    NULL, newItem, NULL);

    head = insertedNode;
    tail = insertedNode;

  }
  else {
  //insert after tail

    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
    tail, newItem, NULL);

    tail = insertedNode;
    insertedNode -> setBeforeAndAfterPointers();

  }
}



template < class NODETYPE >
//Attempts to take the next item out of the queue. If the
//queue is empty, the function returns false and the state
//of the reference parameter(outItem) is undefined. If the
//queue is not empty, the function returns true and outItem
//becomes a copy of the next item in the queue, which is
//removed from the data structure.
bool FIFOQueueClass< NODETYPE >::dequeue(NODETYPE &outItem) {

  LinkedNodeClass<NODETYPE> *curNode = head;

  //if nothing to dequeue, return false
  if(head == NULL) {
  
    return false;
  
  }
  else {
  //get element at head

    outItem = head -> getValue();
    head = head -> getNext();
    delete curNode;

    //if head is null, empty fifo
    if(head == NULL) {

      tail = NULL;
    
    }
    else {
    //empty previous pointers
    //connect with the next pointer

      head -> setPreviousPointerToNull();
      head -> setBeforeAndAfterPointers();
      
    }

    return true;
  
  }
}


template < class NODETYPE >
//Prints out the contents of the queue. All printing is done
//on one line, using a single space to separate values, and a
//single newline character is printed at the end.
void FIFOQueueClass< NODETYPE >::print() const {

  LinkedNodeClass<NODETYPE> *curNode = head;
    
  //print from front to end   
  while(curNode) {

    cout << curNode -> getValue() << " ";
    curNode = curNode -> getNext();

  }  

  cout << endl;

}


template < class NODETYPE >
//Returns the number of nodes contained in the queue.
int FIFOQueueClass< NODETYPE >::getNumElems() const {

  int countNum = 0;
  LinkedNodeClass<NODETYPE> *curNode = head;
  
  //iterate through list and get number
  while(curNode) {
  
      countNum ++;
      curNode = curNode -> getNext();

  }

  return countNum;

}


template < class NODETYPE >
//Clears the queue to an empty state without resulting in any
//memory leaks.
void FIFOQueueClass< NODETYPE >::clear() {

  LinkedNodeClass<NODETYPE> *curNode = head;

  //clear and delete every element of list
  while(head != NULL) {

    curNode = head;
    head = head -> getNext();
    delete curNode;

  }

  head = NULL;
  tail = NULL;

}
