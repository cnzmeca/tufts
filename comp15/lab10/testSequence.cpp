/*
 * A simple test program for the Sequence template instantiated for
 * integers.  This code tests 
 *      - the copy constructor
 *      - the assignment operator 
 *      - the subscript ([ ]) operator for reading only
 *      - addAtBack()
 *      - removeFromBack()
 *      - size()
 *
 * Added a test for a simple structs.  Can push a bunch of Dog
 * instances onto a sequence and print the result.
 *
 * Author:  Mark A. Sheldon, Tufts University, Fall 2016
 */
#include <iostream>

#include "Sequence.h"

using namespace std;


/*
 * A struct that represents dogs.
 * This illustrates that the queue implementation can be used
 * for more than just basic types like int, double, etc.
 */
struct Dog
{
        string name;
        string owner;
};

/*
 * You can overload the stream insertion operator to make printing
 * easier on your own types!
 * This function says that if someone wants to print a dog using an
 * output stream, here's what you do.
 */
ostream &operator<<(ostream &s, Dog d)
{
        s << "[Dog \"" << d.name << "\" owned by \"" << d.owner << "\"]";
        return s;
}

/*
 * A function that prints any sequence as long as the 
 * element type is printable.
 */
template<typename T>
void printSequence(Sequence<T> s)
{
        int size = s.size();

        for (int i = 0; i < size; ++i)
                cout << s[i] << endl;
}

/*
 * Test sequences on integers
 */
void testInts()
{
        Sequence<int> nums(5);
        int num;
        
        // Read in numbers from standard input until EOF
        while (cin >> num)
                nums.addAtBack(num);

        cout << "Original sequence:"  << endl;
        printSequence(nums);

        // Test copy constructor
        Sequence<int> nums2(nums);
        cout << "Copied sequence:"  << endl;
        printSequence(nums2);

        // Test assignment operator
        // Remove last element from nums so the answer is different
        // from above.
        nums.removeFromBack();

        Sequence<int> nums3;
        nums3 = nums;
        cout << "Sequence after removing an element and assigning:"  << endl;
        printSequence(nums3);

        nums3 = nums2;
        cout << "Sequence after assigning from full copy:"  << endl;
        printSequence(nums3);
}

/*
 * Test sequences on dogs
 * Not very thorough.  Feel free to add more.
 */
void testDogs()
{
        Dog testDogs[] = {{"Fido",       "Sam"},
                          {"Sport",      "Jim"},
                          {"Tron",       "Pam"},
                          {"Longfellow", "Henry"},
                          {"Harvey",     "Alegra"},
                          {"Fluffy",     "Hagrid"}};
        // This trick only works for local arrays!
        int numDogs    = sizeof(testDogs) / sizeof(Dog);

       	Sequence<Dog> dogs(numDogs);
	for (int i  = 0; i < numDogs; i++)
	{
		dogs.addAtBack(testDogs[i]);
		cout << dogs[i] << endl;
	}
}

int main()
{
        //testInts();
        // TODO:  Student fills uncomments this line when ready.
        testDogs();

        return 0;
}
