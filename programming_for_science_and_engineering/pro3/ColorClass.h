//program header
//project3:
//tingjie yu
//date: 10/30/2021
//purpose of code: header files for ColorClass
//define functions related to Color

#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include "constants.h"

class ColorClass {
private:
  int selfRed;
  int selfGreen;
  int selfBlue;

public:
  ColorClass();
  bool setTo(int inRed, int inGreen, int inBlue);
  void setToBlack();
  void setToRed();
  void setToGreen();
  void setToBlue();
  void setToWhite();
  bool setTo(ColorClass& inColor);
  bool isSameColor(ColorClass &inColor);
  void outputColor(ofstream* outFile, bool endCol);
  ~ ColorClass();
};

#endif
