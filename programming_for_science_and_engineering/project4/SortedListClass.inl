//program header
//project4:
//tingjie yu
//date: 11/14/2021
//purpose of code: implementation for sortedlistsclass

//library includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

template < class NODETYPE >
//Default Constructor. Will properly initialize a list to
//be an empty list, to which values can be added.
SortedListClass< NODETYPE >::SortedListClass() {

  head = NULL;
  tail = NULL;

}

template < class NODETYPE >
//Copy constructor. Will make a complete(deep) copy of the list, such
//that one can be changed without affecting the other.
SortedListClass< NODETYPE >::SortedListClass(const SortedListClass &rhs) {

  head = NULL;
  tail = NULL;
  
  //cout << "debug2 " << rhs.head -> getValue();
  LinkedNodeClass<NODETYPE> *curNode = rhs.head;
  //cout << "debug " << rhs.head -> getValue();

  //deep copy each element of input sortedlist
  while (curNode != NULL) {

    insertValue(curNode -> getValue());
    curNode = curNode -> getNext();

  }
}


template < class NODETYPE >
//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is
//being destroyed.
SortedListClass< NODETYPE >::~SortedListClass() {

  clear();

}


template < class NODETYPE >
//Clears the list to an empty state without resulting in any
//memory leaks.
void SortedListClass< NODETYPE >::clear() {

  LinkedNodeClass<NODETYPE> *curNode;

  while(head != NULL) {

    curNode = head;
    head = head -> getNext();
    delete curNode;

  }

  tail = NULL;

}


template < class NODETYPE >
//Allows the user to insert a value into the list. Since this
//is a sorted list, there is no need to specify where in the list
//to insert the element. It will insert it in the appropriate
//location based on the value being inserted. If the node value
//being inserted is found to be "equal to" one or more node values
//already in the list, the newly inserted node will be placed AFTER
//the previously inserted nodes.
void SortedListClass< NODETYPE >::insertValue(
  const NODETYPE &valToInsert) {

  LinkedNodeClass<NODETYPE> *curNode = head;

  //search the proper position for insertvalue in sorted list
  while(curNode && curNode -> getValue() <= valToInsert) {

    curNode = curNode -> getNext();

  }

  //if list is empty
  if(curNode == NULL && tail == NULL) {

    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
      NULL, valToInsert, NULL);
    
    head = insertedNode;
    tail = insertedNode;

  }
  else if(curNode == NULL) {
  //if insert after tail

    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
      tail, valToInsert, NULL);
    
    tail = insertedNode;
    insertedNode -> setBeforeAndAfterPointers();

 
  }
  else if(curNode == head) {
  //if insert before head

    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
      NULL, valToInsert, curNode);
    
    head = insertedNode;
    insertedNode -> setBeforeAndAfterPointers();

  }
  else {
  //insert inside the list

    LinkedNodeClass<NODETYPE>* insertedNode = new LinkedNodeClass<NODETYPE>(
      curNode -> getPrev(), valToInsert, curNode);

    insertedNode -> setBeforeAndAfterPointers();

  }
}


template < class NODETYPE >
//Prints the contents of the list from head to tail to the screen.
//Begins with a line reading "Forward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
void SortedListClass< NODETYPE >::printForward() const {

  LinkedNodeClass<NODETYPE> *curNode = head;
    
  cout << "Forward List Contents Follow:" << endl;
  
  //start from head to print forward
  while(curNode) {

    cout << "  " << curNode -> getValue() << endl;
    curNode = curNode -> getNext();

  }

  cout << "End Of List Contents" << endl;
  
}


template < class NODETYPE >
//Prints the contents of the list from tail to head to the screen.
//Begins with a line reading "Backward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End Of List Contents" to indicate the end of the list.
void SortedListClass< NODETYPE >::printBackward() const {

  LinkedNodeClass<NODETYPE> *curNode = tail;
    
  cout << "Backward List Contents Follow:" << endl;

  //start from tail to print backward
  while(curNode) {

    cout << "  " << curNode -> getValue() << endl;
    curNode = curNode -> getPrev();

  }

  cout << "End Of List Contents" << endl;

}


template < class NODETYPE >
//Removes the front item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the first item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
bool SortedListClass< NODETYPE >::removeFront(NODETYPE &theVal) {

  LinkedNodeClass<NODETYPE> *curNode = head;

  //if nothing to remove
  if(head == NULL) {
  
    return false;
  
  }
  else {
  //remove head

    theVal = head -> getValue();
    head = head -> getNext();
    delete curNode;
    
    //if head turns into Null
    //no previous pointer needed to Null
    if(head == NULL) {

      tail = NULL;

    } 
    else {

      head -> setPreviousPointerToNull();
      head -> setBeforeAndAfterPointers();

    }

    return true;
  
  }
}


template < class NODETYPE >
//Removes the last item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the last item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
bool SortedListClass< NODETYPE >::removeLast(NODETYPE &theVal) {

  LinkedNodeClass<NODETYPE> *curNode = tail;

  //nothing to remove, return false
  if(tail == NULL) {
  
    return false;
  
  }
  else {
  //remove tail

    theVal = tail -> getValue();
    tail = tail -> getPrev();
    delete curNode;

    //if tail is Null, empty list
    //else, set next to Null since deleted already
    if(tail == NULL) {
    
      head = NULL;

    }
    else {
 
      tail -> setNextPointerToNull();
      tail -> setBeforeAndAfterPointers();
  
    }

    return true;
  
  }
}


template < class NODETYPE >
//Returns the number of nodes contained in the list.
int SortedListClass< NODETYPE >::getNumElems() const {

  int countNum = 0;
  LinkedNodeClass<NODETYPE> *curNode = head;
  
  while(curNode) {
  
      countNum ++;
      curNode = curNode -> getNext();

  }

  return countNum;

}


template < class NODETYPE >
//Provides the value stored in the node at index provided in the
//0-based "index" parameter. If the index is out of range, then outVal
//remains unchanged and false is returned. Otherwise, the function
//returns true, and the reference parameter outVal will contain
//a copy of the value at that location.
bool SortedListClass< NODETYPE >::getElemAtIndex(
  const int index,
  NODETYPE &outVal) const {

  LinkedNodeClass<NODETYPE> *curNode = head;
  int curIndex = 0;
  
  //search through list
  while(curNode && curIndex < index) {
    
    curNode = curNode -> getNext();
    curIndex = curIndex + 1;

  }
  
  //if find the index and curNode valid
  if(curNode && curIndex == index) {
    
    outVal = curNode -> getValue();
    return true;

  }
  else {

    return false;

  }
}
