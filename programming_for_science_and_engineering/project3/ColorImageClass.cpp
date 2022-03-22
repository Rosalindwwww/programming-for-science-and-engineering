//program header
//project3:
//tingjie yu
//date: 10/30/2021
//purpose of code: implement colorImageClass


//library includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;
#include "ColorImageClass.h"



ColorImageClass::ColorImageClass() {

  numRows = DEFAULT_VAL;
  numColumns = DEFAULT_VAL;

}


//readFile from inFile
void ColorImageClass::readFile
(ifstream* inFile, bool isPattern, bool isLoad,
 int insertRow, int insertCol) {

  string fileType = "NOTHING_HERE";
  int maxColor = DEFAULT_VAL;
  bool validInputFound = false;
  string inputImage;

  //error handle to check if input file is valid
  while (!validInputFound) {

    cin >> inputImage;

    if (cin.fail()) {

      cin.clear();
      cin.ignore(200, '\n');
      cout << "Wrong cin inputs, you should input string!" << '\n';

      if (isLoad) {

        exit(0);

      }
    }

    inFile -> open((inputImage).c_str());

    if (inFile -> fail()) {

        if (isLoad) {

          cout << "Unable to open input file!" << '\n';
          exit(0);

        }

        cout << "Unable to open input file!" << '\n';
        cout << "try again! Enter string for file name: " ;

    }
    else {

      //if input file is not pattern, it defaults to be PPM
      if (!isPattern) {
        
        *inFile >> fileType;

        *inFile >> numColumns;

        *inFile >> numRows;

        *inFile >> maxColor;

        if (fileType != PPM_IMAGE || maxColor != FULL_COLOR
            || numRows <= 0 || numColumns <= 0
            || ((insertCol != DEFAULT_VAL && insertRow != DEFAULT_VAL)
            && (numRows > insertRow || numColumns > insertCol))) {

          //handle invalid file type
          if (fileType != PPM_IMAGE) {

            cout << "Error found when trying to read magic number";
            cout << " - expected P3 but found " << fileType;
            cout << endl;

          }
          
          //handle invalid max color
          if (maxColor != FULL_COLOR) {

            cout << "maxColor should be 255" << '\n';

          }
            
          //handle invalid rows and columns definition 
          if (numRows <= 0 || numColumns <= 0) {

            cout << "numRows and numColumns should larger than 0" << '\n';

          }

          //handle large inserted image
          if (insertCol != DEFAULT_VAL && insertRow != DEFAULT_VAL
              && (numRows > insertRow || numColumns > insertCol)) {

            cout << "inserted images is too big!" << endl;

          }
          
          //error handle for load ppm
          if (isLoad) {
          
            inFile -> close();
            exit(0);

          }

          cout << "Enter string for PPM image file name: ";
          validInputFound = false;
          inFile -> close();
         
        }
        else{

          validInputFound = true;

          //dynamic allocate 2D array
          selfPixel = new ColorClass*[numRows];

          for (int rowInd = 0; rowInd < numRows; rowInd++) {

            selfPixel[rowInd] = new ColorClass[numColumns];

          }

          //pass inFile into selfPixel and store color
          for (int rowInd = 0; rowInd < numRows; rowInd++) {
            for (int colInd = 0; colInd < numColumns; colInd++) {
              
              if (validInputFound 
                  && selfPixel[rowInd][colInd].readColor(inFile)) {

                validInputFound = false;

              }               
            }
          }

          //end of file is expected to have no more data
          if (validInputFound && !inFile -> eof()) {

            int endOfFile = NOTHING_HERE;

            *inFile >> endOfFile;

            if (!inFile -> fail()) {
              
              validInputFound = false;
              cout << "mismatches in dimensions! invalid file!" << endl;

            }
          }


          //if input not valid, trigger delete process 
          if (!validInputFound) {

            if (isLoad) {

              inFile -> close();
              exit(0);

            }
            else {

              inFile -> close();
              cout << "try again! Enter string for PPM image file:";

            }

            for (int rowInd = 0; rowInd < numRows; rowInd++) {

              delete [] selfPixel[rowInd];

            }

              delete [] selfPixel;

          }
        }
      }
    
      else {

        //read in pattern
        *inFile >> numColumns;
        //cout << "column" << numColumns << endl;

        *inFile >> numRows;
        //cout << "row" << numRows << endl;        

        if (numRows <= 0 || numColumns <= 0
            ||((insertCol != DEFAULT_VAL && insertRow != DEFAULT_VAL)
            && (numRows > insertRow || numColumns > insertCol))) {

          if (numRows <= 0 || numColumns <= 0) {

            cout << "numRows and numColumns should larger than 0" << '\n';

          }

          //error handle for large inserted image
          if (insertCol != DEFAULT_VAL && insertRow != DEFAULT_VAL
              && (numRows > insertRow || numColumns > insertCol)) {

            cout << "insered images is too big!" << endl;

          }

          cout << "try again! Enter string for files with pattern: ";
          inFile -> close();

        }
        else {

          validInputFound = true;

          //dynamic allocate 2D array
          selfPixel = new ColorClass*[numRows];

          for (int rowInd = 0; rowInd < numRows; rowInd++) {

            selfPixel[rowInd] = new ColorClass[numColumns];

          }

          for (int rowInd = 0; rowInd < numRows; rowInd++) {
            for (int colInd = 0; colInd < numColumns; colInd++) {
              //convert pattern into image
              if (validInputFound 
                  && selfPixel[rowInd][colInd].readPattern(inFile)) {

                validInputFound = false;
               
              }
            }
          }

          //expect the eof is empty, else throw error information
          if (validInputFound && !inFile -> eof()) {

            int endOfFile = NOTHING_HERE;

            *inFile >> endOfFile;

            if (!inFile -> fail()) {
              
              validInputFound = false;
              cout << "mismatches in dimensions! invalid file!" << endl;

            }
          }

          //error handle for invalid pattern file
          if (!validInputFound) {

            inFile -> close();

            cout << "try again! Enter string for files with pattern: ";

            for (int rowInd = 0; rowInd < numRows; rowInd++) {

              delete [] selfPixel[rowInd];

            }

            delete [] selfPixel;

          }
        }
      }
    }
  }  
}

