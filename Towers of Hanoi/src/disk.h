// �2023 Nathan Greenfield

// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#pragma once

#include <iostream>
#include <string>
#include "gwindow.h"

class Disk
{
public:
    // Name:
    //        Disk default constructor
    // Input:
    //        None
    // Output:
    //        None
    // Side effects:
    //        Sets private member variables to default values.
    // Summary:
    //        Constructor (default)
    //
	Disk();
    
    // Name:
    //        Disk parameterized constructor
    // Input:
    //        Numbers for x coordinate, y coordinate, width, and height.
    // Output:
    //        None
    // Side effects:
    //        Sets the private member variables to values according to the inputted values
    // Summary:
    //        Constructor (parameterized)
	Disk(int x, int y, int width, int height);

    // Name:
    //        draw
    // Input:
    //        GWindow object (passed by reference)
    // Output:
    //        Drawing of the disk
    // Side effects:
    //        Draws the rectangles
    // Summary:
    //        Uses GWindow and member variables to create the colored rectangles that represent the disks
	void draw(GWindow& gw);

    // Name:
    //        setX
    // Input:
    //        integer that the X coordinate should be set to
    // Output:
    //        None
    // Side effects:
    //        Sets mX to the integer given in the function parameter
    // Summary:
    //        Setter function for x coordinate (bottom center of Disk)
	void setX(int x);
    
    // Name:
    //        setY
    // Input:
    //        integer that the Y coordinate should be set to
    // Output:
    //        None
    // Side effects:
    //        Sets mX to the integer given in the function parameter
    // Summary:
    //        Setter function for y coordinate (bottom center of Disk)
	void setY(int y);
    
    // Name:
    //        setWidth
    // Input:
    //        integer that the width should be set to
    // Output:
    //        None
    // Side effects:
    //        Sets mW to the integer given in the function parameter
    // Summary:
    //        Setter function for width of Disk
    void setWidth(int w);

    // Name:
    //        getHeight
    // Input:
    //        None
    // Output:
    //        Returns the height of Disk object (mH)
    // Side effects:
    //        None
    // Summary:
    //        Getter function for mH (height of Disk)
	int getHeight();

private:
	int mX; // x coordinates (bottom center)
	int mY; // y coordinates (bottom center)
	int mW; // width
	int mH; // height
	std::string mColor; // string representing color
};
