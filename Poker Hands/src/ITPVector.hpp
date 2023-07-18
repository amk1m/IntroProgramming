// ITP 365 Spring 2023
// HW06
// Name: Audrey Kim
// Email: amkim@usc.edu
// Platform: Mac

#pragma once
#include <sstream>
#include <ostream>
#include <stdexcept>

template <typename T>
class ITPVector
{
	const unsigned INITIAL_CAPACITY = 10;
	const unsigned CAPACITY_MULTIPLIER = 2;
public:
	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of INITIAL_SIZE and a size of 0.
	// It also dynamically allocates the underlining array data
	// Input: None
	// Returns: Nothing
	ITPVector()
	{
		// default constructor
        mSize = 0; // set size of vector to 0
        mCapacity = INITIAL_CAPACITY; // set capacity to INITIAL_CAPACITY
        mArrayData = new T[mCapacity]; // dynamically allocating an array of size INITIAL_CAPACITY
	}

	// Function: Constructor
	// Purpose: Initializes the ITP vector to have a
	// capacity of inputted value.
	// It also dynamically allocates the underlining array data
	// Input: Unsigned integer
	// Returns: Nothing
	ITPVector(unsigned inCapacity)
	{
		// parameterized constructor
        mSize = 0; // set size of vector to 0
        mCapacity = inCapacity; // set capacity to the capacity given in constructor
        mArrayData = new T[mCapacity]; // dynamically allocating an array of size given in constructor
	}

	// Function: Copy Constructor
	// Purpose: Initializes the ITP vector to have a
	// copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector(const ITPVector<T>& other)
	{
        // 1. Set the new capacity to the other’s size and size = 0
        mCapacity = other.size();
        mSize = 0;
        
        // 2. Create a new underlying array with the new capacity
        T* newA = new T[mCapacity];
        mArrayData = newA;
        
        // 3. Iterate over the other vector and push_back items to the new vector
        for(unsigned i = 0; i < other.size(); i++){
            this->push_back(other[i]);
        }
        
	}

	// Function: Assignment operator
	// Purpose: Clears the current vector and sets
	// the vector to have a copy of the inputted vector
	// Input: Another ITPVector
	// Returns: Nothing
	ITPVector<T>& operator=(const ITPVector<T>& other)
	{
        // 1. Call the clear function
        clear();
        
        // 2. Delete the current array
        delete [] mArrayData;
        
        // 3. Set the new capacity to the other’s size and size = 0
        mCapacity = other.size();
        mSize = 0;
        
        // 4. Create a new underlying array with the new capacity
        T* newA = new T[mCapacity];
        mArrayData = newA;
        
        // 5. Iterate over the other vector and push_back items to the new vector
        for(unsigned i = 0; i < other.size(); i++){
            this->push_back(other[i]);
        }
        
        // 6. By convention, operator= returns *this
		return *this;
	}

	// Function: Destructor
	// Purpose: Deletes the underlying array and
	// sets size/capacity to zero
	// Input: None
	// Returns: Nothing
	~ITPVector()
	{
		
        // deleting the array
        delete [] mArrayData;
        
        // setting size to 0, capacity to 0, and setting mArrayData to nullptr
        mSize = 0;
        mCapacity = 0;
        mArrayData = nullptr;
        
	}

	// Function: clear
	// Purpose: Emptys the current vector
	// Input: None
	// Returns: None
	void clear()
	{
        // 1. Call delete[] on the underlying array
        delete [] mArrayData;
        
        // 2. Create a new underlying array using the old capacity
        T* newA = new T[mCapacity];
        
        // 3. Set size back to 0
        mSize = 0;
        
	}

	// Function: empty
	// Purpose: Returns true if the vector is empty
	// Input: None
	// Returns: Boolean
	bool empty()
	{
		// if size of vector is 0, return true
        if(mSize == 0){
            return true;
        }
		return false; // vector is not empty
	}
	
	// Function: capacity
	// Purpose: Returns the current capacity of the underlying array data
	// Input: None
	// Returns: Capacity of underlying array data
	unsigned capacity() const
	{
		return mCapacity;
	}

