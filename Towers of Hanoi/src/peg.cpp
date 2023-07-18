// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "peg.h"

// default constructor
Peg::Peg()
{
    // setting x, y, width and height to 0
    mX = 0;
    mY = 0;
    mW = 0;
    mH = 0;
    curTop = 0;
    color = "BLACK";
    diskVect.clear(); // clearing the disk vector
}

// parameterized constructor
Peg::Peg(int x, int y, int width, int height)
{
    mX = x;
    mY = y;
    mW = width;
    mH = height;
    curTop = mH; // represents current height of the current disk (used in draw function)
    color = "BLACK";
    diskVect.clear(); // clearing the disk vector
}

// draw function
void Peg::draw(GWindow& gw)
{
    // first draw the peg
    gw.setColor(color); // setting the color
    gw.fillRect(mX - mW / 2, mY - mH, mW, mH); // calling fill rect to draw the peg
    
    // call draw functions for each disk in vector
    // loop through the diskVect to draw each disk on the peg
    for(size_t i = 0; i < diskVect.size(); i++){
        diskVect[i].draw(gw);
    }
}

// add disk function
void Peg::addDisk(Disk toAdd)
{
    size_t numDisks = diskVect.size(); // getting number of disks on the peg
    int diskHeight = toAdd.getHeight(); // getting the height of the disk
    
    // setting the x and y coordinates for the disk that is to be added
    toAdd.setX(mX); // setting the x coordinate of the disk to the same x coordinate of the peg
    // setting the y coordinate of the disk
    toAdd.setY(mY - (numDisks * diskHeight));
    
    // adding the disk to the diskVect vector
    diskVect.push_back(toAdd);
    
}

// remove disk function
Disk Peg::removeDisk()
{
    size_t numDisks = diskVect.size(); // getting number of disks on the peg
    Disk toRemove = diskVect[numDisks - 1]; // getting the last disk on the peg (to be removed)
    diskVect.pop_back(); // getting rid of the last disk in the vector
    return toRemove; // returning the disk that was just removed
}

