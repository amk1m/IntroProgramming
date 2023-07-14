#include "digitblob.h"
#include <iostream>
// Add more includes if necessary
#include <vector>
#include <cmath>

using namespace std;

// TO DO - Complete this function
bool Location::operator<(const Location& other) const
{
    Location temp = *this;

    if(temp.col < other.col){
        return true;
    }
    else if(temp.col == other.col){
        if(temp.row < other.row){
            return true;
        }
        else{
            return false;
        }
    }
    return false;


}

// TO DO - Complete this function
DigitBlob::DigitBlob()
{
    img_ = NULL;
    digit_ = '!'; // dummy value
    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // ul_'s Location default constructor already initializes it to -1,-1

    // Initilaize h_ and w_ and any other data members
    h_ = 0;
    w_ = 0;


}

// TO DO - Complete this function
DigitBlob::DigitBlob(uint8_t** img, Location upperleft, int height, int width)
{
    img_ = img;
    digit_ = '!'; // dummy value

    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // Initilaize ul_, h_ and w_ and any other data members
    ul_ = upperleft;
    h_ = height;
    w_ = width;


}

// TO DO - Complete this function if necessary
DigitBlob::~DigitBlob()
{
    // Add code if it is necessary

}

// TO DO - Complete this function
void DigitBlob::classify()
{
    calc_bit_quads();
    calc_euler_number();
		// if euler_number = 1: 0 holes --> 1, 2, 3, 5, 7
		// if euler_number = 0: 1 hole --> 4, 6, 9, 0
		// if euler_number = -1: 2 holes --> 8

		// Call helper functions to calculate features
		calc_centers_of_mass();
		calc_symmetry();
		calc_thirds();
		calc_quadrants();

		if(euler_ == -1){ // 8
			digit_ = '8';
		}
		else if(euler_ == 1){ // 1, 2, 3, 5, 7
			if((symmetryVert / symmetryHoriz)> 1.2){
				digit_ = '3';
			}
			else if((abs(vertThird2 - vertThird3) < 0.03) && (horizThird1 < horizThird2)){
				digit_ = '7';
			}
			else if((quad1 / quad3 < 0.51) && (quad1 / quad3 > 0.4)){
				digit_ = '2';
			}
			else if((quad1 / quad3) > 1.45){
				digit_ = '5';
			}
			else{
				digit_ = '1';
			}

		}
		else if(euler_ == 0){ // 0, 4, 6, 9
			if(symmetryVert > 0.85 && symmetryHoriz > 0.85){
				digit_ = '0';
			}
			else if(((vertThird1 / vertThird3) > 0.52) && ((vertThird1 / vertThird3) < 0.79)){
				digit_ = '6';
			}
			else if((vertThird1 / vertThird3) > 1.3){
				digit_ = '9';
			}
			else{
				digit_ = '4';
			}

		}




    // TO DO: use the results of helper functions to calculate features
    //    We suggest starting with the Euler number but you are free to
    //    change our structure
		// printClassificationResults();



}

// Complete - Do not alter
char DigitBlob::getClassification() const
{
    return digit_;
}

// TO DO - Complete this function
void DigitBlob::printClassificationResults() const
{
    cout << "Digit blob at " << ul_.row << "," << ul_.col << " h=" << h_ << " w=" << w_ << endl;
    cout << "Bit quads: 1, 2, D, 3, 4:";
    cout << " " << bq1_ << " " << bq2_ << " " << bqd_;
    cout << " " << bq3_ << " " << bq4_ << endl;
    cout << "Euler number is " << euler_ << endl;
		cout << "Centers of mass- vertical: " << cmVert << " horizontal: " << cmHoriz << endl;
		cout << "Symmetry- vertical: " << symmetryVert << " horizontal: " << symmetryHoriz << endl;
		cout << "Vertical thirds: " << vertThird1 << " " << vertThird2 << " " << vertThird3 << endl;
		cout << "Horizontal thirds: " << horizThird1 << " " << horizThird2 << " " << horizThird3 << endl;
		cout << "Quadrants: " << quad1 << " " << quad2 << " " << quad3 << " " << quad4 << endl;
    // TO DO: Add any other couts to print classification test data





    cout << "****Classified as: " << digit_ << "\n\n" << endl;

}

// Complete - Do not alter
const Location& DigitBlob::getUpperLeft() const
{
    return ul_;
}

// Complete - Do not alter
int DigitBlob::getHeight() const
{
    return h_;
}

// Complete - Do not alter
int DigitBlob::getWidth() const
{
    return w_;
}

// Complete - Do not alter
bool DigitBlob::operator<(const DigitBlob& other)
{
    // Use Location's operator< for DigitBlob operator<
    return ul_ < other.ul_;
}

// Complete - Do not alter
void DigitBlob::calc_euler_number()
{
    euler_ = (bq1_ - bq3_ - 2*bqd_) / 4;
}

