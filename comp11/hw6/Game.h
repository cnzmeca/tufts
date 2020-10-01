#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

#define FILENAME "highscores.txt"
class Game
{
private:
	// Highscore values
	int *highscoreVals;
	// Highscore names
	string *highscoreNames;
	// Length of highscores
	int highscoresLength;
public:
	// Default constructor
	Game();
	// Destructor
	~Game();
	
	// Reads in highscores.
	void readInHighscores();
	// Writes to highscores. Takes a name and a score
	void writeToHighscores(string, int);
	// Prints highscores
	void printHighscores();
	
};

#endif
