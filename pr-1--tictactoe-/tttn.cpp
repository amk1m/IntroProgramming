// NxN tic-tac-toes
#include <iostream>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to 
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);


/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);


/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);



/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);


/** 
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 * 
 */
int checkForWinner(char grid[], int dim);


/** 
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 * 
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current 
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);
 

/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

// implementations for each function
char getEntryAtRC(char grid[], int dim, int r, int c){
  return grid[dim * r + c];
}

int idxToRow(int idx, int dim){
  return idx / dim;
}

int idxToCol(int idx, int dim){
  return idx % dim;
}

void printTTT(char grid[], int dim){
  for(int i = 0; i < dim; i++){ // iterating through each row
    cout << " ";

    for(int j = 0; j < dim; j++){ // each column (per row)
      cout << grid[j + dim*i]; // outputting the char
      if((j+1) % dim != 0){
        cout << " | "; // separates each character
      }
      else{
        cout << endl; // next line
      }
    }

    if(i < dim-1){ // outputting the dashes after each row
      for(int k = 0; k < (3*dim+dim-1); k++){
        cout << "-";
      }
      cout << endl;
    }
  }
}


// function checkForWinner
// returns 1 if X wins, 2 if O wins, 0 if no winner yet
int checkForWinner(char grid[], int dim){
  // loop through each row and see if any row has all X or all O
  char rTemp; // variable temporarily holding first char of each row
  char cTemp; // variable temporarily holding first char of each column
  char current; // variable temporarily holding current value of array

  // checking rows
  for(int i = 0; i< dim; i++){ // each row
    for(int j = 0; j < dim; j++){ // each column of each row
      current = getEntryAtRC(grid, dim, i, j); // value at current index
      if(j == 0){
        rTemp = current; // setting first value of row to rTemp
      }
      if((current != rTemp) || (rTemp == '?')){
        break; // exit loop if not same chars or if blank spaces
      }
      if(j == dim-1){ // last element of each row
        if(rTemp == 'X'){
          return 1;
        }
        else if(rTemp == 'O'){
          return 2;
        }
        else{
          break; // exit loop
        }
      }
    }
  }

  // check columns
  for(int i = 0; i < dim; i++){ // go thru each column 
    for(int j = 0; j < dim; j++){ // each row of each column
      current = getEntryAtRC(grid, dim, j, i);
      if(j == 0){
        cTemp = current; // setting first value of column to cTemp
      }
      if((current != rTemp) || (rTemp == '?')){
        break; // exit loop if not all same char in column or if blank space
      }
      if(j == dim-1){
        if(cTemp == 'X'){
          return 1; // X wins
        }
        else if(cTemp == 'O'){
          return 2; // O wins
        }
        else{
          break; // exit loop
        }
      }
    }
  }

  // check both diagonals
  // checking 1st diagonal (from left to right)
  int index1 = 0; // indices representing which ones in grid are part of diagonal
  while(index1 < dim*dim){ // checking each value of first diagonal
    if(grid[index1] != 'O' && grid[index1] != 'X'){
      break; // exit loop if blank space
    }
    if(grid[0] != grid[index1]){
      break; // comparing first value of diagonal to each subsequent value (incremented)
    }
    if(index1 == dim*dim-1){ // last value of the diagonal
      if(grid[index1] == grid[0]){
        if(grid[0] == 'X'){
          return 1;
        }
        else if (grid[0] == 'O'){
          return 2;
        }
      }
    }
    index1 = index1 + dim + 1; // incrementing each index to get index of next value of diagonal
  }

  // checking 2nd diagonal (from right to left)
  int index2 = dim - 1; // indices representing which in grid are part of diagonal
  while(index2 <= dim*dim-dim){ // checking values of 2nd diagonal
    if(grid[index2] != 'O' && grid[index2] != 'X'){
      break; // exit loop if blank space
    }
    if(grid[dim-1] != grid[index2]){
      break; // exit loop if current value is not the same as the first value of diagonal
    }
    if(index2 == dim*dim-dim){ // checking the last value of 2nd diagonal
      if(grid[index2] == grid[dim-1]){
        if(grid[dim-1] == 'X'){
          return 1;
        }
        else if (grid[dim-1] == 'O'){
          return 2;
        }
      }
    }
    index2 = index2 + dim - 1; // incrementing the index for the diagonal
  }

  // return 0 if no winner yet
  return 0; 

}

// return true if there is a draw
bool checkForDraw(char grid[], int dim){
  char current; // variable for holding current char
  int x, o = 0; // variable to determine whether at least 1 x and o are present
  
  // declaring array variables for row, column, 1st diagonal and 2nd diagonal
  char row[dim]; 
  char col[dim]; 
  char diag1[dim];
  char diag2[dim];

  // check each row
  for(int i = 0; i< dim; i++){ 
    x = 0;
    o = 0;
    for(int j = 0; j < dim; j++){ // each column of each row
      current = getEntryAtRC(grid, dim, i, j);
      // add values to row[]
      row[j] = current; // adding values of row to array
    }
  
  for(int k = 0; k < dim; k++){ // loop through array to look for X's and O's
    if(row[k] == 'X'){
      x = 1;
    }
    if(row[k] == 'O'){
      o = 1;
    }
    if(k == dim - 1){
      if(x != 1 || o != 1){
        return false; // return false if there is not at least 1 X and at least 1 O
      }
    }    
  }
  }

  // check each column
  for(int i = 0; i < dim; i++){ // go through each column
    x = 0;
    o = 0;
    for(int j = 0; j < dim; j++){ // each row of each column
      current = getEntryAtRC(grid, dim, j, i);
      col[j] = current; // adding column values to the array
    }
  
  for(int k = 0; k < dim; k++){ // checking values of the array
    if(col[k] == 'X'){
      x = 1;
    }
    if(col[k] == 'O'){
      o = 1;
    }
    if(k == dim - 1){
      if(x != 1 || o != 1){
        return false; // if not at least 1 X and 1 O in array
      }
    }
  }
  }

  // check first diagonal
  int index1 = 0;// indices of new array that has diagonal values being added
  x = 0;
  o = 0;
  int indG = 0; // index of grid that corresponds to first diagonal values
  
  while(indG < dim*dim){ // adding values to diag1 array
    diag1[index1] = grid[indG];
    indG = indG + dim + 1;
    index1 = index1 + 1;
  }
  for(int k = 0; k < dim; k++){ // looping through diag1 array to check X's and O's
      if(diag1[k] == 'X'){
        x = 1;
      }
      if(diag1[k] == 'O'){
        o = 1;
      }
      if(k == dim - 1){
        if(x != 1 || o != 1){
          return false; // if not at least 1 X and 1 O in the diagonal
        }
      }
    }

  // checking 2nd diagonal (from right to left)
  int index2 = 0; // indices of new array that has diagonal values being added
  x = 0;
  o = 0;
  int indH = dim - 1; // index of grid that corresponds to 2nd diagonal values

  while(indH < dim*dim-dim+1){ // adding 2nd diagonal values to diag2 array
    diag2[index2] = grid[indH];
    indH = indH + dim - 1;
    index2 = index2 + 1;
  }
  for(int k = 0; k < dim; k++){ // looping through array to find X's and O's
      if(diag2[k] == 'X'){
        x = 1;
      }
      if(diag2[k] == 'O'){
        o = 1;
      }
      if(k == dim*dim-dim){
        if(x != 1 || o != 1){
          return false; // if not at least 1 X and 1 O
        }
      }
  }

  // if no value has been returned yet, this means there is a draw
  return true;

}



/**********************************************************
 *  Complete the indicated parts of main(), below. 
 **********************************************************/
