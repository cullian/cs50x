/*
mario.c

William Cullian
cullian@msn.com

makes marios pryamid with #'s

*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get input
    int pyramid_height;
    do
    {
        printf("height: ");
        pyramid_height = GetInt();
    }
    while(pyramid_height < 0 || pyramid_height > 23);
    
    // print pyramid
    for(int i = pyramid_height; i > 0; i--)
    {
        for(int j = 1; j <= pyramid_height; j++)
        {
            if (j < i)
                printf(" ");
            else
                printf("#");
        }
        printf("#\n");
    }
}