//to annotate rectangle
void ColorImageClass::annotateRectangle() {
  int selectSpecif;
  int inCenterRow;
  int inCenterCol;
  int inHalfRow;
  int inHalfCol;
  int selectColor;
  int seletFill;
  int startRow;
  int endRow;
  int startCol;
  int endCol;
  int rowNumRectangle;
  int colNumRectangle;
  bool validSpecif = false;
  bool validRowCol = false;
  bool validFillSel = false;

  //select specifying option
  while (!validSpecif) {

    cout << "1. Specify upper left and ";
    cout << "lower right corners of rectangle" << '\n';
    cout << "2. Specify upper left corner and ";
    cout << "dimensions of rectangle" << '\n';
    cout << "3. Specify extent from center of rectangle" <<'\n';
    cout << "Enter int for rectangle specification method: ";

    cin >> selectSpecif;
    checkCinInt();

    //error handle to check if specify is valid or not!
    if (selectSpecif >= SPECI_UP_LEFT_LOWER_RIGHT
        && selectSpecif <= SPECI_CENTER_EXTEN) {

      validSpecif = true;

    }
    else {

      cout << "Wrong selection for Specifying! select from 1, 2, 3" << '\n';

    }
  }

  while (!validRowCol) {

    //calculate row and column according to entered value
    if (selectSpecif == SPECI_UP_LEFT_LOWER_RIGHT) {

      cout << "Enter upper left corner row and column: ";
      cin >> startRow;
      cin >> startCol;

      cout << "Enter lower right corner row and column: ";
      cin >> endRow;
      cin >> endCol;

    }
    else if (selectSpecif == SPECI_UP_LEFT_DIMEN) {

      cout << "Enter upper left corner row and column: ";
      cin >> startRow;
      cin >> startCol;

      cout << "Enter int for number of rows: ";
      cin >> rowNumRectangle;

      cout << "Enter int for number of columns: ";
      cin >> colNumRectangle;

      endRow = startRow + rowNumRectangle;
      endCol = startCol + colNumRectangle;

    }
    else if (selectSpecif == SPECI_CENTER_EXTEN) {

      cout << "Enter rectangle center row and column: ";
      cin >> inCenterRow;
      cin >> inCenterCol;

      cout << "Enter int for half number of rows: ";
      cin >> inHalfRow;

      cout << "Enter int for half number of columns: ";
      cin >> inHalfCol;

      startRow = inCenterRow - inHalfRow;
      endRow = inCenterRow + inHalfRow;
      startCol = inCenterCol - inHalfCol;
      endCol = inCenterCol + inHalfCol;

    }

    //error handle to check if row and column are valid or not!
    if (cin.fail()) {

      cin.clear();
      cin.ignore(200, '\n');
      cout << "Wrong cin inputs, you should input int number!" << '\n';

    }
    else if (startRow >= 0 && endRow < numRows
             && startCol >= 0 && endCol < numColumns
             && startRow < endRow && startCol < endCol) {

      validRowCol = true;

    }
    else {

      cout << "Wrong selection for Row and Col! go beyond boundary!" << '\n';

    }
  }

  selectColor = selectOptionColor(SELECT_RECTAN);

  while (!validFillSel) {

    cout << "1. No" << '\n';
    cout << "2. Yes" << '\n';
    cout << "Enter int for rectangle fill option: ";
    cin >> seletFill;
    checkCinInt();

    //error handle to check if fill is within 1 and 2
    if (seletFill == NO_FILL || seletFill == DO_FILL) {

      validFillSel = true;

    }
    else {

      cout << "Wrong selection for seletFill! select from 1 or 2" << '\n';

    }
  }

  // fill in pixel
  for (int rowInd = startRow; rowInd < endRow; rowInd++) {
    for (int colInd = startCol; colInd < endCol; colInd++) {

      if (seletFill == NO_FILL) {

        if (rowInd == startRow || rowInd == endRow - 1
            || colInd == startCol || colInd == endCol - 1) {

          setToColor(selectColor, selfPixel[rowInd][colInd]);

        }
      }
      else {

        setToColor(selectColor, selfPixel[rowInd][colInd]);

      }
    }
  }
}


