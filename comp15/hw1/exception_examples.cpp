/*
 * First Exception examples.
 *
 * Mark A. Sheldon, UMass Lowell, Fall 2011
 */

#include <iostream>
#include <stdexcept>

#include "PointClass.h"

using namespace std;

void generateException(string exceptionName)
     throw(int, Point, string, invalid_argument, logic_error);

void generateException(string exceptionName)
     throw(int, Point, string, invalid_argument, logic_error)
{
     if (exceptionName == string("int"))
	  throw -1;
     else if (exceptionName == string("Point"))
	  throw Point(-100, 100);
     else if (exceptionName == string("invalid_argument"))
	  throw invalid_argument("bad arg!");
     else if (exceptionName == string("string"))
	  throw string("I'm just a string");
     else if (exceptionName == string("logic_error"))
	  throw logic_error("Bud Lojack");
     else if (exceptionName == string("range"))
          throw out_of_range("Value out of range");

     cout << "Have a nice day!" << endl;
}

template<typename T>
void reportException(string msg, T const &val)
{
     cerr << msg << val << endl;
}

int main(int argc, char *argv[])
{
     string exceptionName;

     // Not using command line arguments
     (void) argc;
     (void) argv;

     cout << "Exception:  ";
     cin >> exceptionName;

     try {
	  generateException(exceptionName);
     } catch (int &n) {
	  reportException("Integer caught:  ", n);
     } catch (Point &p) {
	  p.print();      // prints to stdout :-(
	  cout << endl;
	  throw;
     } catch (logic_error &le) {
	  reportException("Logic error caught:  ", le.what());
     } catch (...) {
	  reportException("Exception, but I don't know what it is", "");
     }
     
     cout << "main() is done" << endl;

     return 0;
}
