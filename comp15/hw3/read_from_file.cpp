/*
 * read_from_file.cpp
 *
 * Author:  Mark A. Sheldon, Tufts University, Fall 2016
 *
 * A program to illustrate basic file input.
 *
 * Invoke the program like this:
 *
 *      read_from_file filename
 *
 * and it will copy the contents of filename to standard output (cout)
 * one string per line, then it will start copying from standard input
 * (cin).  You can stop it by typing Control-d.
 *
 * You can also concatenate the strings of two files like this:
 *
 * read_from_file file1 < file2
 *
 *
 * Notes:
 *      - Don't forget to include fstream.
 *
 *      - When you pass or return input and output streams, you should
 *        always do so using call-by-reference (CBR).  In C++ this is
 *        usually done using C++ reference parameters, as shown
 *        below.  You can tell a parameter is a reference parameter by
 *        the presence of the & before the parameter name.
 *
 *      - If a function is going to manipulate an input stream, and
 *        one those streams is cin, then the function has to take a
 *        reference to a value of type istream.  You can then pass it
 *        cin or an ifstream.
 * 
 */
#include <iostream>
#include <fstream>

using namespace std;

void usage_abort(string program_name);
void copy_strings_from(istream &infile);

int main(int argc, char *argv[])
{
        string   filename;
        ifstream input;

        // Make sure we got 1 command-line argument:  the file name
        if (argc != 2)
                usage_abort(argv[0]);

        filename = argv[1];

        // Try to open input file.  Terminate on failure.
        input.open(filename);
        if (not input.is_open()) {
                cerr << "Unable to open " << argv[0] << endl;
                return 1;
        }
        copy_strings_from(input);
        input.close();

        // Now copy from standard input
        copy_strings_from(cin);

        return 0;
}

/*
 * Copy each string of non-whitespace characters from the given input
 * stream onto standard output (cout), one string per line.
 */
void copy_strings_from(istream &infile)
{
        string s;
        for (infile >> s; not infile.eof(); infile >> s)
                cout << s << endl;
}

/*
 * Abort the program with an error message describing correct program
 * usage.
 */
void usage_abort(string program_name)
{
        cerr << "Usage:  " << program_name << " filename" << endl;
        exit(1);
}
