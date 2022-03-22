//program header
//project4:
//tingjie yu
//date: 11/14/2021
//purpose of code: implementation for LinkedNodeClass
//define linkednode
//The list node class will be the data type for individual nodes of
//a doubly-linked data structure



//library includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;
#include "LinkedNodeClass.h"


template < class NODETYPE >
//constructer, define prenode, nextnode, and nodeval
LinkedNodeClass< NODETYPE > ::LinkedNodeClass( 
  LinkedNodeClass< NODETYPE > *inPrev, 
  const NODETYPE &inVal,
  LinkedNodeClass< NODETYPE > *inNext) {
    
  nodeVal = inVal;
  prevNode = inPrev;
  nextNode = inNext;

}

template < class NODETYPE >
//Returns the value stored within this node.
NODETYPE LinkedNodeClass< NODETYPE > ::getValue() const {

  return nodeVal;

}

template < class NODETYPE >
//Returns the address of the node that follows this node.
LinkedNodeClass< NODETYPE >* LinkedNodeClass< NODETYPE > ::getNext() const {

  return nextNode;

}


template < class NODETYPE >
//Returns the address of the node that comes before this node.
LinkedNodeClass< NODETYPE >* LinkedNodeClass< NODETYPE > ::getPrev() const {

  return prevNode;

}


template < class NODETYPE >
//Sets the object’s next node pointer to NULL.
void LinkedNodeClass< NODETYPE >::setNextPointerToNull() {

  nextNode = NULL;

}


template < class NODETYPE >
//Sets the object's previous node pointer to NULL.
void LinkedNodeClass< NODETYPE >::setPreviousPointerToNull() {

  prevNode = NULL;      

}


template < class NODETYPE >
void LinkedNodeClass< NODETYPE >::setBeforeAndAfterPointers() {

  if(prevNode == NULL && nextNode == NULL) {
  //if this node is single element, do nothing

  }
  else if (prevNode == NULL) {
  //if this node is tail

    nextNode -> prevNode = this;  

  }
  else if (nextNode == NULL) {
  //if this node is head

    prevNode -> nextNode = this;

  }
  else{
  //if this node is in the  middle

    prevNode -> nextNode = this;
    nextNode -> prevNode = this;  

  }
}


