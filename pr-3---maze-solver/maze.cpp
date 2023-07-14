/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use
int checkInvalidMaze(char**, int, int); // prototype for function that checks if maze is valid


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    int checking; // variable to hold return value of checkInvalidMaze function
    const char* invalid_char_message = "Error, input format incorrect.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    // checking that a maze input file is provided
    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }
    
    // reading in the maze
    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.
    if(mymaze == NULL){
      cout << invalid_char_message;
      return 0;
    }

    // checking if maze is valid
    checking = checkInvalidMaze(mymaze, rows, cols);

    // if checking is 0, means that there is an invalid character in the maze
    if(checking == 0){
      cout << "Error, invalid character." << endl;
      // deallocating the memory of array
      for(int i = 0; i < rows; i++){
          delete [] mymaze[i];
      }
      delete [] mymaze;
      return 0;
    }

    // if checking is 1, means the maze is invalid
    if(checking == 1){
      cout << invalid_maze_message;
      return 0;
    }

    if(checking == 3){
      print_maze(mymaze, rows, cols);
      return 0;
    }
    

    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    
    // calling maze search and storing the value in result
    result = maze_search(mymaze, rows, cols);
    
    // if a path was found, maze is printed
    if(result == 1){
      print_maze(mymaze, rows, cols);  
    }

    else{ // no path message is outputted if no path was found
      cout << no_path_message;
    }
    
    
    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    for(int i = 0; i < rows; i++){
        delete [] mymaze[i];
    }
    delete [] mymaze;


    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4

    // checking that maze is valid
    int checker;
    checker = checkInvalidMaze(maze, rows, cols);
    if(checker != 2){
      return -1;
    }
    
    // declaring Queue
    Queue q(rows * cols);
    
    // dynamically allocate predecessor and explored arrays

    // 2D array for predecessor is an array of Locations
    // dynamically allocating memory for predecessor array
    Location** predecessor = new Location*[rows];
    for(int i = 0; i < rows; i++){
      Location* c = new Location[cols];
      predecessor[i] = c;
    }
    
    // initializing values of predecessor array (first all Locations hvae rows and cols of -1)
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        predecessor[i][j].row = -1;
        predecessor[i][j].col = -1;
      }
    }
  
    // 2D array for explored is an array of integers
    // dynamically allocating memory for explored array
    int** explored = new int*[rows];
    for(int i = 0; i < rows; i++){
      int* c = new int[cols];
      explored[i] = c;
    }
    
    // initializing explored array (all values are initialized to 0)
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        explored[i][j] = 0;
      }
    }
    
    // find S in maze
    Location start; // Location to represent the coordinates of the start
    // iterating through the maze to find row and col of S
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        if(maze[i][j] == 'S'){
          start.row = i;
          start.col = j;
        }
      }
    }

    // start is marked as explored and addded to Queue q
    explored[start.row][start.col] = 1;
    q.add_to_back(start);
    Location current; // Location to represent the current Location
    
    // loop that runs while the queue still has values
    while(!q.is_empty()){

      current = q.remove_from_front(); // getting current Location by removing front value from q

      // exploring all Locations north, west, south, and east of each Location in the queue
        
      // checking north of current (1 row above current, so row-1)
      if(current.row - 1 > -1){ // making sure that north Location is valid
        if((maze[current.row - 1][current.col] == '.') && (explored[current.row - 1][current.col] == 0)){
          Location tempN; // temp Location to represent Location above current
          tempN.row = current.row - 1;
          tempN.col = current.col;
          explored[current.row - 1][current.col] = 1; // marking north as explored
          q.add_to_back(tempN); // adding north Location to q
          predecessor[current.row-1][current.col] = current; // changing value in predecessor array
        }
      }

      // checking west of current (1 col to the left of current, so col-1)
      if(current.col - 1 > -1){ // making sure that west Location is valid
        if((current.col - 1 > -1) && (maze[current.row][current.col-1] == '.') && (explored[current.row][current.col-1] == 0)){
          Location tempW; // Location representing west of current
          tempW.row = current.row;
          tempW.col = current.col - 1;
          explored[current.row][current.col - 1] = 1; // marking west as explored
          q.add_to_back(tempW); // adding west Location to q
          predecessor[current.row][current.col - 1] = current; // changing value in predecessor     
        }
      }

      // checking south of current (1 row below current, so row+1)
      if(current.row + 1 < rows){ // making sure that south Location is valid
        if((current.row + 1 < rows) && (maze[current.row+1][current.col] == '.') && (explored[current.row+1][current.col] == 0)){
          Location tempS; // Location representing south of current
          tempS.row = current.row + 1;
          tempS.col = current.col;
          explored[current.row + 1][current.col] = 1; // marking south as explored
          q.add_to_back(tempS); // adding south Location to q
          predecessor[current.row+1][current.col] = current; // changing value in predecessor          
        }
      }

      // checking east of current (1 row to the right of current, so col+1)
      if(current.col + 1 < cols){ // making sure that east Location is valid
        if((current.col + 1 < cols) && (maze[current.row][current.col + 1] == '.') && (explored[current.row][current.col+1] == 0)){
          Location tempE;
          tempE.row = current.row;
          tempE.col = current.col + 1;
          explored[current.row][current.col + 1] = 1; // marking east as explored
          q.add_to_back(tempE); // adding east Location to q
          predecessor[current.row][current.col + 1] = current; // changing value in predecessor      
        }
      }
    }
    
    // deallocating memory for the explored array
    for(int i = 0; i < rows; i++){
        delete [] explored[i];
    }
    delete [] explored;

    // finding Location that is next to F
    while(!(((current.row - 1 > -1) && (maze[current.row-1][current.col] == 'F')) || ((current.row + 1 < rows) && (maze[current.row+1][current.col] == 'F')) || ((current.col - 1 > -1) && (maze[current.row][current.col - 1] == 'F')) || ((current.col + 1 < cols) && (maze[current.row][current.col + 1] == 'F')))){ 
      
      // setting current Location to the Location that precedes it (in predecessor array)
      current = predecessor[current.row][current.col];

      // if the start Location is reached and still has not found a Location that is next to F,
      // then it means that there is no valid path
      if((current.row == start.row) && (current.col == start.col)){
        
        // deallocating memory for predecessor array if no valid path
        for(int i = 0; i < rows; i++){
          delete [] predecessor[i];
        }
        delete [] predecessor;

          return 2; // returning value to show that no valid path was found
      }
    }
      
    Location temp; // declaring Location to hold temporary Location
    // initializing temporary Location to current
    temp.row = current.row;
    temp.col = current.col;

    // tracing back the path (using predecessor)
    // and replacing the path with *
    while(!((current.row == start.row) && (current.col == start.col))){
        
      // setting current Location to the temp
      current.row = temp.row;
      current.col = temp.col;   
      
      // checking that current Location is not S
      if(maze[current.row][current.col] != 'S'){
        maze[current.row][current.col] = '*'; // changing . to * if part of path
      }
        
      // putting preceding value of current into temp
      temp = predecessor[current.row][current.col];
      continue;

    }

    // deallocating memory for predecessor array if there is valid path found
    for(int i = 0; i < rows; i++){
        delete [] predecessor[i];
      }
    delete [] predecessor;
    return 1; // returning value to indicate that valid path was found

}

