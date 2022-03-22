//program header
//project3:
//tingjie yu
//date: 10/30/2021
//purpose of code: implementation of ColorClass 
//library includes

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;
#include "ColorClass.h"

ColorClass::ColorClass() {
  setToWhite();
}

//setTo Color with error handle to check if it beyonds FULL_COLOR
bool ColorClass::setTo(int inRed, int inGreen, int inBlue) {

  bool FalseValue = false;
  if (inRed > FULL_COLOR) {
    FalseValue = true;
  }
  else if (inRed < NO_COLOR) {
    FalseValue = true;
  }
  else {
    selfRed = inRed;
  }

  if (inGreen > FULL_COLOR) {
    FalseValue = true;
  }
  else if (inGreen < NO_COLOR) {
    FalseValue = true;
  }
  else {
    selfGreen = inGreen;
  }

  if (inBlue > FULL_COLOR) {
    FalseValue = true;
  }
  else if (inBlue < NO_COLOR) {
    FalseValue = true;
  }
  else {
    selfBlue = inBlue;
  }

  if (FalseValue == true) {
    cout << "error! go beyond range for color input!"<< endl;
    exit(0);
  }

  return FalseValue;

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

bool ColorClass::setTo(ColorClass& inColor) {

  return setTo(inColor.selfRed, inColor.selfGreen, inColor.selfBlue);

}

//determine if two ColorClass objects are the same
bool ColorClass::isSameColor(ColorClass &inColor) {

  if (inColor.selfRed == selfRed
  && inColor.selfGreen == selfGreen
  && inColor.selfBlue == selfBlue) {
    return true;
  }
  else {
    return false;
  }

};


//output Colors into outFile
void ColorClass::outputColor(ofstream* outFile, bool endCol) {

  if (outFile -> is_open()) {
    if (endCol != true) {
      *outFile << selfRed << ' ' << selfGreen << ' ' << selfBlue << ' ';
    }
    else {
      *outFile << selfRed << ' ' << selfGreen << ' ' << selfBlue;
    }
  }

}


ColorClass::~ ColorClass() {
}
