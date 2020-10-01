//
//  peanutOlympics.cpp
//
//  Created by Chris Gregg on 1/31/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//

#include <iostream>
#include "RunList.h"

int main()
{
        string runnerNames[10] = {"Snoopy", "Charlie Brown", "Linus", "Lucy",
                                  "Peppermint Patty", "Woodstock", "Schroeder",
                                  "Sally", "Pig Pen", "Marcie"};
        int runnerTimes[10]    = {1000, 1800, 1700, 1850,
                                  1200, 1500, 1100,
                                  1200, 1250, 1720};
        RunList theRunList;
        
        for (int index = 0; index < 10; index++) {
                theRunList.insertInOrder(runnerNames[index],
                                         runnerTimes[index]);
        }
        
        cout << "The winner was "  << theRunList.getFirst().getName()
             << " with a time of " << theRunList.getFirst().getTime()
             << " seconds" << "\n\n";

        cout << "The results are:\n";
        theRunList.printList();
        cout << "\n";

        return 0;

}