// defining function to check if maze is valid
int checkInvalidMaze(char** maze, int r, int c){
  char check; // char to each value in maze
  int s = 0; // indicates if S is in maze
  int f = 0; // indicates if F is in maze

  int sRow, sCol;
  int fRow, fCol;

  // iterate through maze
  for(int i = 0; i < r; i++){
    for(int j = 0; j < c; j++){

      check = maze[i][j]; // assigning check char to current value in maze

      // branching statements to track number of S, F
      if(check == 'S'){
        s += 1;
        sRow = i;
        sCol = j;
      }
      if(check == 'F'){
        f += 1;
        fRow = i;
        fCol = j;
      }

      // checking if character is valid (S, F, . or #)
      if((check != 'S') && (check != 'F') && (check != '.') && (check != '#')){
        return 0; // returning 0 if there is an invalid character in maze
      }
    }
  }

  if((s != 1) || (f != 1)){ // if number of S's and F's is not equal to 1, maze is not valid
    return 1; // returning value to indicate that maze is not valid
  } 

  // check if S and F are right next to each other
  else if(((sRow == fRow) && ((sCol - fCol == 1) || (sCol - fCol == -1))) || ((sCol == fCol) && ((sRow - fRow == 1) || (sRow - fRow == -1)))){
    return 3;
  }
  
  else{
    return 2; // returning value to indicate that maze is valid
  }

}
