/*
caesar.c

William Cullian
cullian@msn.com

encrypts using caesar cipher

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check command line input
    if (argc != 2)
    {
        printf("One key required!\n");
        return 1;
    }
    int key = atoi(argv[1]);
    if (key < 1)
    {
        printf("Must be a positive integer!\n");
        return 1;
    }

    // get cipher text
    string cipher_text;
    do
    {
        cipher_text = GetString();
    }
    while(cipher_text == NULL);

    // set key to smallest possible value
    key %= 26;

    // encrypt message
    for(int i = 0, j = strlen(cipher_text); i < j; i++)
    {
        if (isalpha(cipher_text[i]))
        {
            if (isupper(cipher_text[i]))
            {
                cipher_text[i] = 'A' + ((key + (cipher_text[i] - 'A')) % 26);
            }
            else
            {
                cipher_text[i] = 'a' + ((key + (cipher_text[i] - 'a')) % 26);
            }
        }
    }
    
    // print results
    printf("%s\n", cipher_text);

    return 0;
}