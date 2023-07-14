/*
queue.cpp
*/

#include "queue.h"

//Constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    // *** You complete **** CHECKPOINT 3
    // need storage!!
    // dynamically allocating an array of Locations for the queue
    contents = new Location[maxlen];

}

//Destructor. releases resources. C++ will call it automatically.
Queue::~Queue() {
    // *** You complete **** CHECKPOINT 3
    // deallocating memory
    delete [] contents;

}

//Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {

    // *** You complete **** CHECKPOINT 3
    contents[tail] = loc; // adding Location to back of list
    tail += 1; // incrementing tail



}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {

    // *** You complete **** CHECKPOINT 3
    Location x; 
    x = contents[head]; // assigning x to the oldest Location
    head += 1; // incrementing head
    return x; 
    



}

//Is this Queue empty? (did we extract everything added?)
//This is complete, you don't need to change it.
bool Queue::is_empty() {
    return head == tail; // queue is empty if head is equal to tail
}

