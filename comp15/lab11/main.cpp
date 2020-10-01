/*
 * Comp 15 Hash Table Lab
 *
 * main.cpp --- tests the two approaches to collisions and two
 * different hash functions using sameple song data.
 *
 * Songs chosen by Rebecca Newman
 * Song tempi from songbpm.com and www.bpmdatabase.com
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2017
 *     based on prior labs by Ben Hescott, Bruce Molay, Chris Gregg, 
 *     and work by Rebecca Newman.
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

#include "FunkeyTable.h"
using namespace std;


struct SongData {
        string   title;
        SongInfo info;
};

void run_tests(string testName, SongData songs[], int numSongs,
               FunkeyTable::HashFunction hashFunction);


int main()
{
        SongData songs[] = {
                            {"Stayin' Alive",     {3, 104}},
                            {"Funky Town",        {5, 128}},
                            {"Disco Inferno",     {6, 129}},
                            {"Night Fever",       {20, 109 }},
                            {"Last Dance",        {21, 126}},
                            {"I Will Survive",    {1, 116}},
                            {"Car Wash",          {27, 115}},
                            {"Billie Jean",       {30, 117}},
                            {"Get Up and Boogie", {13, 105}},
                            {"YMCA",              {7, 127}}
                           };
        int numSongs = sizeof(songs) / sizeof(SongData);

        run_tests("Bad Hash Function", songs, numSongs,
                  FunkeyTable::BAD_HASH_FUNCTION);

        run_tests("Good Hash Function", songs, numSongs,
                  FunkeyTable::GOOD_HASH_FUNCTION);

        return 0;
}

/*
 *  Test the two approaches to collision handling with an array of
 *  SongData and a specified hash function.
 *  
 *  Approach:
 *       Insert the data, keeping stats
 *       Report test results
 *       Print the hash tables
 *
 *  This function is too long and needs to be broken up.
 *  It would be reasonable to separate out the reporting code.
 *  Maybe next semester...
 */
void run_tests(string testName, SongData songs[], int numSongs,
               FunkeyTable::HashFunction hashFunction)
{
        FunkeyTable songDB;
        
        int maxProbeCollisions = 0;
        int maxChainCollisions = 0;
        int totProbeCollisions = 0;
        
        int collisions, i;
        
        cout << testName << endl;
	cout << "inserting keys:";
        for (i = 0; i < numSongs; ++i) {
                cout << " \"" << songs[i].title << "\"";
                collisions = songDB.insertProbing(songs[i].title,
                                                  songs[i].info,
                                                  hashFunction);
                totProbeCollisions += collisions;
                maxProbeCollisions = max(maxProbeCollisions, collisions);
                collisions = songDB.insertChaining(songs[i].title,
                                                   songs[i].info,
                                                   hashFunction);	
        //      if ( colls > maxC ) maxC = colls;
        }
        cout << endl << "Results of Your Code:" << endl;

        printf("     Linear Probing: reprobes = %d  max lookup = %d\n",
               totProbeCollisions, maxProbeCollisions);

        // For chaining, the maximum bucket size is 1 more than the
        // number of collisions reported, because the collisions is
        // the size of the bucket list before insertion
        printf("           Chaining: reprobes = 0  max bucket size= %d\n",
               maxChainCollisions + 1);
        cout << endl;
        cout << "Your Tables:" << endl;

        songDB.print();
        cout << endl;
}
