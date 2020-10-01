/*
 *  runner.cpp
 *  PeanutOlympics
 *
 *  Created by Chris Gregg on 1/31/14.
 *  Copyright (c) 2014 Chris Gregg. All rights reserved.
 *
 *  Reorganized slightly by Mark A. Sheldon, fall 2015
 *  and by Erica Schwartz, fall 2016
 *  Solution by Mark A. Sheldon, Tufts University, fall 2015
 */

#include <iostream>
#include "Runner.h"

using namespace std;

Runner::Runner()
{
        name = "";
        time = 0;
}
Runner::Runner(string runnerName, int timeInSeconds)
{
        name = runnerName;
        time = timeInSeconds;
}
        
string Runner::getName()
{
        return name;
}

int Runner::getTime()
{
        return time;
}

void Runner::setName(string runnerName)
{
        name = runnerName;
}

void Runner::setTime(int timeInSeconds)
{
        time = timeInSeconds;
}

bool Runner::isFasterThan(Runner anotherRunner)
{
        return time <= anotherRunner.time;
}
