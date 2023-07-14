// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

// To Do - Complete this function
void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    
    // Erase any old contents
    content.clear();
    users.clear();

    // TO DO - Add your code below.

		// adding to content vector

		// declaring variables needed for adding elements to the content vector
    int numContentItems;
    int tempCID;
    int tempCType;
    string tempName;
		int tempTotReviews;
    int tempTotStars;
    int tempRating;
		int tempNumEpisodes;
		vector<string> usersViewed;

		// getting number of content items from the file
    is >> numContentItems;
		cout << numContentItems << endl;

		// throw a parser error if getting the numContentItems does not work
		if(is.fail()){
			throw ParserError(error_msg_1);
		}

		// iterating through all content items to add them to content vector
    for(int i = 0; i < numContentItems; i++){
				// getting the content ID
        is >> tempCID;
				
				// throwing parser error if getting the ID fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}
				// getting the content type
				is >> tempCType;
				
				// throwing parser error if getting the type of content fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}
				// getting the name of the content
				// by using getline
				getline(is, tempName);
				getline(is, tempName, '\t');
				getline(is, tempName);
				
				// throwing parser error if getting the name of content fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}

				// getting the total reviews
				is >> tempTotReviews;
				// throwing parser error if getting total reviews fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}

				// getting the total stars
				is >> tempTotStars;
				// throwing parser error if getting the total stars fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}

				// getting the rating
				is >> tempRating;
				// throwing parser error if getting the rating fails
				if(is.fail()){
					throw ParserError(error_msg_2);
				}

				// checking if the content is a series - has number of episodes
				if(tempCType == 1){
					// getting the number of episodes if content is series
					is >> tempNumEpisodes;
					// throwing parser error if getting the num of episodes fails
					if(is.fail()){
						throw ParserError(error_msg_2);
					}
				}

				// create the content object (movie or series)
				Content* newc = NULL;
				if(tempCType == 1){ // creating a series if type is 1
					newc = new Series(tempCID, tempName, tempTotReviews, tempTotStars, tempRating, tempNumEpisodes);
				}
				else{ // creating a movie if type is not 1
					newc = new Movie(tempCID, tempName, tempTotReviews, tempTotStars, tempRating);
				}

				// finding the users who have viewed the content
				// using getline
				string myLine;
				getline(is, myLine);
				getline(is, myLine);

				// using a stringstream to get each user on the line
				stringstream ssUsers(myLine);
				string user;

				// adding each user that is in the stringstream
				while(ssUsers >> user){
					newc->addViewer(user);				
				}

				// adding the content to the content vector
				content.push_back(newc);
				
    }
		

		// adding to the users vector

		// declaring variables needed for adding to the vector of users
		string userName;
		int tempContentID;
		int tempLimit;
		string contentLine;

		// getting usernames as input from the file
		while(is >> userName){
			// for each username

			// getting the limit of the user
			is >> tempLimit;
			// throwing parser error if getting the limit fails
			if(is.fail()){
				throw ParserError(error_msg_3);
			}

			// making a new user object
			User* u = new User(userName, tempLimit);

			// using getline to get the content watched for the user (content IDs)
			getline(is, contentLine);
			getline(is, contentLine);
			// throwing parser error if getting the line of watched content IDs fails
			if(is.fail()){
				throw ParserError(error_msg_3);
			}
			// using stringstream to get each content ID that the user watched
			stringstream contentWatched(contentLine);
			while(contentWatched >> tempContentID){
				u->addToHistory(tempContentID); // adding to the user history
				// throwing a parser error if getting the content ID fails
				if(is.fail()){
					throw ParserError(error_msg_3);
				}
			}

			// adding the user to the users vector
			users.push_back(u);

		}

}