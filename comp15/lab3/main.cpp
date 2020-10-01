/*
 *      main.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      Simple test program that tests the code for the lab.  The
 *      testing is not as thorough as one might like, but it's a
 *      start.  You should extend the CircularSequence tests at
 *      least.  What cases are important to test?
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Updated by Mark A. Sheldon, Tufts University
 *                 Documenation, factored testing into separate
 *                 functions. 
 */

#include <iostream>

#include "CircularSequence.h"
#include "SequenceStack.h"
#include "SequenceQueue.h"

using namespace std;

void testCircularSequence(string songs[], int numSongs);
void testSequenceStack(string songs[], int numSongs);
void testSequenceQueue(string songs[], int numSongs);

int main() 
{
        string songs[10] = {"Song 1", "Song 2", "Song 3", "Song 4", "Song 5",
                            "Song 6", "Song 7", "Song 8", "Song 9", "Song 10"};

        const int numSongs = sizeof(songs) / sizeof(string);

        testCircularSequence(songs, numSongs);

        // Uncomment each test as you write each part 
        testSequenceStack(songs, numSongs);
        testSequenceQueue(songs, numSongs);

        return 0;
}

/**********************************************************************
 *******************  TEST ONE: Testing Sequence  **********************
 ***********************************************************************/

//
// TODO: Write more tests for testing the sequence.
//       You can use the songs array for your tests.
//
void testCircularSequence(string songs[], int numSongs)
{
        cout << "Testing CircularSequence: \n";

        CircularSequence mySequence(1);

        mySequence.addAtBack("Hello");
        mySequence.addAtBack("World");
        
        cout << "Printing CircularSequence:\n";
        mySequence.printSequence();
}

/**********************************************************************
 **********************  TEST TWO: Testing Stack  **********************
 ***********************************************************************/

void testSequenceStack(string songs[], int numSongs)
{
        cout << "\nTesting SequenceStack: \n";

        SequenceStack myStack;
        myStack.printStack();     // Should print an empty stack

        // add all songs to the stack
        for (int i = 0; i < numSongs; i++) {
                cout << "Adding " << songs[i] << " to playlist.\n";
                myStack.push(songs[i]); 
        }
        myStack.printStack();     // Be sure all songs are there

        // Pop two songs off
        cout << "Playing " << myStack.pop() << endl;
        cout << "Playing " << myStack.pop() << endl;

        cout << "------ Songs remaining on Stack Playlist: \n";
        myStack.printStack();
}

/**********************************************************************
 ********************  TEST THREE: Testing Queue  **********************
 ***********************************************************************/        

void testSequenceQueue(string songs[], int numSongs)
{
        cout << "\nTesting SequenceQueue: \n";

        SequenceQueue myQueue;
        myQueue.printQueue();     // Should print empty queue

        // put all songs in the queue
        for (int i = 0; i < numSongs; i++) {
                cout << "Adding " << songs[i] << " to playlist.\n";
                myQueue.enqueue(songs[i]); 
        }
        myQueue.printQueue();     // Should print songs in order

        // Dequeue a couple and be sure they are first ones that were
        // added. 
        cout << "Playing " << myQueue.dequeue() << endl;
        cout << "Playing " << myQueue.dequeue() << endl;
        cout << "------ Songs remaining on Queue Playlist: \n";       

        // Remaining songs should still be there in order
        myQueue.printQueue();
}
