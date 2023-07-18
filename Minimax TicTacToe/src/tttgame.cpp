// ITP 365 Spring 2023
// HW09
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame()
{
    // initializes the board by setting all spaces to empty
    
    // nested for loop for going through each space on the board and initialize to empty
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            currentState.mBoard[i][j] = GameState::Empty; // setting the space to empty
        }
    }
}

GameState TicTacToeGame::getBoard() const
{
    // return the current GameState (getter function)
	return currentState;
}

bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state)
{
    // return true if square can successfully be set
    // return false if square is already taken
   
    // checking if the given square is empty
    if(currentState.mBoard[row][col] == GameState::Empty){
        
        currentState.mBoard[row][col] = state; // set the square to the given state if it is empty
        return true;
    }

	return false; // return false - means that the square is already taken
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state)
{
    // square is number from 1-9 (inclusive)
    // 1,2,3 are first row; 4,5,6 are second row and 7,8,9 are third row (left->right)
    // in enum: first row is 0, second is 1, third is 2; same with columns
    
    // finding the row and col using the given square number
    unsigned row = (square - 1) / 3;
    unsigned col = (square - 1) % 3;
    
    return setSquareState(row, col, state); // calling setSquareFunction (overloaded)
    
}

char TicTacToeGame::getWinner()
{
    // return 'X' or 'O' depending on who won; return 'N' if tie; return ' ' if spaces are still available
    
    // check all rows
    // 1st row:
    // making sure that the first square is not empty
    if(currentState.mBoard[0][0] != GameState::Empty){
        
        // comparing all squares of the first row
        if((currentState.mBoard[0][0] == currentState.mBoard[0][1]) && (currentState.mBoard[0][1] == currentState.mBoard[0][2])){
            
            if(currentState.mBoard[0][0] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
        }
    }
    
    // 2nd row:
    // making sure that the first square of the second row is not empty
    if(currentState.mBoard[1][0] != GameState::Empty){
        
        // comparing all squares of the second row
        if((currentState.mBoard[1][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[1][2])){
            
            if(currentState.mBoard[1][0] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
        }
    }
    
    // 3rd row:
    // making sure that the first square of the third row is not empty
    if(currentState.mBoard[2][0] != GameState::Empty){
        
        // comparing all squares of the third row
        if((currentState.mBoard[2][0] == currentState.mBoard[2][1]) && (currentState.mBoard[2][1] == currentState.mBoard[2][2])){
            
            if(currentState.mBoard[2][0] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
        }
    }
    
    // check all columns
    // 1st column
    // making sure that the first square of the first column is not empty
    if(currentState.mBoard[0][0] != GameState::Empty){
        
        // comparing all squares of the first column
        if(currentState.mBoard[0][0] == currentState.mBoard[1][0] && currentState.mBoard[1][0] == currentState.mBoard[2][0]){
            
            if(currentState.mBoard[0][0] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
            
        }
        
    }
    
    // 2nd column
    // making sure that the first square of the second column is not empty
    if(currentState.mBoard[0][1] != GameState::Empty){
        
        // comparing all squares of the second column
        if((currentState.mBoard[0][1] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][1])){
            
            if(currentState.mBoard[0][1] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
        }
    }
    
    // 3rd column
    // making sure that the first square of the third column is not empty
    if(currentState.mBoard[0][2] != GameState::Empty){
        
        // comparing all squares of the third column
        if((currentState.mBoard[0][2] == currentState.mBoard[1][2]) && (currentState.mBoard[1][2] == currentState.mBoard[2][2])){
            
            if(currentState.mBoard[0][2] == GameState::X){
                return 'X'; // X wins
            }
            else{
                return 'O'; // O wins
            }
        }
    }
     
    // check both diagonals
    // first diagonal: 00, 11, 22
    // comparing values of the first diagonal (going from top left to bottom right)
    if((currentState.mBoard[0][0] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][2])){
        
        if(currentState.mBoard[0][0] == GameState::X){
            return 'X'; // X wins
        }
        else if(currentState.mBoard[0][0] == GameState::O){
            return 'O'; // O wins
        }
        
    }
    
    // second diagonal: 02, 11, 20
    // comparing values of the second diagonal (going from top right to bottom left)
    if((currentState.mBoard[0][2] == currentState.mBoard[1][1]) && (currentState.mBoard[1][1] == currentState.mBoard[2][0])){
        
        if(currentState.mBoard[0][2] == GameState::X){
            return 'X'; // X wins
        }
        else if(currentState.mBoard[0][2] == GameState::O){
            return 'O'; // O wins
        }
        
    }
    
    // after checking for any possible winners: check if the entire board is filled
    // if entire board is filled and nothing has been returned yet, return tie
    // if there is an empty spot, return ' ' to indicate game is still going on
    for(int i = 0; i < 3; i++){
        
        for(int j = 0; j < 3; j++){
            
            if(currentState.mBoard[i][j] == GameState::Empty){
                
                return ' '; // means that there is at least one empty space, so the game is not over
                
            }
            
        }
    }

	return 'N';	// returns N if there is a tie
}

