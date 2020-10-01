/*
* Christian Zinck and Phong Hoang
* Assignment 5: Code
* 3/30/18
*
* Implements the 6 phases of the binary bomb and their helper functions.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
 * explode_bomb
 * No inputs.
 * Returns void.
 *
 * Explodes the bomb.
 */
void explode_bomb()
{
        printf("The bomb has exploded!");
}

/*
 * strings_not_equal
 * Takes 2 char * as input.
 * Returns an integer truth value.
 *
 * Returns a nonzero number if the 2 inputs are not the same.
 */
int strings_not_equal(char *string1, char *string2)
{   
        return (strcmp(string1, string2) != 0);

} 
/*
 * phase_1
 * Takes a char * as input
 * Returns void.
 *
 * Explodes the bomb unless the given string is equal to the stored string.
 */
void phase_1(char *string1)
{
        char *string2 = "You may charm it with smiles and soap.";
        if (strings_not_equal(string1, string2)) {
                explode_bomb();
        }
}

/*
 * read_six_numbers
 * Takes a char * as input.
 * Returns a pointer to the start of an int array of size 6
 *
 * Gets 6 numbers from the given string and stores them in an array.
 */
int *read_six_numbers(char *string)
{
        int *arr = malloc(6 * sizeof(*arr));
        if (6 != sscanf(string, "%d %d %d %d %d %d", arr, arr + 1, arr + 2,
            arr + 3, arr + 4, arr + 5)) {
                explode_bomb();
        }
        return arr;
}

/*
 * phase_2
 * Takes a char * as input.
 * Returns void.
 *
 * Explodes the bomb unless the given string contains the numbers 1, 6, 11, 16,
 * 21 and 26.
 */
void phase_2(char *string)
{
        int *arr = read_six_numbers(string);
        for (int i = 0; i < 6; i++) {
                if (*(arr + i) != (1 + (5 * i))) {
                        explode_bomb();
                }
        }
        free(arr);
}

/*
 * phase_3
 * Takes a char * as input.
 * Returns void.
 *
 * Explodes unless the given string contains 2 integers, the second of
 * which must be equal to the value contained in the switch case
 * determined by the first interger, which must be between 0 and 7.
 */
void phase_3(char *string)
{
        int num1 = 0, num2 = 0;
        int val;
        if (2 != sscanf(string, "%d %d", &num1, &num2)) {
                explode_bomb();
        }
        // Case specific values were found in objdump
        switch(num1) {
                case 0:
                        val = 833;
                        break;
                case 1:
                        val = 79;
                        break;
                case 2:
                        val = 343;
                        break;
                case 3:
                        val = 227;
                        break;
                case 4:
                        val = 962;
                        break;
                case 5:
                        val = 472;
                        break;
                case 6:
                        val = 645;
                        break;
                case 7:
                        val = 848;
                        break;
                default:
                        explode_bomb();
                        break;
        }

        if (num2 != val) {
                explode_bomb();
        }
}

/*
 * func4
 * Takes an integer pow
 * Returns  an integer
 *
 * Calculates 7^pow recursively.
 */
int func4(int pow)
{
        if (pow == 0) {
                return 1;
        } else {
                return 7 * func4(pow - 1);
        }
}

/*
 * phase_4
 * Takes a char * as input/
 * Returns void.
 *
 * Explodes unless the given string contains 1 integer x such that:
 * 7 ^ x = 5764801
 */
void phase_4(char *string) 
{
        int num = 0;
        int val;

        if (1 != sscanf(string, "%d", &num)) {
                explode_bomb();
        }

        val = func4(num);
        
        // 5764801 = 7^8
        if (val != 5764801) {
                explode_bomb();
        }
}

/*
 * phase_5
 * Takes a char * as input.
 * Returns void.
 *
 * Explodes unless the input is equal to the starting index and sum of the
 * of the array traversal: "13 69".
 */
void phase_5(char *string)
{
        int num1 = 0, num2 = 0;

        // Found in objdump
        int arr[16] = {10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5};
        if (2 != sscanf(string, "%d %d", &num1, &num2)) {
                explode_bomb();
        }

        int counter = 0, total = 0;
        
        // Ensures num1 is inbounds of the array.
        num1 = num1 % 16;
        
        while (num1 != 15) {
                counter++;
                num1 = arr[num1];
                total += num1;
        }

        if (counter != 10 || num2 != total) {
                explode_bomb();
        }
}

/*
 * fun6
 * Takes a struct Node * as input
 * Returns a struct Node *
 *
 * Sorts the linked list that starts at the given struct Node *.
 */
struct Node *fun6(struct Node *start)
{
        struct Node *ret = malloc(sizeof(*ret));
        int last_smallest = 0;
        struct Node *current = ret;
        for (int i = 1; i < 10; i++) {
                struct Node *curr = start;
                int smallest = 1000;
                // Finds next smallest value
                while (curr != NULL) {
                        if (curr->val < smallest && curr->val > last_smallest) {
                                smallest = curr->val;
                        }
                        curr = curr->nxt;
                }
                last_smallest = smallest;

                // Creates node for next smallest value in ret
                struct Node *next = malloc(sizeof(*next));
                next->num = i;
                next->val = smallest;
                current->nxt = next;
                current = next;
        }

        return ret;
}

/*
 * phase_6
 * Takes a char * as input.
 * Returns void.
 *
 * Explodes unless the given string contains 1 integer. The integer must
 * be equal to the 5th value in the sorted linked list: 663.
 */
void phase_6(char *string)
{
        // Found in objdump
        int vals[9] = {860, 248, 181, 761, 465, 811, 762, 370, 663};
        struct Node *start = malloc(sizeof(*start));

        struct Node *curr = start;
        for (int i = 1; i < 10; i++) {
                struct Node *next = malloc(sizeof(*next));
                next->num = i;
                next->val = vals[i-1];
                curr->nxt = next;
                curr = next;
        }
        
        int num = atoi(string);
        start = fun6(start);
        
        // Index to 5th element
        for (int i = 1; i <= 5; i++) {
                start = start->nxt;
        }
        
        if (num != start->val) {
                explode_bomb();
        }
}

