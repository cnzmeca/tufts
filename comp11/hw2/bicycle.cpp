/*
Christian Zinck
COMP11
HW 2
Programming #2
February 9, 2017
*/

/*
Test 1 -
	In: 1001 wheels, -1 frames, 50 links
	Out: 1 bike, 0 wheels, 0 frames, 0 links
Test 2 -
	In: 10 wheels, 60 frames, 300 links
        Out: 5 bikes, 0 wheels, 55 frames, 50 links
Test 3 - 
        In: 2 wheels, 7 frames, 0 links
        Out: 0 bikes, 2 wheels, 7 frames, 0 links
*/
#include <iostream>
using namespace std;

int main()
{
	//Highest accepted value
	const int MAX_VALUE = 1000;
	//Numbers of parts required to make a bike
	const int WHEELS_NEEDED = 2;
	const int FRAMES_NEEDED = 1;
	const int LINKS_NEEDED = 50;
	//Variables used in calculations
	int numWheels, numFrames, numLinks, numBikes;
	//Assigns a value to numWheels
	cout << "How many wheels do you have?" << endl;
	cin >> numWheels;
	if (numWheels < 0 || numWheels > MAX_VALUE)
	{
		cout << "You do not actually have that many wheels. I will assume you have enough wheels for 1 bike." << endl;
		numWheels = WHEELS_NEEDED;
	}
	cout << "You have enough wheels for " << (numWheels / WHEELS_NEEDED) << " bike(s)." << endl;
	//Assigns a value to numFrames
	cout << "How many frames do you have?" << endl;
	cin >> numFrames;
	if (numFrames < 0 || numFrames > MAX_VALUE)
        {
                cout << "You do not actually have that many frames. I will assume you have enough frames for 1 bike." << endl;
       		numFrames = FRAMES_NEEDED;
	}
	cout << "You have enough frames for " << (numFrames / FRAMES_NEEDED) << " bike(s)." << endl;	
	//Assigns a value to numLinks
	cout << "How many links do you have?" << endl;
	cin >> numLinks;
	if (numLinks < 0 || numLinks > MAX_VALUE)
        {
                cout << "You do not actually have that many links. I will assume you have enough links for 1 bike." << endl;
		numLinks = LINKS_NEEDED;
        }
	cout << "You have enough links for " << (numLinks / LINKS_NEEDED) << " bike(s)." << endl;
	//Calculates numBikes
	numBikes = numWheels / WHEELS_NEEDED;
	if ((numFrames / FRAMES_NEEDED) < numBikes)
		numBikes = numFrames / FRAMES_NEEDED;
	if ((numLinks / LINKS_NEEDED) < numBikes)
                numBikes = numLinks / LINKS_NEEDED;
	//Displays all required information
	cout << "I can make you " << numBikes << " bike(s) with " << (numWheels - (numBikes * WHEELS_NEEDED)) << " wheel(s), " <<
	(numFrames - (numBikes * FRAMES_NEEDED)) << " frame(s), and " << (numLinks - (numBikes * LINKS_NEEDED)) <<
	 " link(s) left over for me to keep." << endl;

	return 0;
}