//insertImage and insert Pattern
//combine they together to reduce redundant codes
//default insert image
//if insertPattern is True, convert pattern into image
void ColorImageClass::insertImageOrPattern (bool insertPattern) {
  ColorImageClass* insertOneImage = new ColorImageClass;
  ifstream* insertFile = new ifstream;
  int startRow;
  int startCol;
  int endRow;
  int endCol;
  int selectColor;
  ColorClass referenceColor;
  bool validRowCol = false;
  bool validInsert = false;
  bool isLoad = false;

  //read in inserted image and read in inserted pattern
  while (!validInsert) {
    if (!insertPattern) {

      cout << "Enter string for file name of PPM image to insert: ";
      insertOneImage -> 
      readFile(insertFile, insertPattern, isLoad, numRows, numColumns);

    }
    else {

      cout << "Enter string for file name containing pattern: ";
      insertOneImage -> 
      readFile(insertFile, insertPattern, isLoad, numRows, numColumns);

    }

    //if inserted file is too big, close file
    if (insertOneImage -> numRows > numRows 
        || insertOneImage -> numColumns > numColumns) {

      //cout << "insered images is too big!" << endl;
      insertFile -> close();

    }
    else {
    
      validInsert = true;

    }
  }

  //error handle for valid row and column
  //input row and column
  while (!validRowCol) {

    cout << "Enter upper left corner to insert image row and column: ";
    cin >> startRow;
    cin >> startCol;

    if (cin.fail()) {

      cin.clear();
      cin.ignore(200, '\n');
      cout << "Wrong cin inputs, you should input int number!" << '\n';

    }
    else {
      //cout << "Row" << startRow << endl;
      //cout << "Col" << startCol << endl;

      endRow = startRow + insertOneImage -> numRows;
      endCol = startCol + insertOneImage -> numColumns;

      if (startRow >= 0 && endRow <= numRows
          && startCol >= 0 && endCol <= numColumns
          && startRow <= endRow && startCol <= endCol) {

        validRowCol = true;

      }
      else {

        cout << "Wrong input for startCol or startRow!" << endl;
        cout << "the range of Row is from 0 to ";
        cout << (numRows - insertOneImage -> numRows) << endl;
        cout << "the range of column is from 0 to ";
        cout << (numColumns - insertOneImage -> numColumns) << endl;

      }
    }
  }

  //get selectColor
  if (!insertPattern) {

    selectColor = selectOptionColor(SELECT_TRANSPARE);

  }
  else {

    selectColor = selectOptionColor(SELECT_PATTERN);

  }

  if (!insertPattern) {

    //referenceColor is the one that is transparent for inserted color
    //set the color in original files accoding to insered color
    setToColor(selectColor,referenceColor);

    for (int rowInd = startRow; rowInd < endRow; rowInd++) {
      for (int colInd = startCol; colInd < endCol; colInd++) {

        if (!insertOneImage
            -> selfPixel [rowInd-startRow][colInd-startCol]
            .isSameColor(referenceColor)) {

          selfPixel[rowInd][colInd]
          .setTo(insertOneImage
          -> selfPixel [rowInd-startRow][colInd-startCol]);

        }
      }
    }
  }
  else {

    //referenceColor is BLACK, since we set pattern element of 1 as black
    setToColor(OPTION_BLACK,referenceColor);

    for (int rowInd = startRow; rowInd < endRow; rowInd++) {
      for (int colInd = startCol; colInd < endCol; colInd++) {

        if (insertOneImage
            -> selfPixel [rowInd-startRow][colInd-startCol]
            .isSameColor(referenceColor)) {

          setToColor(selectColor,selfPixel[rowInd][colInd]);

        }
      }
    }
  }

  delete insertOneImage;
  delete insertFile;

}


