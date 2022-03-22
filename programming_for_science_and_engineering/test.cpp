#include <iostream>
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "LIFOStackClass.h"
using namespace std;


#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main() {
    //This is just a placeholder main function - it does exceptionally
    //little actual testing, so you'll want to add your own tests here.
    //Feel free to leave your tests in the version of this file you
    //submit, but we will not be running your main function, so the
    //output, etc., of your main doesn't need to match anything from
    //a sample output, etc.
    SortedListClass testList;
    //test print and insert and getNumElems()
    testList.printForward();
    testList.insertValue(42);
    testList.insertValue(5);
    testList.insertValue(9);
    testList.insertValue(8);
    testList.printForward();
    testList.insertValue(4);
    testList.printForward();
    testList.clear();
    cout << "-------------------------" << endl;
    testList.insertValue(42);
    testList.insertValue(5);
    testList.insertValue(9);
    testList.insertValue(8);
    testList.printForward();
    testList.insertValue(4);
    testList.printForward();

    int listLeng = 0;
    listLeng = testList.getNumElems();
    cout << "List1 length: " << listLeng << endl;
    cout << "-------------------------" << endl;

    //test deep copy
    SortedListClass copyList(testList); 
    copyList.insertValue(11);
    copyList.insertValue(12);
    copyList.printForward();
    cout << "-------------------------" << endl;


    //remove elements in testList and test printBackward,getElemAtIndex
    int remFront = 0;
    int remBack = 0;
    testList.removeFront(remFront);
    testList.printBackward();
    cout << "-------------------------" << endl;
    testList.removeLast(remBack);
    testList.printBackward();
    cout << "-------------------------" << endl;
    int outValueSorted = 0;
    testList.getElemAtIndex(2, outValueSorted);
    cout << "getEle: " << outValueSorted << endl;
    testList.clear();
    testList.printForward();
    cout << "-------------------------" << endl;

    //FIFOQueue test all functions
    FIFOQueueClass testList2;
    testList2.print();
    testList2.enqueue(5);
    testList2.enqueue(7);
    testList2.enqueue(12);
    testList2.enqueue(25);
    testList2.print();
    int outQueue = 0;
    testList2.dequeue(outQueue);
    cout << "outNum: " << outQueue << endl;
    int list2Leng = 0;
    list2Leng = testList2.getNumElems();
    cout << "List2 length: " << list2Leng << endl;
    testList2.clear();
    testList2.print();
    cout << "-------------------------" << endl;

    //LIFOStack test all functions
    LIFOStackClass testList3;
    testList3.print();
    testList3.push(1);
    testList3.push(3);
    testList3.push(5);
    testList3.print();
    int popVal = 0;
    testList3.pop(popVal);
    cout << "popnum: " << popVal << endl;
    int list3Leng = 0;
    list3Leng = testList3.getNumElems();
    cout << "List3 length: " << list3Leng << endl;
    testList3.clear();
    testList3.print();
    return 0;
  
}
#endif
