/*********************************************************************
 File:     chromakey.cpp

 Author:   Audrey Kim

 Email address: amkim@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

double calcDistance(int red1, int gr1, int bl1, int red2, int gr2, int bl2);

int main(int argc, char *argv[])
{
  // Image data array
  // Note:  DON'T use the static keyword except where we expressly say so.
  //        It puts the large array in a separate, fixed, area of memory. 
  //        It is bad practice. But useful until we have dynamic allocation.
  static unsigned char inputImage[SIZE][SIZE][RGB];
  static unsigned char bgrndImage[SIZE][SIZE][RGB];
  static unsigned char outputImage[SIZE][SIZE][RGB];
  static bool chromaMask[SIZE][SIZE];

  double threshold;

  if (argc < 6) {
    cerr << "usage: program_name in.bmp background.bmp dist_threshold " 
         << "out1.bmp out2.bmp" << endl;
    return 0;
  }
	
  if (readRGBBMP(argv[1], inputImage)) {
    cerr << "Error reading file: " << argv[1] << endl;
    return 1;
  }

  if (readRGBBMP(argv[2], bgrndImage)) {
    cout << "Error reading file: " << argv[2] << endl;
    return 1;
  }
  
  // Write code to convert the threshold (argv[3])
  //  from string format to a double and assign the 'threshold'
  threshold = atof(argv[3]);

  // Call Method 1 Function
  method1(inputImage, chromaMask, threshold);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);

  // Write the output image to a file using the filename argv[4]
  if (writeRGBBMP(argv[4], outputImage)) {
    cout << "Error writing file: " << argv[4] << endl;
    exit(1);
  }	

  // Call Method 2 Function
  method2(inputImage, chromaMask);

  // Produce the output by calling replace()
  replace(chromaMask, inputImage, bgrndImage, outputImage);


  // Write the output image to a file using the filename argv[5]
  if (writeRGBBMP(argv[5], outputImage)) {
    cout << "Error writing file: " << argv[5] << endl;
    exit(1);
  }	

  return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE],
	     double threshold)
{
  // declaring and initializing variables for computing average
  // RGB values
  int redAvg = 0, greenAvg = 0, blueAvg = 0;

  // loop through top row of each plane (RGB)
  for(int i = 0; i < SIZE; i++){
    redAvg += inImage[0][i][0]; // adding each value to the variable to compute average later
    greenAvg += inImage[0][i][1];
    blueAvg += inImage[0][i][2];
  }

  // loop through left column of each plane (RGB)
  for(int i = 0; i < SIZE; i++){
    redAvg += inImage[i][0][0];
    greenAvg += inImage[i][0][1];
    blueAvg += inImage[i][0][2];
  }
  
  // calculating the average values for R,G,B of chromakey
  redAvg = (redAvg - inImage[0][0][0]) / (SIZE + SIZE - 1);
  greenAvg = (greenAvg - inImage[0][0][1]) / (SIZE + SIZE - 1);
  blueAvg = (blueAvg - inImage[0][0][2]) / (SIZE + SIZE - 1);

  // loop through entire image & compute distance for each
  // if distance of pixel from chromakey if <= threshold, then is part of background
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      
        double distance = sqrt(pow(redAvg - inImage[i][j][0], 2) + pow(greenAvg - inImage[i][j][1], 2) + pow(blueAvg - inImage[i][j][2], 2));
    
        if(distance <= threshold){
          mask[i][j] = 0;
        }
        else {
          mask[i][j] = 1;
        }
    }
  }

}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
  // declaring and initializing variables for calculating average RGB
  int redAvg = 0, greenAvg = 0, blueAvg = 0;
  int redMid = 0, greenMid = 0, blueMid = 0;
  int redInL = 0, greenInL = 0, blueInL = 0;
  int redInR = 0, greenInR = 0, blueInR = 0;
  double distanceP; // variable for holding distance of pixel from chromakey

  // loop through top row of each plane (RGB)
  for(int i = 0; i < SIZE; i++){
    // adding values to variable for calculating average RGB later on
    redAvg += inImage[0][i][0];
    greenAvg += inImage[0][i][1];
    blueAvg += inImage[0][i][2];
  }

  // loop through left column of each plane (RGB) 
  for(int i = 0; i < SIZE; i++){
    redAvg += inImage[i][0][0];
    greenAvg += inImage[i][0][1];
    blueAvg += inImage[i][0][2];
  }

  // loop through right column of each plane (RGB)
  for(int i = 0; i < SIZE; i++){
    redAvg += inImage[i][SIZE-1][0];
    greenAvg += inImage[i][SIZE-1][1];
    blueAvg += inImage[i][SIZE-1][2];
  }

  // calculating the average values for R,G,B of chromakey
  redAvg = (redAvg - inImage[0][0][0]) / (SIZE * 3 - 2);
  greenAvg = (greenAvg - inImage[0][0][1]) / (SIZE * 3 - 2);
  blueAvg = (blueAvg - inImage[0][0][2]) / (SIZE * 3 - 2);


  // look at 15 columns/rows in center
  for(int i = SIZE/2 - 7; i < SIZE/2 + 8; i++){
    for(int j = SIZE/2 - 7; j < SIZE/2 + 8; j++){
      redMid += inImage[i][j][0];
      greenMid += inImage[i][j][1];
      blueMid += inImage[i][j][2];
    }
  }

  // computing the average RGB for the middle 15 rows/columns of input image
  redMid = (redMid) / (225);
  greenMid = (greenMid) / (225);
  blueMid = (blueMid) / (225);

  // calculate distance between chromakey and average of middle pixels
  // center 15 rows/columns
  double distance = sqrt(pow(redAvg - redMid, 2) + pow(greenAvg - greenMid, 2) + pow(blueAvg - blueMid, 2));

  // check left and right
  // and find which distance is the farthest from the chromakey

  // check the left area of the picture
  for(int i = SIZE/4 - 7; i < SIZE/4 + 8; i++){
    for(int j = SIZE/4 - 7; j < SIZE/4 + 8; j++){
      redInL += inImage[i][j][0];
      greenInL += inImage[i][j][1];
      blueInL += inImage[i][j][2];
    }
  }

  // calculating average RGB values in left area of picture
  redInL = (redInL) / (225);
  greenInL = (greenInL) / (225);
  blueInL = (blueInL) / (225);
  // calculating average distance from left to chromakey
  double distanceL = sqrt(pow(redAvg - redInL, 2) + pow(greenAvg - greenInL, 2) + pow(blueAvg - blueInL, 2));

  // check the right middle area of the picture
  for(int i = 3*SIZE/4 - 7; i < 3*SIZE/4 + 8; i++){
    for(int j = 3*SIZE/4 - 7; j < 3*SIZE/4 + 8; j++){
      redInR += inImage[i][j][0];
      greenInR += inImage[i][j][1];
      blueInR += inImage[i][j][2];
    }
  }
  // calculating average distance from right to chromakey
  redInR = (redInR) / (225);
  greenInR = (greenInR) / (225);
  blueInR = (blueInR) / (225);
  // calculating average distance from right to chromakey
  double distanceR = sqrt(pow(redAvg - redInR, 2) + pow(greenAvg - greenInR, 2) + pow(blueAvg - blueInR, 2));

  // branching statements for finding which section (left, middle, or right)
  // has the furthest distance from the chromakey
  // and setting that value as the distance (threshold) value
  if(distanceL > distance){
    distance = distanceL;
  }
  if(distanceR > distance){
    distance = distanceR;
  }

  // iterate through every row and column of image and assign mask values
  // depending on the calculated distance
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      // computing distance of each pixel from the chromakey
      distanceP = sqrt(pow(redAvg - inImage[i][j][0], 2) + pow(greenAvg - inImage[i][j][1], 2) + pow(blueAvg - inImage[i][j][2], 2));
    
      if(distanceP <= distance - 35){ // assigning mask to 0 if lower than threshold
        mask[i][j] = 0;
      }
      else { // assigning mask to 1 if greater than threshold
        mask[i][j] = 1;
      }
    }
  }
}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB])
{
  // Create the output image using the mask to determine
  //  whether to use the pixel from the Input or Background image

  // in mask: 0 = false(background), 1 = true(foreground)

  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      for(int c = 0; c < RGB; c++){
        // assigning pixels of outImage to either bgImage or inImage
        // depending on value of pixel in the mask
        if (mask[i][j] == 0){
          outImage[i][j][c] = bgImage[i][j][c];
        }
        else if (mask[i][j] == 1){
          outImage[i][j][c] = inImage[i][j][c];
        }
      }
    }
  }

}
