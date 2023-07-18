// ITP 365 Spring 2023
// HW06
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "Cards.h"
#include "ITPVector.hpp"

#include <random>
#include <algorithm>

// Function: Constructor
// Purpose: Draws 5 cards from the supplied deck, and sorts them
// by rank
// Input: Takes in a ITPVector of cards for the deck
// Returns: Nothing
PokerHand::PokerHand(ITPVector<Card>& deck)
{
    // for loop for adding cards to the deck vector
    for(int i = 0 ; i < 5; i++){
        mHand.push_back(deck.back());
        deck.pop_back();
    }
    
    // calling the sort function to sort the hand
    sortHand();
}

// Function: getBestPokerHand
// Purpose: Returns a string describing the poker hand this PokerHand
// contains
// Input: None
// Returns: The name of the best poker hand
std::string PokerHand::getBestPokerHand() const
{
    // conditional statements for checking the different poker hands
    
    if(hasStraight() && hasFlush()){ // straight flush
        return "straight flush";
    }
    else if(hasFourOfAKind()){ // four of a kind
        return "four of a kind";
    }
    else if(hasFullHouse()){ // has a full house
        return "full house";
    }
    else if(hasFlush()){ // has a flush
        return "flush";
    }
    else if(hasStraight()){ // has straight
        return "straight";
    }
    else if(hasThreeOfAKind()){ // has three of a kind
        return "three of a kind";
    }
    else if(hasTwoPairs()){ // has two pairs
        return "two pairs";
    }
    else if(hasPair()){ // has a pair
        return "pair";
    }
    else{ // high card
        return "high card";
    }
}

// Function: hasStraight
// Purpose: Determines if the hand has a straight
// Input: None
// Returns: true if there's a straight
bool PokerHand::hasStraight() const
{
    // finding the rank of the first card
    int startRank = mHand[0].mRank;
    
    // for loop for iterating through the vector
    for(int i = 1; i < mHand.size(); i++){
        
        // checking that the rank is incremented by 1 for each card in poker hand
        if((mHand[i]).mRank != (startRank + 1)){ //
            return false;
        }
        
        startRank += 1;
        
    }
    
    return true;
}

// Function: hasFlush
// Purpose: Determines if the hand has a flush
// Input: None
// Returns: true if there's a flush
bool PokerHand::hasFlush() const
{
    // checking the suit of the first card
    Suit same = mHand[0].mSuit;
    
    // for loop - checking that each suit is the same
    for(int i = 0; i < mHand.size(); i++){
        
        if(mHand[i].mSuit != same){
            return false;
        }
    }
    
    return true;
}

// Function: hasFourOfAKind
// Purpose: Determines if the hand has a 4 of a kind
// Input: None
// Returns: true if there's a 4 of a kind
bool PokerHand::hasFourOfAKind() const
{
    // getting the first rank and last rank (first and last card)
    unsigned first = mHand[0].mRank;
    unsigned last = mHand[mHand.size() - 1].mRank;
    
    // checking that there are 4 of the same cards in the poker hand
    if(mHand[1].mRank == first && mHand[2].mRank == first && mHand[3].mRank == first){
        return true;
    }
    else if(mHand[1].mRank == last && mHand[2].mRank == last && mHand[3].mRank == last){
        return true;
    }

    return false;
}

// Function: hasFullHouse
// Purpose: Determines if the hand has a full house
// Input: None
// Returns: true if there's a full house
bool PokerHand::hasFullHouse() const
{
    // check first and last ranks
    unsigned first = mHand[0].mRank;
    unsigned last = mHand[mHand.size() - 1].mRank;
    
    // possibility 1 - check if first 3 cards are same and last 2 cards are same
    if(mHand[1].mRank == first && mHand[2].mRank == first){
        
        if(mHand[3].mRank == last){
            return true;
        }
        else{
            return false;
        }
        
    }
    // possibility 2 - check if first 2 cards are same and last 3 cards are same
    else if(mHand[1].mRank == first){
        
        if(mHand[2].mRank == last && mHand[3].mRank == last){
            return true;
        }
        else{
            return false;
        }
        
    }
    
    return false;
}

// Function: hasThreeOfAKind
// Purpose: Determines if the hand has a three of a kind
// Input: None
// Returns: true if there's a three of a kind
bool PokerHand::hasThreeOfAKind() const
{
    // possibility 1: first 3 cards are same rank
    if(mHand[0].mRank == mHand[1].mRank && mHand[1].mRank == mHand[2].mRank){
        return true;
    }
    
    // possibility 2: middle 3 cards are same rank
    else if(mHand[1].mRank == mHand[2].mRank && mHand[2].mRank == mHand[3].mRank){
        return true;
    }
    
    // possibility 3: last 3 cards are same rank
    else if(mHand[2].mRank == mHand[3].mRank && mHand[3].mRank == mHand[4].mRank){
        return true;
    }
    
    return false;
}

// Function: hasTwoPairs
// Purpose: Determines if the hand has two pairs
// Input: None
// Returns: true if there's two pairs
bool PokerHand::hasTwoPairs() const
{
    // possibility 1: pairs are the first 4 cards (2 and 2)
    if(mHand[0].mRank == mHand[1].mRank && mHand[2].mRank == mHand[3].mRank){
        return true;
    }
    
    // possibility 2: pairs are the last 4 cards (2 and 2)
    else if(mHand[1].mRank == mHand[2].mRank && mHand[3].mRank == mHand[4].mRank){
        return true;
    }
    
    // possibility 3: pairs are the outer 4 cards (2 first, 2 last)
    else if(mHand[0].mRank == mHand[1].mRank && mHand[3].mRank == mHand[4].mRank){
        return true;
    }

    return false;
}

