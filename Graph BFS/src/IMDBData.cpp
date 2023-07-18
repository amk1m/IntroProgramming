// ITP 365 Spring 2023
// HW10
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "IMDBData.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

IMDBData::IMDBData(const std::string& fileName)
{
	// declaring input file stream using the fileName
    std::ifstream ifile(fileName);
    
    // throw an error if the file cannot be opened
    if(!ifile.is_open()){
        throw std::invalid_argument("error");
    }
    
    // declaring variables
    std::string tempName;
    std::string temp;
    std::vector<std::string> tempMovVec;
    
    // getting the first line
    getline(ifile, tempName); // gets first actor's name and stores it in tempName
    
    // while the end of file has not been reached yet
    while(!ifile.eof()){
        
        // get the line
        getline(ifile, temp);
        
        // checking if the line contains a movie or an actor (if first char is "|", movie)
        if(temp[0] == '|'){ // movie
            std::string tempMovie = temp.substr(1);
            tempMovVec.push_back(tempMovie); // add the movie to the vector of movies
        }
        else{ // actor name
            // add the old actor's name and movie vector to the map
            mActorsToMoviesMap.emplace(tempName, tempMovVec); // populating mActorsToMoviesMap
            tempName = temp; // storing the current actor's name in tempName
            tempMovVec.clear(); // clearing the movie vector (which contains the movies of the previous actor)
            continue; // go to next iteration of while loop to get the movies of the new actor
        }
    }
    
    // populate the MoviesToActors map by calling reverseMap on each item in actorstomovies map
    for(auto& item : mActorsToMoviesMap){
        reverseMap(item.first, item.second);
    }
    
}


void IMDBData::reverseMap(const std::string& actorName, const std::vector<std::string>& movies)
{
    // iterating through each element of movies vector
    for(int i = 0; i < movies.size(); i++){
        
//      1. If mMoviesToActorsMap already contains the movie in question, you need to add
//      actorName to that movie’s associated vector
        if(mMoviesToActorsMap.count(movies[i]) != 0){ // means movie already exists in the map
            (mMoviesToActorsMap.at(movies[i])).push_back(actorName);
        }
        
//      2. Otherwise, you need to add an entry in mMoviesToActorsMap that associates the movie
//      with a vector that, for now, only contains actorName
        else{
            std::vector<std::string> tempActors; // declaring vector for temporarily storing actors' names
            tempActors.push_back(actorName); // adding actor to the vector
            mMoviesToActorsMap.emplace(movies[i], tempActors);
        }
    }
}


const std::vector<std::string>& IMDBData::getMoviesFromActor(const std::string& actorName)
{
    // making sure that the key is in the map
    if(mActorsToMoviesMap.count(actorName) != 0){
        return mActorsToMoviesMap.at(actorName); // return the map at the key actorName
    }
    
    // return sEmptyVector if the key is not in the map
	return sEmptyVector;
}


const std::vector<std::string>& IMDBData::getActorsFromMovie(const std::string& movieName)
{
	// making sure that the key is in the map
    if(mMoviesToActorsMap.count(movieName) != 0){
        return mMoviesToActorsMap.at(movieName); // return the map at the key movieName
    }
    
    // return sEmptyVector if the key is not in the map
	return sEmptyVector;
}


void IMDBData::createGraph()
{
    // use the data in mMoviesToActorsMap and the IMDBGraph function createActorEdge to populate the map
    // The key (movie name) will be used to connect each actor with every other actor in the value (the actor name vector). Be sure to only connect each actor pair only once.
    
    // iterating through the mMoviesToActorsMap
    for(auto& item : mMoviesToActorsMap){
        // connect each actor with every other actor in the vector
        for(int i = 0; i < item.second.size(); i++){
            ActorNode* actor1 = mGraph.getActorNode(item.second[i]); // getting the actor at i
            
            // creating an edge between actor1 and all of the actors in the vector after it
            for(int j = i + 1; j < item.second.size(); j++){
                ActorNode* actor2 = mGraph.getActorNode(item.second[j]); // getting the actor at j
                mGraph.createActorEdge(actor1, actor2, item.first); // creating the edge between the two actors
            }
        }
    }
}


