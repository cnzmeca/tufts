/*
 * simlines.c
 * by Christian Zinck and Josh Mitchell. 2/1/18
 * HW 1: FilesNPix
 *
 * A program that reads in any number of files from the command line and detects
 * which lines in which files are similar to eachother.
 */
#include <stdio.h>
#include <stdlib.h>
#include <readaline.h>
#include <string.h>
#include <table.h>
#include <seq.h>
#include <atom.h>

struct Pair {
        char *fileName;
        int lineNum;
};

Table_T makeTable(int, char *[]);
void modifySeq(char *, int, Seq_T);
char *parseString(char *);
void print(const void *, void **, void *);
void freeTable(const void *, void **, void *);

int main(int argc, char *argv[])
{
        
        Table_T data = makeTable(argc, argv); 
        void (*print_ptr)(const void *, void **, void *) = &print;
        Table_map(data, print_ptr, NULL);
        void (*free_ptr)(const void *, void **, void *) = &freeTable;
        Table_map(data, free_ptr, NULL);
        Table_free(&data);
        return EXIT_SUCCESS;
}

/*
 * makeTable reads the files from the command line arguments line by line and
 * stores the lines as the keys in a table with sequences of struct Pair's as
 * values. The table is returned by the function.
 *
 * Parameters:
 *         argc - number of command line arguments.
 *         argv - array containing c string command line arguments. 
 */
Table_T makeTable(int argc, char *argv[])
{
        Table_T data = Table_new(100, NULL, NULL);
        for (int i = 1; i < argc; ++i) {
                FILE *fp = fopen(argv[i], "r");
                if (fp == 0) {
                        fprintf(stderr, "File could not be opened.\n");
                        exit(EXIT_FAILURE);
                }
                int lineNum = 1;
                char *sentence = " ";
                while (sentence != NULL) {
                        readaline(fp, &sentence);
                        if (sentence == NULL) {
                                break;
                        }
                        
                        char *cleanSentence = parseString(sentence);
                        const char *atom = Atom_string(cleanSentence);
                        
                        Seq_T sequence = Table_get(data, (void *)atom);
                        if (sequence != NULL) {
                                modifySeq(argv[i], lineNum, sequence); 
                        } else {
                                Seq_T seq = Seq_new(10);
                                modifySeq(argv[i], lineNum, seq);
                                Table_put(data, (void *)atom, (void *)seq);
                        }
                        ++lineNum;
                        free(sentence);
                        free(cleanSentence);        
                }
                sentence = NULL;
                fclose(fp);
        }
        return data;
}

/*
 * modifySeq takes a sequence from the table and adds a new struct Pair to it.
 * The struct's data members are the given file name and line number pair.
 *
 * Parameters:
 *         fName - a file name to be assigned as the struct's data member.
 *         lNum - a line number to be assigned as the struct's data member.
 *         seq - the sequence to which the struct is added.
 */
void modifySeq(char *fName, int lNum, Seq_T seq)
{
        struct Pair *p = malloc(sizeof(*p));
        if (p == NULL) {
                fprintf(stderr, "Failed to malloc.\n");
                exit(EXIT_FAILURE);
        }
        p->fileName = fName;
        p->lineNum = lNum;

        void *sp = p;
        Seq_addhi(seq, sp);
}

/*
 * parseString takes a c string and lowercases all letters, removes non
 * alphanumeric characters (excluding underscore) and eliminates excess
 * whitespace and returns the resulting string.
 *
 * Parameters:
 *         string - the string to parse.
 */
char *parseString(char *string)
{
        size_t size = strlen(string);
        char *rString = malloc(size + 1);
        if (rString == NULL) {
                fprintf(stderr, "Failed to malloc.\n");
                exit(EXIT_FAILURE);
        }
        char ch = ' ';
        int rsI = 0;
        int sI = 0;
        while (ch != '\0') {
                ch = string[sI];
                if (ch >= 65 && ch <= 90) {
                        rString[rsI] = ch + 32;
                        ++rsI; 
                } else if ((ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57)) {
                        rString[rsI] = ch;
                        ++rsI;
                } else if (ch == 95 || ch == '\n') {
                        rString[rsI] = ch;
                        ++rsI;
                } else if (ch == 32 && (rsI != 0) && rString[rsI - 1] != 32) {
                        rString[rsI] = ch;
                        ++rsI;
                } else if (ch == 0) {
                        break;
                } else if (rString[rsI - 1] != 32) {
                        rString[rsI] = 32;
                        ++rsI;
                }
                ++sI;
        }
        rString[rsI] = '\0';
        return rString;
}
/*
 * print is a mapping function that prints all of the similar lines with the
 * filename and line number combinations in the specified format. It also frees all
 * of the
 * allocated data.
 *
 * Parameters:
 *         key - the key representing the sentence of the current table element.
 *         value - the value representing the sequence of the current table element.
 *         cl - a variable that can be used to take additional infortmation.
 */
void print(const void *key, void **value, void *cl)
{
        (void) cl; 
        Seq_T seq = *value;
        int seqlen = Seq_length(seq);
        if (seqlen > 1 && strcmp(key, "\n") != 0) {
                printf("%s", (char *)key);
                for (int i = 0; i < seqlen; ++i) {
                        struct Pair *p = Seq_get(seq, i);
                        printf("%-20.20s %7d\n", p->fileName, p->lineNum);
                }
                printf("\n");
        }
}
/* 
 * freeTable is a mapping function that frees all of the memory in use at the end of
 * the function.
 *
 * Parameters:
 *         key - the key representing the sentence of the current table element.
 *         value - the value representing the sequence of the current table element.
 *         cl - a variable that can be used to take additional infortmation.
 */
void freeTable(const void *key, void **value, void *cl)
{
        (void) cl;
        (void) key;
        Seq_T seq = *value;
        int seqlen = Seq_length(seq);
        for (int i = 0; i < seqlen; ++i) {
                struct Pair *sp = Seq_get(seq, i);
                free(sp);
        }
        Seq_free(&seq);
}
