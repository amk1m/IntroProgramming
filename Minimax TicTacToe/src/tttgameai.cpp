// ITP 365 Spring 2023
// HW09
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

// You can use this for the std::min / std::max functions
#include <algorithm>
#include "tttgameai.h"
#include "tttgame.h"
#include "tttgamedata.h"

bool IsGameOver(const GameState& state)
{
    // call GetScore
    // if GetScore returns 0, need to check if there are any empty spaces - if there are, means that game is not over yet
    // if no spaces are empty, means game is over and there is tie
    
    // float to store the return value of GetScore
    float score;
    score = GetScore(state);
    
    // if GetScore returns 0, check if there are empty spaces
    if(score == 0.0){
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                
                if(state.mBoard[i][j] == GameState::Empty){
                    return false; // game is not over yet if there are empty spaces and no winner yet
                }
            }
        }
        
        return true; // returns true if there is no winner and there is no empty space left
    }
    
    // if GetScore returns something other than 0.0, means that there is a winner, so return true
    return true;
    
}

void GenStates(GTNode* root, bool xPlayer)
{
    // base case
    if(IsGameOver(root->mState)){
        return;
    }
    
    // iterate through all positions of the board - do this with a nested for loop
    for(int i = 0; i < 3; i++){ // row
        for(int j = 0; j < 3; j++){ // col
            
            //   Each position that is empty should…
            if(root->mState.mBoard[i][j] == GameState::Empty){ // checking that the square is empty
                
                //   1. Generate a new child node
                GTNode* child = new GTNode;
                
                //   2. Set child’s board to the root’s board
                child->mState = root->mState;
                        
                //   3. Set the empty position to the X (or the player’s symbol)
                if(xPlayer){
                    child->mState.mBoard[i][j] = GameState::X;
                }
                else{
                    child->mState.mBoard[i][j] = GameState::O;
                }
                
                //   4. Add the node as a child to root
                root->mChildren.push_back(child);
                
                //   5. Generate the child nodes for this child (or call the function recursively)
                GenStates(child, !xPlayer); // call the function recursively
            }
        }
    }
}

float GetScore(const GameState& state) // return 1 if O wins, -1 if X wins and 0 if tie
{
    // check all rows
    // 1st row:
    // comparing all squares in the first row
    if((state.mBoard[0][0] == state.mBoard[0][1]) && (state.mBoard[0][1] == state.mBoard[0][2])){
        
        if(state.mBoard[0][0] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[0][0] == GameState::X){
            return -1.0; // X wins
        }
    }

    // 2nd row:
    // comparing all squares in the second row
    if((state.mBoard[1][0] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[1][2])){
        
        if(state.mBoard[1][0] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[1][0] == GameState::X){
            return -1.0; // X wins
        }
    }

    // 3rd row:
    // comparing all squares in the third row
    if((state.mBoard[2][0] == state.mBoard[2][1]) && (state.mBoard[2][1] == state.mBoard[2][2])){
        
        if(state.mBoard[2][0] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[2][0] == GameState::X){
            return -1.0; // X wins
        }
    }
    
    // check all columns
    // 1st column
    // comparing all squares in the first column
    if(state.mBoard[0][0] == state.mBoard[1][0] && state.mBoard[1][0] == state.mBoard[2][0]){
        
        if(state.mBoard[0][0] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[0][0] == GameState::X){
            return -1.0; // X wins
        }
    }
        
    // 2nd column
    // comparing all squares in the second column
    if((state.mBoard[0][1] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[2][1])){
        
        if(state.mBoard[0][1] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[0][1] == GameState::X){
            return -1.0; // X wins
        }
    }
        
    // 3rd column
    // comparing all squares in the third column
    if((state.mBoard[0][2] == state.mBoard[1][2]) && (state.mBoard[1][2] == state.mBoard[2][2])){
        
        if(state.mBoard[0][2] == GameState::O){
            return 1.0; // O wins
        }
        else if(state.mBoard[0][2] == GameState::X){
            return -1.0; // X wins
        }
    }
        
    // check both diagonals
    // first diagonal: 00, 11, 22 (top left to bottom right)
    if((state.mBoard[0][0] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[2][2])){
        
        if(state.mBoard[0][0] == GameState::X){
            return -1.0; // X wins
        }
        else if(state.mBoard[0][0] == GameState::O){
            return 1.0; // O wins
        }
    }
    
    // second diagonal: 02, 11, 20 (top right to bottom left)
    if((state.mBoard[0][2] == state.mBoard[1][1]) && (state.mBoard[1][1] == state.mBoard[2][0])){
        
        if(state.mBoard[0][2] == GameState::X){
            return -1.0; // X wins
        }
        else if(state.mBoard[0][2] == GameState::O){
            return 1.0; // O wins
        }
    }
    
	return 0.0;
}

float MinPlayer(const GTNode* node)
{
    // setting minVal to a large number
    float minVal = 1000;
    
    // check if it is leaf node - means the mChildren is empty
    if(node->mChildren.size() == 0){
        return GetScore(node->mState); // call GetScore if it is a leaf node
    }
    else{ // if it is not a leaf node, iterate through the children
        
        for(GTNode* curr : node->mChildren){
            minVal = std::min(minVal, MaxPlayer(curr)); // finding minVal using std::min
        }
    }
    
    return minVal;
    
    
}

float MaxPlayer(const GTNode* node)
{
    // setting maxVal to a small number
    float maxVal = -1000;
    
    // check if it is leaf node - means the mChildren is empty
    if(node->mChildren.size() == 0){
        return GetScore(node->mState); // call GetScore if it is a leaf node
    }
    else { // if it is not a leaf node, iterate through the children
        
        for(GTNode* curr : node->mChildren){
            maxVal = std::max(maxVal, MinPlayer(curr)); // finding maxVal using std::max
        }
    }
    
    return maxVal;
    
}

const GTNode* MinimaxDecide(const GTNode* root)
{
    // decide which subtree leads to O winning
    
    // setting float max to a small value
    float max = -1000;
    
    // setting decide node to nullptr - this will later store the node that is the decision to be returned
    const GTNode* decide = nullptr;
    
    // go through each child node of the root
    for(GTNode* curr : root->mChildren){
        // Find the node with the largest MinPlayer score - call MinPlayer on the current node
        float temp = MinPlayer(curr);
        if(temp > max){
            max = temp; // if the float returned by MinPlayer(curr) is larger than current max, set the decide node to the current node
            decide = curr;
        }
    }

    // Make the move to yield the state found above - return the decide node
	return decide;
    
}

unsigned pickMove(const GameState& board)
{
    // make GTNode* to keep track of the node/state
    GTNode* start = new GTNode;
    
    // put board into GTNode* start
    start->mState = board;
    
    // call GenStates to generate the tree
    GenStates(start, false);
    
    // call MiniMaxDecide to find next move
    const GTNode* move = MinimaxDecide(start);
    
    // find/return the square that is different between the two boards
	return changedSquare(board, move->mState);
}

unsigned changedSquare(const GameState& board1, const GameState& board2)
{
    // nested for loop to iterate through all positions of the board
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            
            if(board1.mBoard[i][j] != board2.mBoard[i][j]){ // checking if the two squares are different
                
                return (i * 3) + j + 1; // return the number of the square that is different between board1 and board2
            }
        }
    }
}


