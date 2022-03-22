//program header
//project3:
//tingjie yu
//date: 10/30/2021
//purpose of code: main inplement
//select which modification to do 
//and call specify functions

//library includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;
#include "ColorClass.h"
#include "ColorImageClass.h"


int main() {
  string contentInFile;
  ifstream* inFile = new ifstream;
  ifstream insertFile;
  ofstream* outFile = new ofstream;
  int inModif = START_MODI;
  ColorImageClass* currImage = new ColorImageClass;

  //load ppm image into readFile
  cout << "Enter string for PPM image file name to load: ";
  currImage -> readFile(inFile);


  while (inModif != EXIT_PROGRAM) {

    std::cout << "1. Annotate image with rectangle" << '\n';
    std::cout << "2. Annotate image with pattern from file" << '\n';
    std::cout << "3. Insert another image" << '\n';
    std::cout << "4. Write out current image" << '\n';
    std::cout << "5. Exit the program" << '\n';
    std::cout << "Enter int for main menu choice: " ;
    cin >> inModif;
    currImage -> checkCinInt();
    
    if (inModif == ANOTA_RECTAN) {

      //Annotate image with rectangle
      currImage -> annotateRectangle();

    }
    else if (inModif == ANOTA_PATTERN) {

      //Annotate image with pattern from file
      currImage -> insertImageOrPattern(true);

    }
    else if (inModif == INSERT_IMAGE) {

      //Insert another image
      currImage -> insertImageOrPattern();

    }
    else if (inModif == WRITE_OUT_CURR_IMAGE) {

      //Write out current image
      currImage -> outputImage(outFile);

    }
    else if (inModif == EXIT_PROGRAM) {

     //Exit program
     cout << "Thank you for using this program" << endl;

    }
    else {

     cout << "invalid input, you should input value between 1 to 5" << endl;

    }

  }

  delete currImage;
  delete inFile;
  delete outFile;

}
