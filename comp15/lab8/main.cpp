/*
 * imageEngine
 *
 *     Created on:  Mar 29, 2015
 *         Author:  Chris Gregg
 *  Re-written by:  Mark A. Sheldon, Fall 2016
 *                  Factored out argument collection and image transformation.
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "ImageEngine.h"

using namespace std;

/*
 * A struct for holding the arguments.
 */
struct Arguments {
        string infilename;
        string outfilename;
        char   command;
        int    scaleFactor;
};



const string simpleCommands = "mfp";
const string requireScale   = "ud";

void      usageAbort(string programName);
Arguments getArguments(int argc, char *argv[]);
Arguments getArgumentsInteractively();
void      performTransform(char command,
                           int scaleFactor,
                           ImageEngine &imageEng);

/*
 * Return true if c is in s, false otherwise.
 */
static inline bool in(char c, string s)
{
        return s.find(c) != string::npos;
}

int main(int argc, char *argv[])
{
        Arguments   args = getArguments(argc, argv);
	ImageEngine imageEng;

	imageEng.readImage(args.infilename);
	cout << "Done reading image.\n";

        performTransform(args.command, args.scaleFactor, imageEng);

	imageEng.save(args.outfilename);

	cout << "To see your new image, type the following:\n";
	cout << "  eog " << args.outfilename << "\n";

	return 0;
}

/*
 * Retrieve the arguments that define the transformation:
 *
 *      input file, output file, transform command, and possibly scale factor
 *
 * Gets them from the command line if there is something there, otherwise
 * expects the user to enter them interactively.
 */
Arguments getArguments(int argc, char *argv[])
{
        Arguments args;

        if (argc == 1)
                return getArgumentsInteractively();

        if (not (argc >= 4 and argc <= 5 and strlen(argv[3]) == 1))
                usageAbort(argv[0]);

        args.infilename  = argv[1];
        args.outfilename = argv[2];
        args.command     = argv[3][0];
                
        if (in(args.command, requireScale) and argc == 5) {
                try {
                        args.scaleFactor = stoi(argv[4]);
                } catch (...) {
                        usageAbort(argv[0]);
                }
        } else if (in(args.command, simpleCommands) and argc == 4) {
                args.scaleFactor = 0;   // Shouldn't matter
        } else {
                usageAbort(argv[0]);
        }
        return args;
}

/*
 * Gets the transformation arguments by prompting user and reading
 * from standard input.
 */
Arguments getArgumentsInteractively()
{
        Arguments args = {"", "", '?', 0};

        

	cout << "Filename: ";
	cin  >> args.infilename;

	cout << "Scale up or down, mirror,\n";
	cout << "flip, or psychedelic? (u/d/m/f/p): ";
	cin  >> args.command;
	args.command = tolower(args.command);

	if (args.command == 'u' or args.command == 'd') {
		cout << "Scale factor: ";
		cin  >> args.scaleFactor;
	}
	cout << "Filename for save? ";
	cin  >> args.outfilename;

        return args;
}

/*
 * Transform the image.  
 * Uses command to call appropriate tranformation function.
 */
void performTransform(char command, int scaleFactor, ImageEngine &imageEng)
{
	switch (command) {
	case 'u':
		imageEng.scale_up(scaleFactor);
		break;
	case 'd':
		imageEng.scale_down(scaleFactor);
		break;
	case 'm':
		imageEng.mirror();
		break;
	case 'f':
		imageEng.flip();
		break;
	case 'p':
		imageEng.psychedelic();
		break;
	default:
		cerr << "Not a recognized command:  " << command << endl;;
	}
}

/*
 * Print a usage message and exit the program with non-zero status.
 */
void usageAbort(string programName)
{
        cerr << "Usage:  " << programName
             << " inputfile outputfile command" << endl
             << "        " << "where command is one of "
                           << simpleCommands << endl
             << "   or:  " << programName
             << " inputfile outputfile command scalefactor" << endl
             << "        " << "where command is one of "
                           << requireScale << endl;
        exit(1);
}
