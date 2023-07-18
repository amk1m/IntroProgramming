// ITP 365 Spring 2023
// HW10
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "catch.hpp"
#include "IMDBData.h"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests -- only add sections
TEST_CASE("Student tests", "[student]") 
{
    
    SECTION("Testing getMoviesFromActor")
    {
        // IMDBData constructor
        IMDBData data1("input/top250.list");

        // getting list of movies that the actor was in
        std::vector<std::string> movieList = data1.getMoviesFromActor("F. Murray Abraham");
        
        // checking each of the elements in movieList
        REQUIRE(movieList[0] == "Amadeus (1984)");
        REQUIRE(movieList[1] == "Scarface (1983)");
        REQUIRE(movieList[2] == "The Grand Budapest Hotel (2014)");

    }

    SECTION("Testing getActorsFromMovie")
    {
        // IMDBData constructor
        IMDBData data1("input/top250.list");
        
        // vector of actors
        std::vector<std::string> actorList = data1.getActorsFromMovie("Jurassic Park (1993)");
        
        // checking the size of actorList
        REQUIRE(actorList.size() == 29);
        
    }
    
    SECTION("Testing find relationship")
    {
        // IMDBData constructor
        IMDBData data1("input/top250.list");
        data1.createGraph(); // calling mGraph to create the graph
        
        // testing two actors who have a path
        std::string result1;
        result1 = data1.findRelationship("Gail Yudain", "Seguna");
        REQUIRE(result1 == "Found a path! (6 hops)\nGail Yudain was in...\nThe Departed (2006) with Brian Smyj who was in...\nGladiator (2000) with Russell Crowe who was in...\nL.A. Confidential (1997) with Jane Russell who was in...\nNuovo Cinema Paradiso (1988) with Simone Signoret who was in...\nLes diaboliques (1955) with Charles Vanel who was in...\nLe salaire de la peur (1953) with Seguna\n");
        
        // testing two actors who do not have a graph
        std::string result2;
        result2 = data1.findRelationship("Sahar Kave", "Seguna");
        REQUIRE(result2 == "Didn't find a path.\n");
        
        // testing two actors who are not in the map
        std::string result3;
        result3 = data1.findRelationship("Kevin Bacon", "Nicki Minaj");
        REQUIRE(result3 == "Kevin Bacon is unknown!\nNicki Minaj is unknown!\n");
        
    }
     

}


