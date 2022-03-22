//program header
//project3:
//tingjie yu
//date: 10/30/2021
//purpose of code: headerfiles for ColorImageClass

#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include "constants.h"
#include "ColorClass.h"

class ColorImageClass {
private:
  ColorClass **selfPixel;
  int numRows;
  int numColumns;

public:
  ColorImageClass();
  void readFile(ifstream* inFile, bool isPattern = false);
  void annotateRectangle();
  void insertImageOrPattern(bool insertPattern = false);
  int selectOptionColor(int selectType);
  void setToColor(int selectColor, ColorClass& inputPixel);
  void outputImage(ofstream* outFile);
  void checkCinInt();
  ~ ColorImageClass();
  
};

#endif