std::string IMDBData::findRelationship(const std::string& fromActor, const std::string& toActor)
{
    // declaring an output stringstream (to be returned later on)
    std::ostringstream ss;
    
    // checking if the graph contains the actors inputted by the user
    if(mGraph.containsActor(fromActor) == false){
        ss << fromActor + " is unknown!\n";
    }
    if(mGraph.containsActor(toActor) == false){
        ss << toActor + " is unknown!\n";
    }
    if(mGraph.containsActor(fromActor) == false || mGraph.containsActor(toActor) == false){
        mGraph.clearVisited();
        return ss.str(); // return the error message if at least one of the actors is not in the graph
    }
    
    // bool variable to keep track of whether a relationship between actors was found or not
    bool found = false;
    
//    1. Create a queue and enqueue the node we’re starting from…
    std::queue<ActorNode*> actorQueue;
    actorQueue.push(mGraph.getActorNode(fromActor)); // enqueing fromActor
    
//    2. While the BFS queue is not empty…
    while(!actorQueue.empty()){
        // a) Dequeue the front ITPGraphNode*, and save in currentNode
        ActorNode* currentNode = actorQueue.front(); // store in currentNode
        actorQueue.pop(); // calling pop to dequeue the first actor
        
        // b) If currentNode == targetNode, we found a path!
        if(currentNode == mGraph.getActorNode(toActor)){
            found = true; // set bool to true if found
        }
        
        // c) Otherwise if currentNode’s visited bool is false…
        else if(currentNode->mIsVisited == false){
            // 1. Visit currentNode
            // 2. Set currentNode visited to true
            currentNode->mIsVisited = true;
            // 3. Loop through currentNode’s adjacency list and if the visited flag is false…
            for(int i = 0; i < currentNode->mEdges.size(); i++){
                if(currentNode->mEdges[i].mOtherActor->mIsVisited == false){
                    //    a) enqueue the adjacent node
                    actorQueue.push(currentNode->mEdges[i].mOtherActor);
                    //    b) If the adjacent node path has a size of 0…
                    if(currentNode->mEdges[i].mOtherActor->mPath.size() == 0){
                        //    a) Set the adjacent node’s path equal to currentNode’s path
                        currentNode->mEdges[i].mOtherActor->mPath = currentNode->mPath;
                        //    b) Push_back adjacent nodes’s relevant path information (destination name and label in ITPPathInfo struct)
                        // You then need to append an additional PathPair to represent the additional “hop” of visiting.
                        currentNode->mEdges[i].mOtherActor->mPath.push_back(PathPair(currentNode->mEdges[i].mMovieName, currentNode->mEdges[i].mOtherActor->mName));
                    }
                }
            }
        }
    }
    
    // checking if a path was found
    if(found){
        // adding to the stringstream if a path was found between fromActor and toActor
        ss << "Found a path! (" << mGraph.getActorNode(toActor)->mPath.size() << " hops)" << std::endl;
        ss << fromActor << " was in..." << std::endl;
        
        // iterating through actor's path to trace the path
        for(int i = 0; i < mGraph.getActorNode(toActor)->mPath.size(); i++){
            // output if on the last element of the mPath vector
            if(i == mGraph.getActorNode(toActor)->mPath.size() - 1){
                ss << mGraph.getActorNode(toActor)->mPath[i].getMovieName() << " with " << mGraph.getActorNode(toActor)->mPath[i].getActorName() << std::endl;
            }
            else{
                ss << mGraph.getActorNode(toActor)->mPath[i].getMovieName() << " with " << mGraph.getActorNode(toActor)->mPath[i].getActorName() << " who was in..." << std::endl;
            }
        }
        
        // clear mPath
        mGraph.clearVisited(); // clear mGraph
        
        return ss.str(); // return result
    }
    
//    3. If we made it here, we didn’t find a path
    ss << "Didn't find a path." << std::endl;
    mGraph.clearVisited(); // clear mGraph
    
    return ss.str(); // return result
}


// Leave here! Do not edit!!!
// DO NOT REMOVE THIS LINE
std::vector<std::string> IMDBData::sEmptyVector;
