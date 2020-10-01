/*
 * readaline.c
 * by Christian Zinck and Josh Mitchell. 2/1/18
 * HW 1: FilesNPix
 *
 * A program that reads a single line of input from a file that is presumed to
 * be open for reading.
 */

#include <readaline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * readaline takes an open file and a reference to a c string. It reads the
 * first unread line from the file and stores it in the given c string
 * reference. The function returns the number of bytes necessary to store the
 * c string contained in the reference. If the end of file is reached, the c
 * string reference is set to NULL and 0 is returned.
 *
 * Parameters:
 *         inputfd - an open file to be read from.
 *         datapp - a c string reference used as an extra return value.
 *
 *
 */
size_t readaline(FILE *inputfd, char **datapp)
{
        if (inputfd == NULL || datapp == NULL) {
                fprintf(stderr, "One or both argument(s) was NULL.\n");
                exit(EXIT_FAILURE);
        }
        
        int currentMax = 100;
        int position = 0;
        char ch = ' ';
        char *buffer = malloc(currentMax);
        if (buffer == NULL) {
                fprintf(stderr, "Failed to malloc.\n");
                exit(EXIT_FAILURE);
        }
        while ((ch != '\n') && (ch != EOF)) {
                if (position == currentMax) {
                        currentMax *= 2;
                        buffer = realloc(buffer, currentMax);
                }
                ch = fgetc(inputfd);
                buffer[position] = ch;
                ++position;
        }

        buffer[position] = '\0';
        ++position;
 
        if (ch == EOF) {
                if (!feof(inputfd)) {
                        fprintf(stderr, "Failed to read from file.\n");
                        exit(EXIT_FAILURE);
                } else {
                        *datapp = NULL;
                        return 0;
                }
        } else {
                *datapp = buffer;
                return position;
        }
}