// Function: hasPair
// Purpose: Determines if there's a pair
// Input: None
// Returns: true if there's a pair
bool PokerHand::hasPair() const
{
    // checking if there is a pair - comparing the ranks of all the cards to each other
    if(mHand[0].mRank == mHand[1].mRank || mHand[1].mRank == mHand[2].mRank || mHand[2].mRank == mHand[3].mRank || mHand[3].mRank == mHand[4].mRank){
        return true;
    }

    return false;
}

void PokerHand::sortHand()
{
    // for loop
    for(int i = 0; i < mHand.size() - 1; i++){
        
        // getting minimum index
        int minIndex = i;
        
        for(int j = i; j < mHand.size(); j++){
            
            if(mHand[j] < mHand[minIndex]){
                minIndex = j; // changing minimum index to j if found a new smallest value
            }
            
        }
        
        if(minIndex != i){
            
            Card temp = mHand[i]; // swapping the two elements
            mHand[i] = mHand[minIndex];
            mHand[minIndex] = temp;
            
        }
        
    }
}

// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(ITPVector<Card>& deck)
{
    // looping through each of the suits
    for(int numSuit = 0; numSuit < 4; numSuit++){
        
        // adding each card (for the current suit)
        for(int numRank = 2; numRank < 15; numRank++){
            Card toAdd;
            toAdd = Card(numRank, static_cast<Suit>(numSuit));
            deck.push_back(toAdd);
        }
        
    }
    
    // shuffling the deck
    std::sort(&deck[0], &deck[0] + deck.size());
    std::random_shuffle(&deck[0], &deck[0] + deck.size());
}

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    // getting the rank and suit of the card
    unsigned tempRank = card.mRank;
    int tempSuit = card.mSuit;
    
    // vector of the cards above rank 10
    std::vector<std::string> vecHighCards = {"Jack", "Queen", "King", "Ace"};
    
    // different output based on the suit of the card
    if(tempSuit == 0){ // clubs
        
        if(tempRank > 10){
            os << vecHighCards[tempRank - 11] << " of Clubs";
        }
        else{
            os << tempRank << " of Clubs";
        }
        
    }
    else if(tempSuit == 1){ // diamonds
        
        if(tempRank > 10){
            os << vecHighCards[tempRank - 11] << " of Diamonds";
        }
        else{
            os << tempRank << " of Diamonds";
        }
    }
    else if(tempSuit == 2){ // hearts
        
        if(tempRank > 10){
            os << vecHighCards[tempRank - 11] << " of Hearts";
        }
        else{
            os << tempRank << " of Hearts";
        }
    }
    else if(tempSuit == 3){ // spades
        if(tempRank > 10){
            os << vecHighCards[tempRank - 11] << " of Spades";
        }
        else{
            os << tempRank << " of Spades";
        }
    }
    
    
    return os;
}


// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right)
{
    // comparing the left and right cards by checking both rank and the suit
    if(left.mRank < right.mRank){
        return true;
    }
    else if(left.mRank == right.mRank && left.mSuit < right.mSuit){
        return true;
    }
    return false;
}

// Function: > comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left > right
bool operator>(const Card& left, const Card& right)
{
    // comparing the left and right cards by checking both rank and the suit
    if(left.mRank > right.mRank){
        return true;
    }
    else if(left.mRank == right.mRank && left.mSuit > right.mSuit){
        return true;
    }
    return false;
}

// Function: << operator
// Purpose: Prints out the hand
std::ostream& operator<<(std::ostream& os, const PokerHand& hand)
{
    // vector of the suits of cards higher than rank 10
    std::vector<std::string> vecHighCards = {"Jack", "Queen", "King", "Ace"};
    
    os << "{ ";
    
    // for loop
    for(int i = 0; i < hand.mHand.size(); i++){
        
        // getting rank and suit of the card
        unsigned tempRank = hand.mHand[i].mRank;
        int tempSuit = hand.mHand[i].mSuit;
        
        // conditional statements for checking suits
        if(tempSuit == 0){ // clubs
            
            if(tempRank > 10){
                os << vecHighCards[tempRank - 11] << " of Clubs";
            }
            else{
                os << tempRank << " of Clubs";
            }
            
        }
        else if(tempSuit == 1){ // diamonds
            
            if(tempRank > 10){
                os << vecHighCards[tempRank - 11] << " of Diamonds";
            }
            else{
                os << tempRank << " of Diamonds";
            }
        }
        else if(tempSuit == 2){ // hearts
            
            if(tempRank > 10){
                os << vecHighCards[tempRank - 11] << " of Hearts";
            }
            else{
                os << tempRank << " of Hearts";
            }
        }
        else if(tempSuit == 3){ // spades
            if(tempRank > 10){
                os << vecHighCards[tempRank - 11] << " of Spades";
            }
            else{
                os << tempRank << " of Spades";
            }
        }
        
        if(i < hand.mHand.size() - 1){
            os << ", ";
        }
        
    }
    
    os << " }";
     
    
    return os;
}
