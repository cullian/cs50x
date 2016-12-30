/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// create structure for buffer
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef struct 
{ 
    DWORD header;
    BYTE buffer[508];
} __attribute__((__packed__)) 
BUFFER; 

int main(void)
{
    // open card file
    FILE* file = fopen("card.raw", "r");
    
    // check if it opened
    if (file == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }

    // create buffer for storage of blocks
    BUFFER buffer;

    // pointer to image file
    FILE *image = NULL;

    // tracking variable
    int jpegs_found = 0;

    // loop while we can still read
    while (fread(&buffer, sizeof(buffer), 1, file) != 0)
    {
        // check for new jpeg
        if (buffer.header == 0xe0ffd8ff || buffer.header == 0xe1ffd8ff)
        {
            // if we already had one open, lets close it
            if (jpegs_found > 0)
            {
                // close outfile
                fclose(image);
            }

            // create new file
            char title[8];
            sprintf(title, "%03d.jpg", jpegs_found++);
            image = fopen(title, "a");
            
            // check if it opened
            if (image == NULL)
            {
                printf("Could not open %s.\n", title);
                return 2;
            }
        }
        // if we already found one, lets start writing
        if (jpegs_found > 0)
        {
            fwrite(&buffer, sizeof(buffer), 1, image);
        }
    }
    // close outfile
    fclose(image);
    
    // close infile
    fclose(file);

    // that's all folks
    return 0;

}