int main()
{
  // This array holds the actual board/grid of X and Os. It is sized 
  // for the biggest possible case (11x11), but you should only 
  // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
  char tttdata[121];
    
  // dim stands for dimension and is the side length of the 
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5). 
  int dim;
  // Get the dimension from the user
  cin >> dim;
    
  int dim_sq = dim*dim;

  for(int i=0; i < dim_sq; i++){
    tttdata[i] = '?';
  }

  // Print one of these messages when the game is over
  // and before you quit
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] =  "Draw...game over!";
  
  bool done = false;
  char player = 'X';
  // Show the initial starting board
  printTTT(tttdata, dim);

  while(!done){ // while loop that runs until the game is over

    //**********************************************************
    // Get the current player's input (i.e. the location they want to
    // choose to place their mark [X or O]) and update the tttdata array.
    // Be sure to follow the requirements defined in the guide/writeup
    // for quitting immediately if the user input is out-of-bounds 
    // (i.e. not in the range 0 to dim_sq-1) as well as continuing to 
    // prompt for an input if the user chooses locations that have already
    // been chosen (already marked with an X or O).
    //**********************************************************

    // Add your code here for getting input
    int input;
    cout << "Player " << player << " enter your square choice [0-";
    cout << dim*dim - 1 << "]: " << endl;
    cin >> input;

    if(input < 0 || input > dim*dim-1){ 
      break; // exit loop if the user inputs a number that is out of bounds
    }

    bool valid = true; // setting bool variable to true
    while(tttdata[input] != '?'){ // checking if the input is valid (not already taken)
      cout << "Enter a valid location: " << endl;
      cin >> input;
      if(input < 0 || input > dim*dim-1){
        valid = false;
        break;
      }
      continue;
    }

    if(valid == false){ 
      break;
    }

    tttdata[input] = player;

    // Show the updated board if the user eventually chose a valid location
    // (i.e. you should have quit the loop and program by now without any 
    //  other output message if the user chosen an out-of-bounds input).
    printTTT(tttdata, dim);

    //**********************************************************
    // Complete the body of the while loop to process the input that was just
    //  received to check for a winner or draw and update other status, as 
    //  needed. 
    // 
    // To match our automated checkers' expected output, you must output 
    // one of the messages defined above using *one* of the cout commands 
    // (under the appropriate condition) below:
    //   cout << xwins_msg << endl;  OR
    //   cout << owins_msg << endl;  OR
    //   cout << draw_msg << endl;
    //
    // Note: Our automated checkers will examine a specific number of lines
    //  at the end of the program's output and expect to see the updated board
    //  and game status message.  You may certainly add some debug print  
    //  statements during development but they will need to be removed to 
    //  pass the automated checks.
    //**********************************************************

    int winner = checkForWinner(tttdata, dim); // checking for winner
    bool draw;
    if (winner == 1){
      cout << xwins_msg << endl;
      done = true; // game ends if winner
    }
    else if (winner == 2){
      cout << owins_msg << endl;
      done = true; // game ends if winner
    }
    else{
      draw = checkForDraw(tttdata, dim);
      if (draw == true){
        cout << draw_msg << endl;
        done = true; // game ends if there is draw
      }
    }

    // switching between player X and O
    if(player == 'X'){
      player = 'O';
    }
    else{
      player = 'X';
    }


  } // end while
  return 0;
}