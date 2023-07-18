// ITP 365 Spring 2023
// HW06
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#include "catch.hpp"

#include "Cards.h"
#include "ITPVector.hpp"

// Helper function declarations (don't change this)
extern bool CheckTextFilesSame(const std::string& fileNameA,
	const std::string& fileNameB);

// Your tests
TEST_CASE("Vector tests", "[student]") 
{
	// Complete tests are worth 2 points for each test
	
	SECTION("Default constructor, size, capacity, and destructor")
	{
        // declaring vector with default constructor
        ITPVector<int> test = ITPVector<int>();
                
		REQUIRE(test.size() == 0); // checking size
        REQUIRE(test.capacity() == 10); // checking capacity
        
	}

	SECTION("Parameterized constructor, size, capacity, and destructor")
	{
        // declaring vector with the parameterized constructor
        ITPVector<int> test = ITPVector<int>(20);
        
        REQUIRE(test.size() == 0); // checking size
        REQUIRE(test.capacity() == 20); // checking capacity
        
		
	}

	SECTION("Push_back x1, back, pop_back, destructor")
	{
        // declaring vector using default constructor
        ITPVector<int> test = ITPVector<int>();
        
        // adding a value of 2
        test.push_back(2);
        REQUIRE(test.back() == 2); // checking that the last element is 2
        REQUIRE(test.size() == 1); // checking size of vector
        
        test.pop_back(); // removing the last element of the vector
        REQUIRE(test.size() == 0); // checking that size is 0
        REQUIRE(test.empty()); // checking that the vector is empty
		
	}

	SECTION("Push_back x3, operator[], destructor")
	{
        // declaring vector using default constructor
        ITPVector<int> test = ITPVector<int>();
        
        // adding 3 values to the vector
        test.push_back(2);
        test.push_back(4);
        test.push_back(6);
        
        // using operator[] to verify the values
        REQUIRE(test[0] == 2);
        REQUIRE(test[1] == 4);
        REQUIRE(test[2] == 6);
        
		
	}

	SECTION("Push_back (over capacity), size, capacity, destructor")
	{
        // declaring vector using parameterized constructor
        ITPVector<int> test = ITPVector<int>(3);
        
        // adding 4 elements to the vector (over capacity)
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        test.push_back(4);
        
        REQUIRE(test.size() == 4); // checking size
        REQUIRE(test.capacity() == 6); // checking that the capacity changed
        
		
	}

	SECTION("Push_back (over capacity), operator[], destructor")
	{
        // declaring vector using parameterized constructor
        ITPVector<int> test = ITPVector<int>(3);
        
        // adding 4 values to the vector (over capacity)
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        test.push_back(4);
        
        // using [] to verify all of the values
        REQUIRE(test[0] == 1);
        REQUIRE(test[1] == 2);
        REQUIRE(test[2] == 3);
        REQUIRE(test[3] == 4);
        
		
	}

	SECTION("Push_back, pop_back, back, operator[], exceptions")
	{
        // declaring vector using parameterized constructor
        ITPVector<int> test = ITPVector<int>(3);
        
        // try catch statements to catch the error in each scenario
        
        // testing back function
        try {
            test.back(); // attempting to get the last element of the vector
        } catch (const std::out_of_range& e) {
            REQUIRE(true);
        }
        
        // testing pop_back function
        try{
            test.pop_back(); // attempting to remove the last element of the vector
        } catch (const std::out_of_range& e) {
            REQUIRE(true);
        }
        
        // adding 1 element to the vector
        test.push_back(1);
        
        // testing out of bounds indices for operator []: less than 0
        try{
            int i = test[-1]; // testing out of bounds index
        } catch (const std::out_of_range &e) {
            REQUIRE(true);
        }
        
        // testing out of bounds indices for operator []: greater than or equal to the size of vector
        try{
            int i = test[5]; // testing out of bounds index
        } catch (const std::out_of_range& e) {
            REQUIRE(true);
        }
        
	}

	SECTION("Push_back (over capacity), operator[] (with assignment), destructor")
	{
        // declaring vector with parameterized constructor
        ITPVector<int> test = ITPVector<int>(3);
        
        // adding 4 values to the vector
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        test.push_back(4);
        
        // using [] operator for assignment
        test[0] = 0;
        test[1] = 1;
        test[2] = 2;
        test[3] = 3;
        
        // verifying the values at each of the indices
        REQUIRE(test[0] == 0);
        REQUIRE(test[1] == 1);
        REQUIRE(test[2] == 2);
        REQUIRE(test[3] == 3);
        
	}

	SECTION("Clear")
	{
        // declaring a vector with parameterized constructor
        ITPVector<int> test = ITPVector<int>(3);
        
        // adding 2 elements to the vector
        test.push_back(1);
        test.push_back(2);
        
        // clear function
        test.clear();
        
        // checking size and making sure that vector is empty
        REQUIRE(test.size() == 0);
        REQUIRE(test.empty());
        
		
	}
/*
	SECTION("Destructor")
	{
		
		// TODO: Tests go here
	}
 */

	SECTION("Copy constructor deep copies")
	{
        // declaring vector with parameterized constructor
        ITPVector<int> test = ITPVector<int>(5);
        
        // adding 4 values to the vector
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        test.push_back(4);
        
        // using copy constructor to declare another vector
        ITPVector<int> testCopy = ITPVector<int>(test);
        
        // checking the size of vector and elements of the copy vector
        REQUIRE(testCopy.size() == 4);
        REQUIRE(testCopy[0] == 1);
        REQUIRE(testCopy[1] == 2);
        REQUIRE(testCopy[2] == 3);
        REQUIRE(testCopy[3] == 4);
        
		
	}

	SECTION("Assignment operator deep copies")
	{
        // declaring a vector using the parameterized constructor
        ITPVector<int> test = ITPVector<int>(5);
        
        // adding 4 values to the vector
        test.push_back(1);
        test.push_back(2);
        test.push_back(3);
        test.push_back(4);
        
        // copying the vector using the assignment operator
        ITPVector<int> testCopy = test;
        
        // checking size of vector and the values of each element
        REQUIRE(testCopy.size() == 4);
        REQUIRE(testCopy[0] == 1);
        REQUIRE(testCopy[1] == 2);
        REQUIRE(testCopy[2] == 3);
        REQUIRE(testCopy[3] == 4);
        
		
	}

	// Complete tests for this section is worth 24 points
}


