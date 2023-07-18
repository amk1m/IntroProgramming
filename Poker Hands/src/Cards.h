// ©2023 Nathan Greenfield
// Cards.h
// Defines Cards and Poker Hand functionality
#pragma once

#include <ostream>
#include <vector>

#include "ITPVector.hpp"

// enum to define the suits
enum Suit
{
	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES
};

// struct that defines an individual card
struct Card
{
	// Default constructor initializes to 2 of clubs
	Card()
	{ 
		mRank = 2;
		mSuit = CLUBS;
	}

	// Non-default constructor
	Card(unsigned rank, Suit suit)
	{
		mRank = rank;
		mSuit = suit;
	}

	unsigned mRank;
	Suit mSuit;
};

// Function: << operator for Card
// Purpose: Outputs the name and suit of the card
// Input: ostream and card
// Returns: ostream, with card data output to it
std::ostream& operator<<(std::ostream& os, const Card& card);

// Function: < comparison operator for Card
// Purpose: Compares the value of the left and right card
// Input: Two cards to compare
// Returns: true if left < right
bool operator<(const Card& left, const Card& right);

// Function: 
// Purpose: 
// Input: 
// Returns: 
bool operator>(const Card& left, const Card& right);


// Function: createDeck
// Purpose: Given an empty ITPVector of Cards, inserts a
// standard 52 card deck and shuffles it
// Input: An (empty) ITPVector of Cards (by reference)
// Returns: nothing
void createDeck(ITPVector<Card>& deck);

class PokerHand
{
public:
	// Function: Constructor
	// Purpose: Draws 5 cards from the supplied deck, and sorts them
	// by rank
	// Input: Takes in a ITPVector of cards for the deck
	// Returns: Nothing
	PokerHand(ITPVector<Card>& deck);

	// Function: hasStraight
	// Purpose: Determines if the hand has a straight
	// Input: None
	// Returns: true if there's a straight
	bool hasStraight() const;

	// Function: hasFlush
	// Purpose: Determines if the hand has a flush
	// Input: None
	// Returns: true if there's a flush
	bool hasFlush() const;

	// Function: hasFourOfAKind
	// Purpose: Determines if the hand has a 4 of a kind
	// Input: None
	// Returns: true if there's a 4 of a kind
	bool hasFourOfAKind() const;

	// Function: hasFullHouse
	// Purpose: Determines if the hand has a full house
	// Input: None
	// Returns: true if there's a full house
	bool hasFullHouse() const;

	// Function: hasThreeOfAKind
	// Purpose: Determines if the hand has a three of a kind
	// Input: None
	// Returns: true if there's a three of a kind
	bool hasThreeOfAKind() const;

	// Function: hasTwoPairs
	// Purpose: Determines if the hand has two pairs
	// Input: None
	// Returns: true if there's two pairs
	bool hasTwoPairs() const;

	// Function: hasPair
	// Purpose: Determines if there's a pair
	// Input: None
	// Returns: true if there's a pair
	bool hasPair() const;

	// Function: getBestPokerHand
	// Purpose: Returns a string describing the poker hand this PokerHand
	// contains
	// Input: None
	// Returns: The name of the best poker hand
	std::string getBestPokerHand() const;

	// Function: << operator
	// Purpose: Prints out the hand
	friend std::ostream& operator<<(std::ostream& os, const PokerHand& hand);
private:
	// Function: Constructor
	// Purpose: Draws 5 cards from the supplied deck, and sorts them
	// by rank
	// Input: Takes in a ITPVector of cards for the deck
	// Returns: Nothing
	void sortHand();

	// Data
	ITPVector<Card> mHand;
};
