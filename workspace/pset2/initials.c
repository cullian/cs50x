/*
initials.c

William Cullian
cullian@msn.com

takes a name, outputs the initials

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // get string
    string name;
    do
    {
        name = GetString();
    }
    while(name == NULL);

    // create string and index for initials
    char initials[4] = "   ";
    int init_index = 0;
    
    // iterate through name looking for spaces
    for(int i = 0, j = strlen(name); i < j; i++)
    {
        // initialize first initial with first letter of name
        if (i == 0 && !isspace(name[i]))
        {
            initials[init_index++] = toupper(name[i]);
            continue;
        }
        if (isspace(name[i]))
        {
            // if next char isn't a space add it to the initials
            if (!isspace(name[i + 1]))
            {
                initials[init_index++] = toupper(name[i + 1]);

            }
        }
        // check for too many initials
        if (init_index > 2) 
        {
            break;
        }
    }
    // move end of line
    initials[init_index] = initials[3];
    
    printf("%s\n", initials);
    return 0;
}