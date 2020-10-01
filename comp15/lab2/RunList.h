//
//  RunList.h
//  PeanutOlympics
//
//  Created by Chris Gregg on 1/31/14.
//  Copyright (c) 2014 Chris Gregg. All rights reserved.
//
//  Changelog:
//    2015-09-11 msheldon 
//               Reorganized to make node struct private, 
//               changed head/tail to front/back,
//               made getters for front/back and insertBefore/insertAfter private
//               added getFirst/getLast for client access
//    2016-09-05 eschwa08
//               made list singly-linked
//

#ifndef __OrderedRunners__RunList__
#define __OrderedRunners__RunList__

#include <iostream>
#include "Runner.h"

using namespace std;

class RunList
{
public:
        RunList();
        ~RunList();

        bool   isEmpty      ();
        void   insertInOrder(string runnerName, int runnerTime);
        void   printList    ();
        Runner getFirst     ();
        Runner getLast      ();

private:
        struct RunnerNode {
                Runner      aRunner;
                RunnerNode *next;
        };

        RunnerNode *front;

        RunnerNode *getFront       ();
        RunnerNode *getBack        ();
        void        insertIntoEmpty(RunnerNode *newNode);
        void        insertBefore   (RunnerNode *aNode, RunnerNode *newNode);
        void        insertAfter    (RunnerNode *aNode, RunnerNode *newNode);
        void        deleteFront    ();
        RunnerNode *getTemp	   (RunnerNode *aNode, RunnerNode *currNode);
	void        clearNodeData  (RunnerNode *aNode);
        RunnerNode *newRunnerNode  (string name, int time);
};

#endif /* defined(__OrderedRunners__RunList__) */
