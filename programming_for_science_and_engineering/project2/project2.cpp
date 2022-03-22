//library includes
#include <iostream>
using namespace std;

//program header
//tingjie yu
//project2:
//frameworks with ColorClass, RowColumnClass, ColorImageClass
//ColorClass: define functions and definitions of Red,Green, Blue of pixel
//RowColumnClass: define functions and definitions of Row and Column of pixel
//ColorImageClass:define functions and definitions of pixel

//global constant declarations and initializations
//define maximum and minimum of color value
const int FULL_COLOR = 1000;
const int NO_COLOR = 0;

//define maximum and minimum of Row and Column
const int DEFAULT_ROW = -99999;
const int DEFAULT_COL = -99999;

//define size of row and Column
const int SIZE_OF_ROW = 10;
const int SIZE_OF_COL = 18;


//global function prototypes and documentation here
//class definitions (method prototypes w/ comments, no implementations)
//define colors of Red, green and blue
//define functins to set, change and print color
class ColorClass {
private:
  int selfRed;
  int selfGreen;
  int selfBlue;

public:
  ColorClass();
  ColorClass (int inRed, int inGreen, int inBlue);
  bool setTo(int inRed, int inGreen, int inBlue);
  void setToBlack();
  void setToRed();
  void setToGreen();
  void setToBlue();
  void setToWhite();
  bool setTo(ColorClass &inColor);
  bool addColor(ColorClass &rhs);
  bool subtractColor(ColorClass &rhs);
  bool adjustBrightness(double adjFactor);
  void printComponentValues();
  ~ ColorClass();

};


//define vaules of Row and column
//define functions to set, get, add and print RowCol
class RowColumnClass {
private:
  int selfRow;
  int selfCol;

public:
  RowColumnClass();
  RowColumnClass(int inRow, int inCol);
  void setRowCol(int inRow, int inCol);
  void setRow(int inRow);
  void setCol(int inCol);
  int getRow();
  int getCol();
  void addRowColTo(RowColumnClass &inRowCol);
  void printRowCol();
  ~ RowColumnClass();

};


//define image with pixel of fixed size of [SIZE_OF_ROW][SIZE_OF_COL]
//define functions to initialize, add, set color and print image
class ColorImageClass {
private:
  ColorClass selfPixel [SIZE_OF_ROW][SIZE_OF_COL];

public:
  ColorImageClass();
  void initializeTo(ColorClass &inColor);
  bool addImageTo(ColorImageClass &rhsImg);
  bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd []);
  bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
  bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
  void printImage();
  ~ ColorImageClass();

};



//implementation of main function goes here
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main() {
  //implementation of main function
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;
  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;
  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor)) {
    testColor.printComponentValues();
  }
  else {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor)) {
    testColor.printComponentValues();
  }
  else {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);

  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2) {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
      testColor.printComponentValues();
    }
    else {
      cout << "Invalid Index!";
    }
    cout << endl;
  }

  for (int rowInd = 0; rowInd < 8; rowInd += 2) {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
      testColor.printComponentValues();
    }
    else {
      cout << "Invalid Index!";
    }
    cout << endl;
  }

  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;

}
#endif

//global function definitions (if needed)
//class method definitions
//implementation of methods in ColorClass
ColorClass::ColorClass() {

  setToWhite();

}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue) {

  setTo(inRed, inGreen, inBlue);

}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue) {

  bool valueClipped = false;

  //deal with clip issue and others can be applied
  //setRed and clip color when it goes beyond the boundary
  if (inRed > FULL_COLOR) {

    selfRed = FULL_COLOR;
    valueClipped = true;

  }
  else if (inRed < NO_COLOR) {

    selfRed = NO_COLOR;
    valueClipped = true;

  }
  else {

    selfRed = inRed;

  }

  //setGreen and clip color when it goes beyond the boundary
  if (inGreen > FULL_COLOR) {

    selfGreen = FULL_COLOR;
    valueClipped = true;

  }
  else if (inGreen < NO_COLOR) {

    selfGreen = NO_COLOR;
    valueClipped = true;

  }
  else {

    selfGreen = inGreen;

  }

  //setBlue and clip color when it goes beyond the boundary
  if (inBlue > FULL_COLOR) {

    selfBlue = FULL_COLOR;
    valueClipped = true;

  }
  else if (inBlue < NO_COLOR) {

    selfBlue = NO_COLOR;
    valueClipped = true;

  }
  else {

    selfBlue = inBlue;

  }

  return valueClipped;

}

//call functions of setTo and reduce duplicate code
void ColorClass::setToBlack() {

  setTo(NO_COLOR, NO_COLOR, NO_COLOR);

}

void ColorClass::setToRed() {

  setTo(FULL_COLOR, NO_COLOR, NO_COLOR);

}

void ColorClass::setToGreen() {

  setTo(NO_COLOR, FULL_COLOR, NO_COLOR);

}

void ColorClass::setToBlue() {

  setTo(NO_COLOR, NO_COLOR, FULL_COLOR);

}

void ColorClass::setToWhite() {

  setTo(FULL_COLOR, FULL_COLOR, FULL_COLOR);

}

bool ColorClass::setTo(ColorClass &inColor) {

  return setTo(inColor.selfRed, inColor.selfGreen, inColor.selfBlue);

}