	// Function: size
	// Purpose: Returns the current size of the vector
	// Input: None
	// Returns: Size of vector
	unsigned size() const
	{
		return mSize;
	}

	// Function: data
	// Purpose: Returns the pointer to the underlying array
	// Input: None
	// Returns: T*
	T* data() const
	{
		return mArrayData;
	}

	// Function: Subscript operator (read/write version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	T& operator[](unsigned index)
	{
		// checking to see if the index is out of bounds (either less than 0 or greater than/equal to size)
        if ((index < 0) || (index >= mSize)) {
            throw std::out_of_range("index out of range"); // error
        }
        else {
            return mArrayData[index]; // if index is valid, return the value at that index
        }
		
	}

	// Function: Subscript operator (read-only version)
	// Purpose: Grabs the specified index from vector
	// Causes an error if the index is out of bounds
	// Input: Index to access
	// Returns: Value at index, by reference
	const T& operator[](unsigned index) const
	{
        // checking to see if the index is out of bounds (either less than 0 or greater than/equal to size)
        if ((index < 0) || (index >= mSize)) {
            throw std::out_of_range("index out of range"); // error
        }
        else {
            return mArrayData[index]; // if index is valid, return the value at that index
        }
	}

	// Function: insert_back
	// Purpose: Adds the specified element to the end of the ITPVector
	// It automatically reallocates the underlying array if we are
	// going over capacity
	// Input: Value to add (by const reference)
	// Returns: Nothing
	void push_back(const T& value)
	{
        // at capacity:
        if(mCapacity == mSize){
            
            // 1. Increase the capacity
            mCapacity = mCapacity * CAPACITY_MULTIPLIER;
            
            // 2. Dynamically allocate a new underlying array w/ new capacity
            T* newA = new T[mCapacity];
            
            // 3. Copy the data from the old array to the new array
            for(unsigned i = 0; i < mSize; i++){
                newA[i] = mArrayData[i];
            }
            
            // 4. Delete the old array
            delete [] mArrayData;
            
            // 5. Set your pointer to the new array
            mArrayData = newA;
            
            // 6. Add an element at index size
            mArrayData[mSize] = value;
            
            // 7. Increment size by 1
            mSize += 1;
            
        }
        else{ // if size < capacity
            
            // add the element at index size
            mArrayData[mSize] = value;
            
            // increment size member variable
            mSize += 1;
        }
        
	}

	// Function: get_back
	// Purpose: Returns the current last element in the vector
	// Does not remove this element from the vector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Value at back of vector, by reference
	T& back()
	{
		// if size is 0, throw an error
        if(mSize == 0){
            throw std::out_of_range("no elements in vector"); // error
        }
        else{
            return (*this)[mSize - 1]; // if size is not 0, then return the last element
        }
	}

	// Function: remove_back
	// Purpose: Removes the last element from the ITPVector
	// Causes an error if there are no elements in the vector
	// Input: Nothing
	// Returns: Nothing
	void pop_back()
	{
		// if size is 0, throw an error
        if(mSize == 0){
            throw std::out_of_range("no elements in vector"); // error
        }
        else{
            mSize -= 1; // decrementing the size by 1
        }
	}

	// Function: Output Stream Operator
	// Purpose: Prints the contents of the vector to the provided stream
	// Written in the format of {x, y, ..., z}
	// Input: Stream to write to, vector to write
	// Output: Stream after values are written
	friend std::ostream& operator<<(std::ostream& os, const ITPVector<T>& vector)
	{
        os << "{";
        
        for(unsigned i = 0; i < vector.size(); i++){
            
            // if printing out the last element of the vector, do not print out comma
            if(i == vector.size() - 1){
                os << vector[i];
            }
            else{
                os << vector[i] << ", "; // print out comma after element as long as it is not the last one
            }
        }
        
        os << "}";
        
		return os;
	}
private:
	// defining member variables
    unsigned mCapacity;
    unsigned mSize;
    T* mArrayData;
};
