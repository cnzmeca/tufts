/* 
 * Simple Hookbook test.
 * - Adds a bunch of pirates to the Hookbook, 
 * - makes every pirate have all previous priates as friends
 *   (e. g., pirate number 4 is friends with pirates 0, 1, 2, 3)
 * - prints result
 *
 * This should NOT be the only test you use, and it should certainly 
 * not be the first test.
 * 
 * Comment out "run_final_lab_test();" and insert your own test functions
 * first.
 */

#include <iostream>
#include <string>

#include "Hookbook.h"

using namespace std;

void run_final_lab_test();


int main()
{
	
        run_final_lab_test();
        return 0;
}

void test()
{
	Hookbook hb;
	hb.addPirate(0, "Blackbeard");
}
void run_final_lab_test()
{
        string   color[] = {"red",       "blue",         "grey", "white", 
                            "orange",    "burnt sienna", "puse", "black",
                            "cerulean",  "dandelion",    "cyan", "mauve"};
        Hookbook hb;
        int      size = sizeof(color) / sizeof(string); // Tricky!  Only works
                                                        // for local arrays.
    
        for (int i = 0; i < size; i++) {
                hb.addPirate(i, color[i] + " beard");
        }
        for (int pirateID = 0; pirateID < size; pirateID++) {
                for (int friendID = 0; friendID < pirateID; friendID++) {
                        if (pirateID != friendID) {
                                hb.addFriend(pirateID, friendID);
                        }
                }
        }
        hb.print();
}
