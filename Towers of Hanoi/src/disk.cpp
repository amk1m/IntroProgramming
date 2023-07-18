// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "disk.h"

// default constructor
Disk::Disk()
{
    mX = 0;
    mY = 0;
    mW = 0;
    mH = 0;
    mColor = "";
}

// parameterized constructor
Disk::Disk(int x, int y, int width, int height)
{
    mX = x;
    mY = y;
    mW = width;
    mH = height;
    mColor = "BLUE";
}

// draw function
void Disk::draw(GWindow& gw)
{
    gw.setColor(mColor);
    gw.fillRect(mX - mW/2, mY - mH, mW, mH); // CHANGED
}

// setting x coordinate
void Disk::setX(int x)
{
    mX = x;
}

// setting y coordinate
void Disk::setY(int y)
{
    mY = y;
}

// getting height
int Disk::getHeight()
{
    return mH;
}

// setting width
void Disk::setWidth(int w)
{
    mW = w;
}




