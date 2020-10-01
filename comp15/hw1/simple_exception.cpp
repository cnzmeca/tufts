/*
 * Here's how you can throw an exception.  There's a lot more one can 
 * learn about exceptions, but this is a basic example.  In C++, you
 * "throw" an exception, and you can give "throw" any type of value.
 * There are some built-in classes that represent exceptions, and 
 * we're using "runtime_error" here.  We call that constructor with a
 * string that represents the message associated with the exception.
 *
 * Programs can choose to handle exceptions using a "try" statement,
 * but if they don't, the program will terminate with an unhandled
 * exception, and the message will print out.
 *
 * For no good reason, I'm also demonstrating a weird feature of C++:
 * if you put two string constants one after the other in a source
 * file with no intervening operator, the strings are concatenated
 * together to make one string constant.  It can be handy if you have
 * to spread a string constant across multiple lines, e. g., if the
 * string is very long (like a URL).
 *
 * Mark A. Sheldon, Tufts University, Fall 2015
 *
 */

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int crash()
{
        throw runtime_error("Crashing!"
                            "  oh no!");
        return 12;
}

int main()
{
        cout << "Result:  " << crash() << endl;
        cout << "This won't print" << endl;
        return 0;
}
