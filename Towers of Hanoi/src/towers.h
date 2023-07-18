// �2023 Nathan Greenfield

// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac
#pragma once

#include "disk.h"
#include "peg.h"
#include "gwindow.h"

#include <vector>

// Name:
//      promptForDisks
// Input:
//      None
// Output:
//      Prints out a message asking the user to enter the number of disks.
//      Returns the int that the user inputted (given that the inputted value is between 2 and 10)
// Side effects:
//      Gets input from user
// Summary:
//      Prompts the user for the number of disks
//
int promptForDisks();

// Name:
//      promptForPegs
// Input:
//      integer representing the starting peg and integer represetning the ending peg
// Output:
//      None
// Side effects:
//      Prompts the user for the two integers
// Summary:
//      It asks the user to input the start and ending integers that represent the starting and ending peg
//
void promptForPegs(int& start, int& end);

// Name:
//      promptForPause
// Input:
//      None
// Output:
//      Returns the integer the user inputted that represents the number of milliseconds (has to be between the range)
// Side effects:
//
// Summary:
//      Prompts the user to input an integer that represents the number of milliseconds to pause for
//
int promptForPause();

// Name:
//      promptForWindowSize
// Input:
//      2 ints representing the width and the height
// Output:
//      None
// Side effects:
//      Gets input from user
// Summary:
//      Prompts the user for input - asks for an integer representing the width and height of the window, and keeps asking for input unless the numbers inputted are valid
//
void promptForWindowSize(int& width, int& height);

// Name:
//      draw
// Input:
//      GWindow object, a vector (passed by reference), and an int representing the number of milliseconds
// Output:
//      No return value
// Side effects:
//      Draws the 3 pegs and the disks
// Summary:
//      This function draws the 3 pegs and the disks on the starting peg
//
void draw(GWindow& gw, std::vector<Peg>& vecPegs, int ms);

// Name:
//      moveDisk
// Input:
//      GWindow object, a vector (passed by reference), and 3 integers representing the start peg, destination peg, and the number of milliseconds to pause for
// Output:
//      No return value
// Side effects:
//
// Summary:
//      This function adds the disk to the destination peg and removes that disk from the start peg
//
void moveDisk(GWindow& gw, std::vector<Peg>& vecPegs, int start, int dest, int ms);

// Name:
//      towerSolve
// Input:
//      GWindow object, vector of pegs (passed by reference), and 4 integers representing the start peg, destination peg, number of idsks, and the number of milliseconds to pause for
// Output:
//      No return value
// Side effects:
//
// Summary:
//      This function is recursive and has the algorithm for solving the tower.
//
void towerSolve(GWindow& gw, std::vector<Peg>& vecPegs, int start, int dest, int numDisks, int ms);

// Name:
//      towerRun
// Input:
//      None
// Output:
//      Returns 0 if successful
// Side effects:
//      Calls the required functions to solve the tower and output the drawings
// Summary:
//      This function calls the required functions to solve the tower, including the solve algorithm, moving the disks, and all the drawing functions
//
int towerRun();

// constant values for valid inputs from user
const int MINSCREENWIDTH = 800;
const int MINSCREENHEIGHT = 600;
const int MAXSCREENWIDTH = 4096;
const int MAXSCREENHEIGHT = 2160;
const int MINDISKS = 2;
const int MAXDISKS = 10;
const int NUMPEGS = 3;
const int MAXPAUSELEN = 1000000;
