#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

// To do - Complete this function
StreamService::StreamService()
{
    // Update as needed
		cUser_ = NULL;
    
}

// To do - Complete this function
StreamService::~StreamService()
{
    // deallocate memory in content_ and users_
    for(size_t i = 0; i < content_.size(); i++){
        delete content_[i];
    }

    for(size_t i = 0; i < users_.size(); i++){
        delete users_[i];
    }


}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string& uname)
{
    bool valid = false;
    int uIndex;
	if(cUser_ != NULL){
		throw runtime_error("Please log out first.");
	}

    for(size_t i = 0; i < users_.size(); i++){
        if(users_[i]->uname == uname){
            valid = true;
            uIndex = i;
        }
    }
    if(valid == false){
        throw invalid_argument("Not a valid username.");
    }

    cUser_ = users_[uIndex]; // setting the current user

}

// To do - Complete this function
void StreamService::userLogout()
{
    cUser_ = NULL;

}

// To do - Complete this function
std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        if(partial == "*" || (content_[i]->name().find(partial) != string::npos)){
            results.push_back(i);
        }        
    }
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID)
{
    // throwing exceptions
    // if not logged in
    throwIfNoCurrentUser();

    // if the content ID is not valid
    if(!(isValidContentID(contentID))){
        throw range_error("Content ID is out of valid range.");
    }

    // if above rating limit
    if(content_[contentID]->rating() > cUser_->ratingLimit){
        throw RatingLimitError("Rating of content is too high.");
    }

    //cUser_->history.push_back(contentID);
    cUser_->addToHistory(contentID);
    content_[contentID]->addViewer(cUser_->uname);


}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars)
{
    throwIfNoCurrentUser();

    if(numStars < 0 || numStars > 5){
        throw ReviewRangeError("Not a valid number of stars.");
    }

    content_[contentID]->review(numStars);

}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{
    // Change this when you are ready, but for now it is a 
    // dummy implementation
		// current user asks for suggestions similar to provided content

		// find set of users who also watched this content
		// adding to similarUsers vector to users who watched the same thing
		vector<User*> similarUsers; // declaring the similarUsers vector

		// for each user: go through their history and check to see if they
		// watched the given content (the parameter of this function)
		for(size_t i = 0; i < users_.size(); i++){
			User* temp = users_[i];
			// going through the user's history to check
			for(size_t j = 0; j < (temp->history).size(); j++){
				if(((temp->history)[j] == contentID) && (temp != cUser_)){
					// adding the user to the vector if they viewed the given content
					similarUsers.push_back(temp); 
					break;
				}
			}
		}

		// make vector for content IDs and vector for number of times watched
		vector<CID_T> ids_;
		vector<int> times;

		// for each user in the similar users vector, check each element 
		// of the user's history and add to the id and times vector if not there already
		// if there already, increment the times by 1
		for(size_t i = 0; i < similarUsers.size(); i++){
			User* temp = similarUsers[i];
			bool exists = false; // bool variable to keep track of whether
													 // the content exists in the ids_ vector already 
			int index; // variable to keep track of index of the content in the vector

			// ** content cannot be the content that is typed in the parameter **
			// ** content cannot be content that cUser has already watched **

			// for each element in history, check if it is in ids_ vector
			for(size_t j = 0; j < (temp->history).size(); j++){
				exists = false;
				for(size_t k = 0; k < ids_.size(); k++){
					if(((temp->history)[j] == ids_[k]) && ((temp->history)[j] != contentID)){
						exists = true;
						index = j;
						break;
						// break if the content was found in the ids_ vector
					}
				}
				if(exists == true){
					incrementing the number of times watched by 1 if it is
					already in the ids_ vector
					times[index] += 1;
				}
				else if((temp->history)[j] != contentID){
					bool alrWatched = false; // shows if content was already watched by user
					// checking to see if the content is already in the cUser_ history
					for(size_t l = 0; l < (cUser_->history).size(); l++){
						if((cUser_->history)[l] ==(temp->history)[j]){
							alrWatched = true;
						}
					}
					// if content was not watched by cUser_ yet, then add to the ids_ vector
					// and add to the times vector
					if(alrWatched == false){
						ids_.push_back((temp->history)[j]);
						times.push_back(0);
					}
				}
			}
			
		}

		// if no valid content suggestions were found, then vector ids_ has size 0
		// return -1 if there are no valid suggestions
		if(ids_.size() == 0){
			return -1;
		}

		// if the size of ids_ is greater than 0
		int maxTimes;
		int maxIndex;
		// looping through the times vector to find the maximum number of times
		for(size_t i = 0; i < times.size(); i++){
			if(i == 0){
				maxTimes = times[0];
				maxIndex = 0;
			}
			else if(times[i] >= maxTimes){
				maxTimes = times[i];
				maxIndex = i;
			}
		}

		// returning the content ID that was viewed the most times by similar users
    return (ids_[maxIndex]);

}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const
{
    // Do not alter this
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object



}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