bool ColorClass::addColor(ColorClass &rhs) {

  int resultRed = selfRed + rhs.selfRed;
  int resultGreen = selfGreen + rhs.selfGreen;
  int resultBlue = selfBlue + rhs.selfBlue;

  return setTo(resultRed, resultGreen, resultBlue);

}

bool ColorClass::subtractColor(ColorClass &rhs) {

  int resultRed = selfRed - rhs.selfRed;
  int resultGreen = selfGreen - rhs.selfGreen;
  int resultBlue = selfBlue - rhs.selfBlue;

  return setTo(resultRed, resultGreen, resultBlue);

}

bool ColorClass::adjustBrightness(double adjFactor) {

  int adjRed = (int) selfRed * adjFactor;
  int adjGreen = (int) selfGreen * adjFactor;
  int adjBlue = (int) selfBlue * adjFactor;

  return setTo(adjRed, adjGreen, adjBlue);

}

void ColorClass::printComponentValues() {

  std::cout << "R: " << selfRed;
  std::cout << " G: " << selfGreen;
  std::cout << " B: " << selfBlue;

}

ColorClass::~ ColorClass() {
}


//implementation of methods in RowColumnClass
RowColumnClass::RowColumnClass() {

  selfRow = DEFAULT_ROW;
  selfCol = DEFAULT_COL;

}

RowColumnClass::RowColumnClass(int inRow, int inCol) {

  selfRow = inRow;
  selfCol = inCol;

}

void RowColumnClass::setRowCol(int inRow, int inCol) {

  selfRow = inRow;
  selfCol = inCol;

}

void RowColumnClass::setRow(int inRow) {

  selfRow = inRow;

}

void RowColumnClass::setCol(int inCol) {

  selfCol = inCol;

}

int RowColumnClass::getRow() {

  return selfRow;

}

int RowColumnClass::getCol() {

  return selfCol;

}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol) {

  selfRow = selfRow + inRowCol.selfRow;
  selfCol = selfCol + inRowCol.selfCol;

}

void RowColumnClass::printRowCol() {

  std::cout << "["<<selfRow<<","<<selfCol<<"]";

}

RowColumnClass::~ RowColumnClass() {
}


//implementation of methods in ColorImageClass
ColorImageClass::ColorImageClass() {

  for (int i = 0 ; i < SIZE_OF_ROW ; i++) {
    for (int j = 0 ; j < SIZE_OF_COL ; j++) {

      selfPixel[i][j].setToBlack();

    }
  }
}

void ColorImageClass::initializeTo(ColorClass &inColor) {

  for (int i = 0 ; i < SIZE_OF_ROW ; i++) {
    for (int j = 0 ; j < SIZE_OF_COL ; j++) {

      selfPixel[i][j].setTo(inColor);

    }
  }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg) {

  bool valueClipped = false;

  for (int i = 0 ; i < SIZE_OF_ROW ; i++) {
    for (int j = 0 ; j < SIZE_OF_COL ; j++) {

      valueClipped += selfPixel [i][j].addColor(rhsImg.selfPixel[i][j]);

    }
  }

  return valueClipped;

}

//this function has issue, to be debuged
bool ColorImageClass::addImages(
  int numImgsToAdd, ColorImageClass imagesToAdd []) {

    bool valueClipped = false;
    ColorImageClass resultImage;

    //add all input images together and pass the result to resultImage
    for (int i = 0; i < numImgsToAdd; i++) {

      valueClipped += resultImage.addImageTo(imagesToAdd [i]);

    }

    //set selfPixel as resultImage
    for (int i = 0 ; i < SIZE_OF_ROW ; i++) {
      for (int j = 0 ; j < SIZE_OF_COL ; j++) {

        selfPixel [i][j] = resultImage.selfPixel[i][j];

      }
    }

    return valueClipped;

  }

  bool ColorImageClass::setColorAtLocation(
    RowColumnClass &inRowCol, ColorClass &inColor) {

      //set Color At Location when it is within valid row and column
      if(inRowCol.getRow() >= 0 && inRowCol.getRow() < SIZE_OF_ROW
      && inRowCol.getCol() >= 0 && inRowCol.getCol() < SIZE_OF_COL) {

        selfPixel [inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);

        return true;

      }

      return false;

    }

    bool ColorImageClass::getColorAtLocation(
      RowColumnClass &inRowCol, ColorClass &outColor) {

        //get color at location when it is within valid row and column
        if(inRowCol.getRow() >= 0 && inRowCol.getRow() < SIZE_OF_ROW
        && inRowCol.getCol() >= 0 && inRowCol.getCol() < SIZE_OF_COL) {

          outColor = selfPixel [inRowCol.getRow()][inRowCol.getCol()];

          return true;

        }

        return false;

      }

      void ColorImageClass::printImage() {

        for (int i = 0 ; i < SIZE_OF_ROW ; i++) {
          for (int j = 0 ; j < SIZE_OF_COL ; j++) {

            selfPixel [i][j].printComponentValues();

            //except for last column, others are seperated with '--'
            if (j != SIZE_OF_COL-1) {

              cout << "--";

            }

          }

          cout << "\n";

        }
      }

      ColorImageClass::~ ColorImageClass() {
      }
