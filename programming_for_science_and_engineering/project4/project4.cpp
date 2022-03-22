//program header
//project4:
//tingjie yu
//date: 11/14/2021
//purpose of code: main function of project4
//include some testcases 

#include <iostream>
using namespace std;
#include "SortedListClass.h"
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main() {
  //This is just a placeholder main function - it does exceptionally
  //little actual testing, so you'll want to add your own tests here.
  //Feel free to leave your tests in the version of this file you
  //submit, but we will not be running your main function, so the
  //output, etc., of your main doesn't need to match anything from
  //a sample output, etc


  //test sorted list
  SortedListClass< float > testList;
  float outItem;
  float outVal;
  int index = 0;
  testList.printForward();
  testList.insertValue(42);
  testList.insertValue(4); 
  testList.insertValue(10);
  testList.insertValue(100);
  testList.printForward();
  testList.printBackward();
 
  //test deep copy for constructor
  cout << "==========================" << endl;
  cout << "print copylist: " << endl;
  SortedListClass< float >  copyList(testList);
  copyList.printForward();
  copyList.printBackward();

  cout << "==========================" << endl;

   //test getElemAtIndex
   //getNumElems
   //removeFront
   //removeLast
   //insertValue
   for(int i = 0; i< 3; i++) {

    cout << "==========================" << endl;
    cout << "index num: " << index << endl;
    cout << "index valid: " << testList.getElemAtIndex(index,outVal) << endl;
    cout << "outVal: " << outVal << endl;
    cout << "nums: " << testList.getNumElems() << endl;
    cout << "valid mv front: " << testList.removeFront(outItem) << endl;
    cout << "valid mv last: " << testList.removeLast(outItem) << endl;
    testList.insertValue(i);
    testList.printForward();
    testList.printBackward();
    cout << "outItem: " << outItem << endl;
    index = index + 1;
    cout << "==========================" << endl;

  }

  //test clear
  cout << "==========================" << endl;
  testList.printBackward();
  cout << "before clear: ";
  testList.insertValue(19);
  testList.printBackward();
  testList.clear();
  cout << "after clear: ";
  testList.printForward();
  cout << "==========================" << endl;





  //testcase for fifo
  FIFOQueueClass< float > testFifo;
  testFifo.print();
  testFifo.enqueue(12);  
  testFifo.enqueue(4);
  testFifo.enqueue(44); 
  testFifo.enqueue(10);

  //test getNumElems
  //test dequeue
  //outItem
  for(int i = 0; i< 5; i++) {

    cout << "nums: " << testFifo.getNumElems() << endl;
    cout << "valid: " << testFifo.dequeue(outItem) << endl;
    cout << "outItem: " << outItem << endl;
    testFifo.print();


  }
 
  //test clear
  testFifo.print();
  cout << "before clear: ";
  testFifo.enqueue(19);
  testFifo.print();
  testFifo.clear();
  cout << "after clear: ";
  testFifo.print();


  cout << "==========================" << endl;
 
  return 0;
}

#endif
