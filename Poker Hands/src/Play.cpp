// ©2023 Nathan Greenfield
#include "ITPVector.hpp"
#include "Cards.h"

#include <fstream>
#include <iostream>

void playPoker(std::istream& in, std::ostream& out, unsigned seed)
{
	srand(seed);

	while (true)
	{
		ITPVector<Card> deck;
		createDeck(deck);

		PokerHand hand(deck);
		out << "You drew: " << hand << std::endl;
		out << "You have a " << hand.getBestPokerHand() << std::endl;

		out << "Try again (y/n): ";
		std::string choice;
		std::getline(in, choice);
		if (choice != "y" && choice != "Y")
		{
			break;
		}
	}
}


void playPoker(const std::string& inFile, const std::string& outFile, unsigned seed)
{
	std::ifstream inStream(inFile);

	if (!inStream.is_open())
	{
		std::cout << "Failed to open the file successfully" << std::endl;
	}

	std::ofstream outStream(outFile);

	playPoker(inStream, outStream, seed);
}
