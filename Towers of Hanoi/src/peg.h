// �2023 Nathan Greenfield

// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#pragma once

#include <string>

#include <vector>
#include "gwindow.h"

#include "disk.h"

class Peg
{
public:
    // Name:
    //        Peg default constructor
    // Input:
    //        None
    // Output:
    //        None
    // Side effects:
    //        Sets private member variables to default values.
    // Summary:
    //        Constructor (default)
    //
	Peg();
    
    // Name:
    //        Peg default constructor
    // Input:
    //        4 integers representing x coordinate (of bottom center), y coordinate (of bottom center), width, and height
    // Output:
    //        None
    // Side effects:
    //        Sets private member variables to the parameters.
    // Summary:
    //        Constructor (parameterized)
    //
	Peg(int x, int y, int width, int height);

    // Name:
    //        draw
    // Input:
    //        GWindow object (passed by reference)
    // Output:
    //        Drawing of the peg and the disks on that peg
    // Side effects:
    //        Draws the peg and the disks on that peg by calling the draw functions for disks
    // Summary:
    //        Draw function for peg
    //
	void draw(GWindow& gw);
    
    // Name:
    //        addDisk
    // Input:
    //        Disk object (to add)
    // Output:
    //        None
    // Side effects:
    //        Adds a disk to the vector corresponding to that peg;
    // Summary:
    //        Adds a disk to the vector for that peg
    //
	void addDisk(Disk toAdd);
    
    // Name:
    //        removeDisk
    // Input:
    //        None
    // Output:
    //        Returns the Disk that is being removed
    // Side effects:
    //        Removes last element of the vector
    // Summary:
    //        Removes the last disk on that peg (last element of vector) and returns it
    //
	Disk removeDisk();
private:
	int mX; // x coordinate of bottom center
	int mY; // y coordinate of bottom center
	int mW;
	int mH;
	//int xCenter;
	int curTop; // represents y coordinate of current disk

	std::string color;

	std::vector<Disk> diskVect; // disk at index 0 is at the bottom of the peg
};
