// ITP 365 Spring 2023
// HW04 – Towers of Hanoi
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "towers.h"

// promptForDisks function
int promptForDisks()
{
    int input; // int variable for getting input from user
    std::cout << "Enter number of disks (2-10): "; // prompt
    std::cin >> input;
    std::cout << std::endl;
    
    // checking the user's input; while loop keeps running while the input is invalid
    while((input < MINDISKS) || (input > MAXDISKS)){
        std::cout << "Enter number of disks (2-10): ";
        std::cin >> input;
        std::cout << std::endl;
    }
    
    return input;
}

// prompting the user for pegs
void promptForPegs(int& start, int& end)
{
    std::cout << "Enter the starting peg and ending peg (1-3): "; // prompt
    std::cin >> start >> end;
    std::cout << std::endl;
    
    // checking the user's input; while loop keeps running while the input is invalid
    while((start == end) || (start < 1) || (end < 1) || (start > NUMPEGS) || (end > NUMPEGS)){
        std::cout << "Enter the starting peg and ending peg (1-3): ";
        std::cin >> start >> end;
        std::cout << std::endl;
    }
    
    // decrementing the start and end int variables in order to get the indices of the corresponding pegs in the vector of pegs
    start -= 1;
    end -= 1;
}

// prompting the user for pause (number of milliseconds)
int promptForPause()
{
    int input; // int variable for getting input from user
    std::cout << "Enter number of milliseconds (1-1000000): "; // prompt
    std::cin >> input;
    std::cout << std::endl;
    
    // checking the user's input; while loop keeps running while the input is invalid
    while(input < 1 || input > MAXPAUSELEN){
        std::cout << "Enter number of milliseconds (1-1000000): ";
        std::cin >> input;
        std::cout << std::endl;
    }
    
    return input;
}

// prompting the user for size of the window
void promptForWindowSize(int& width, int& height)
{
    std::cout << "Enter a width and height: "; // prompt
    std::cin >> width >> height;
    std::cout << std::endl;
    
    // checking the user's input; while loop keeps running while the input is invalid
    while((width < MINSCREENWIDTH) || (width > MAXSCREENWIDTH) || (height < MINSCREENHEIGHT) || (height > MAXSCREENHEIGHT)){
        std::cout << "Enter a width and height: ";
        std::cin >> width >> height;
        std::cout << std::endl;
    }
}

// drawing the pegs and the disks
void draw(GWindow& gw, std::vector<Peg>& vecPegs, int ms)
{
    gw.clear(); // clearing gw
    
    // for each peg in the vector, the peg and its disks are drawn (by calling the draw function)
    for(size_t i = 0; i < vecPegs.size(); i++){
        vecPegs[i].draw(gw);
    }
    
    pause(ms);
}

// move disk function
void moveDisk(GWindow& gw, std::vector<Peg>& vecPegs, int start, int dest, int ms)
{
    // getting the disk that is to be moved by removing it from the starting peg
    Disk moving = vecPegs[start].removeDisk();

    // the disk removed from the start peg is being added to the destination peg
    vecPegs[dest].addDisk(moving);
    
    // the draw function is called for the pegs
    draw(gw, vecPegs, ms);
    
}

// towerSolve function
void towerSolve(GWindow& gw, std::vector<Peg>& vecPegs, int start, int dest, int numDisks, int ms)
{

    // base case
    if(numDisks == 0){
        return; // if the number of disks is 0, return
    }
    
    // finding the temp peg (the one that is neither the start nor the dest peg)
    int temp = 3 - (start + dest);
    
    // calling the towerSolve function for numDisks - 1, from start to temp peg
    towerSolve(gw, vecPegs, start, temp, numDisks - 1, ms);
    
    // moving the disk from start to destination peg
    moveDisk(gw, vecPegs, start, dest, ms);
    
    // calling the towerSolve function for numDisks - 1, from temp to dest peg
    towerSolve(gw, vecPegs, temp, dest, numDisks - 1, ms);
    
}

// tower run function
int towerRun()
{
    
    // declaring the variables for getting input from user
    int numDisks;
    int start;
    int end;
    int msPause;
    int windowW;
    int windowH;
    
    // call all prompts
    numDisks = promptForDisks();
    promptForPegs(start, end);
    msPause = promptForPause();
    promptForWindowSize(windowW, windowH);
    
    // declaring gw and vector
    GWindow gw(windowW, windowH);
    std::vector<Peg> vectorPegs;
    
    // make the three peg objects and add to vector (depending on the input)
    // set peg height to the window height
    // set the x coordinate of peg depending on window width (divide the window into fourths)
    // using the peg parameterized constructor to create the 3 pegs
    Peg p1 = Peg(windowW / 4, windowH, windowW / 100, windowH);
    Peg p2 = Peg(windowW / 2, windowH, windowW / 100, windowH);
    Peg p3 = Peg((windowW * 3) / 4, windowH, windowW / 100, windowH);
    
    // add the pegs to the vector
    vectorPegs.push_back(p1); // index 0
    vectorPegs.push_back(p2); // index 1
    vectorPegs.push_back(p3); // index 2
    
    // make the disk objects (according the number of disks inputted) and add them to the disk vector for the start peg
    int diffWidth = 0; // changing this variable for each disk that is drawn on the peg
    
    // adding each of the disks to the start peg
    for(size_t i = 0; i < numDisks; i++){
        // creating a temporary Disk object that represents the current Disk that is being added to the peg
        Disk temp = Disk(windowW, windowH, windowW / 4.5 - diffWidth, windowH / (numDisks + 1));
        vectorPegs[start].addDisk(temp); // adding the disk to the start peg
        diffWidth += (windowW / 45); // changing the value to decrease the width for each of the next disks that need to be added
    }
    
    // calling the draw function
    draw(gw, vectorPegs, msPause);
    
    // calling tower solve function
    towerSolve(gw, vectorPegs, start, end, numDisks, msPause);
    
    pause(msPause); // pause
    
    return 0;
}