// TO DO - Complete this function to set bq1_, bq2_, etc.
void DigitBlob::calc_bit_quads()
{

	for(int i = ul_.row-1; i < ul_.row + h_; i++){
		for(int j = ul_.col-1; j < ul_.col + w_; j++){

			int countB = 0; // count number of black pixels

			if(img_[i][j] == 0){
				countB += 1;
			}
			if(img_[i+1][j] == 0){
				countB += 1;
			}
			if(img_[i][j+1] == 0){
				countB += 1;
			}
			if(img_[i+1][j+1] == 0){
				countB += 1;
			}

			if(countB == 0){
				bq0_ += 1;
			}
			else if(countB == 1){
				bq1_ += 1;
			}
			else if(countB == 2){
				if((img_[i][j] == 0 && img_[i+1][j+1] == 0) || (img_[i+1][j] == 0 && img_[i][j+1] == 0)){
					bqd_ += 1;
				}
				else{
					bq2_ += 1;
				}
			}
			else if(countB == 3){
				bq3_ += 1;
			}
			else if(countB == 4){
				bq4_ += 1;
			}
			
		}
	}


}

// Add more private helper function implementations below
void DigitBlob::calc_centers_of_mass(){

    double vertCM = 0;
    double horizCM = 0;
    int numBlackPixels = 0;

    // calculating centers of mass
    // go through digitblob image and do row index * 1 if the pixel is black
    for(int i = 0; i < h_; i++){
		for(int j = 0; j < w_; j++){
            if(img_[i+ul_.row][j+ul_.col] == 0){
                vertCM += i * 1;
                horizCM += j * 1;
                numBlackPixels += 1;
            }
        }
    }

    // actual centers of mass 
    vertCM = vertCM / numBlackPixels;
    horizCM = horizCM / numBlackPixels;

    // normalize the values:
    cmVert = (vertCM) / (h_);
    cmHoriz = (horizCM) / (w_);

}

void DigitBlob::calc_symmetry(){

	// vertical: split image in half - go through first half of rows and compare to other half
	int pixelCount = 0;
	int symmVCount = 0;
	int symmHCount = 0;

	// vertical symmetry:
	for(int i = ul_.row; i < ul_.row+h_/2; i++){
		for(int j = ul_.col; j < ul_.col+w_; j++){
			if(img_[i][j] == img_[ul_.row + ul_.row+h_-1-i][j]){
				symmVCount += 1;
			}
			pixelCount += 1;
		}
	}
	symmetryVert = (static_cast<double>(symmVCount)) / pixelCount;

	// horiz symmetry:
	pixelCount = 0;
	for(int i = ul_.row; i < ul_.row + h_; i++){
		for(int j = ul_.col; j < ul_.col+w_/2; j++){
			if(img_[i][j] == img_[i][ul_.col + ul_.col+w_-1-j]){
				symmHCount += 1;
			}
			pixelCount += 1;
		}
	}
	symmetryHoriz = (static_cast<double>(symmHCount)) / pixelCount;


}

void DigitBlob::calc_thirds(){
	// calculate proportion of black pixels to total in each third

	int blackPixelCount = 0;
	int totalPixelCount = 0;

	// vertically: rows / 3
	// first third
	for(int i = ul_.row; i < ul_.row + (h_/3); i++){
		for(int j = ul_.col; j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	vertThird1 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// second third
	for(int i = ul_.row + (h_/3); i < ul_.row + 2*(h_/3); i++){
		for(int j = ul_.col; j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	vertThird2 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// 3rd third
	for(int i = ul_.row + 2*(h_/3); i < ul_.row + h_; i++){
		for(int j = ul_.col; j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	vertThird3 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// calculating horizontal calc_thirds
	// horizontally: cols / 3

	// horizThird1
	for(int i = ul_.row; i < ul_.row + h_; i++){
		for(int j = ul_.col; j < ul_.col + (w_/3); j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	horizThird1 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// second horizontal third
	for(int i = ul_.row; i < ul_.row + h_; i++){
		for(int j = ul_.col + (w_/3); j < ul_.col + 2*(w_/3); j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	horizThird2 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// last horizontal third
	for(int i = ul_.row; i < ul_.row + h_; i++){
		for(int j = ul_.col + 2*(w_/3); j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	horizThird3 = (static_cast<double>(blackPixelCount)) / totalPixelCount;


}


void DigitBlob::calc_quadrants(){

	int blackPixelCount = 0;
	int totalPixelCount = 0;

	// quadrant 1 (upper left)
	for(int i = ul_.row; i < ul_.row + (h_/2); i++){
		for(int j = ul_.col; j < ul_.col + (w_/2); j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	quad1 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// quadrant 2 (upper right)
	for(int i = ul_.row; i < ul_.row + (h_/2); i++){
		for(int j = ul_.col + (w_/2); j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	quad2 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// quadrant 3 (bottom left)
	for(int i = ul_.row + (h_/2); i < ul_.row + h_; i++){
		for(int j = ul_.col; j < ul_.col + (w_/2); j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	quad3 = (static_cast<double>(blackPixelCount)) / totalPixelCount;

	blackPixelCount = 0;
	totalPixelCount = 0;

	// quadrant 4 (bottom right)
	for(int i = ul_.row + (h_/2); i < ul_.row + h_; i++){
		for(int j = ul_.col + (w_/2); j < ul_.col + w_; j++){
			if(img_[i][j] == 0){
				blackPixelCount += 1;
			}
			totalPixelCount += 1;
		}
	}
	quad4 = (static_cast<double>(blackPixelCount)) / totalPixelCount;


}



