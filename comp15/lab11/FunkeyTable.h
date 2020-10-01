#ifndef FUNKEYTABLE_H
#define FUNKEYTABLE_H

#include <string>

/*
 * This hash table maps song titles (strings) to information about
 * that song:  the rank of the song on the pop charts and the tempo of
 * the song in beats per minute (bpm).  
 * For the hash table, the song titles are keys and the values are
 * structs containing the chart position and the tempo.
 *
 * (c) Mark A. Sheldon, Tufts University, Spring 2017
 */

struct SongInfo {
        int chartPosition;
        int bpm;

        // Constructors for struct
        SongInfo() 
        {
                chartPosition = bpm = -1;
        }

        SongInfo(int position, int tempo)
        {
                chartPosition = position;
                bpm           = tempo;
        }
};

/*
 * The following type definitions allow us to abstract the FunkeyTable
 * class over the details of the key and value type.
 * In the implementation, the only code that depends on knowing the
 * types is the print function, which could be removed after
 * debugging.  Then we could make this a template!
 */
typedef std::string   KeyType;
typedef SongInfo      ValueType;

class FunkeyTable
{
public:
	FunkeyTable();
	~FunkeyTable();

        enum HashFunction {BAD_HASH_FUNCTION, GOOD_HASH_FUNCTION};

	int insertProbing (KeyType key, ValueType value,
                           HashFunction hashFunction);
	int insertChaining(KeyType key, ValueType value,
                           HashFunction hashFunction);
	void print();

private:
        /*
         * used by the chained version of collision handling
         */
	struct ChainNode {
		KeyType    key;
		ValueType  value;
		ChainNode *next;
	};

        /*
         * used by the table for linear probing
         */
        struct TableEntry {
                bool      isEmpty;
                KeyType   key;
                ValueType value;
        };

        /*
         * Here are the tables themselves.
         * Each is a kind of sequence with a current size.
         * A chaining table is an array of pointers to nodes.
         * A linear probing table is an array of TableEntries.
         */ 
	static const int INITIAL_TABLE_SIZE = 23;
        int currentTableSize;
        int numItemsInTable;

	ChainNode  **chainedTable;
	TableEntry  *linearTable;

        /*
         * Various private helper functions definitions
         */
	void  expand(HashFunction hashFunction);
        void  deleteList(ChainNode *node);
        int   listLength(ChainNode *nodep);
        void  printTableEntry(TableEntry entry);
        void  printChainNode(ChainNode *nodep);
};
#endif	/* FUNKEYTABLE_H */