//select color function to reduce redundant codes
int ColorImageClass::selectOptionColor(int selectType) {
  int selectColor;
  bool validColor = false;


  while (! validColor) {

    cout << "1. Red" << '\n';
    cout << "2. Green" << '\n';
    cout << "3. Blue" << '\n';
    cout << "4. Black" << '\n';
    cout << "5. White" << '\n';

    //different selectType has different output to print
    if (selectType == SELECT_RECTAN) {

      cout << "Enter int for rectangle color: ";

    }
    else if (selectType == SELECT_TRANSPARE) {

      cout << "Enter int for transparecy color: ";

    }
    else if (selectType == SELECT_PATTERN) {

      cout << "Enter int for pattern color: ";

    }

    cin >> selectColor;
    checkCinInt();
 
    //error handle
    if (selectColor < OPTION_RED || selectColor > OPTION_WHITE) {

      cout << "Wrong selection for Colors! select from 1 to 5" << '\n';

    }
    else {

      validColor = true;

    }
  }

  return selectColor;

}


//set input pixels according to selected color
void ColorImageClass::setToColor(int selectColor, ColorClass& inputPixel) {

  if (selectColor == OPTION_RED) {

    inputPixel.setToRed() ;

  }
  else if (selectColor == OPTION_GREEN) {

    inputPixel.setToGreen();

  }
  else if (selectColor == OPTION_BLUE) {

    inputPixel.setToBlue();

  }
  else if (selectColor == OPTION_BLACK) {

    inputPixel.setToBlack();

  }
  else if (selectColor == OPTION_WHITE) {

    inputPixel.setToWhite();

  }
}


//output image into outfile
void ColorImageClass::outputImage(ofstream* outFile) {
  string outputImage;

  cout << "Enter string for PPM file name to output: ";
  cin >> outputImage;

  if (cin.fail()) {

    cin.clear();
    cin.ignore(200, '\n');
    cout << "Wrong cin inputs, you should input string!" << '\n';

  }

  outFile -> open(outputImage.c_str());

  if (outFile -> fail()) {

    cout << "Unable to open output file" << endl;

  }
  else {

    *outFile << PPM_IMAGE << endl;
    *outFile << numColumns << ' ' << numRows << endl;
    *outFile << FULL_COLOR << endl;

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {

        bool endCol = (j == (numColumns - 1));
        selfPixel [i][j].outputColor(outFile, endCol);

      }

      *outFile << endl;

    }

    outFile -> close();

  }
}

//check cin
void ColorImageClass::checkCinInt() {

  if (cin.fail()) {

      cin.clear();
      cin.ignore(200, '\n');
      cout << "Wrong cin inputs, you should input int number!" << '\n';
      cout << "default value is set to 0!" << '\n';

  }
}


//clear pointer and free memory
ColorImageClass::~ ColorImageClass() {

  for (int rowInd = 0; rowInd < numRows; rowInd++) {

    delete [] selfPixel[rowInd];

  }

  delete [] selfPixel;

}
