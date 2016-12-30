/*
vigenere.c

William Cullian
cullian@msn.com

encrypts using vigenere cipher

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
    for(int i = 0, j = strlen(argv[1]); i < j; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Alphabetic key required!\n");
            return 1;
        }
    }
    
    // get cipher text
    string cipher_text = GetString();
    
    // encrypt text with key
    for(int i = 0, j = strlen(cipher_text), k = 0, key_len = strlen(argv[1]), 
        key = 0; i < j; i++)
    {
        if (isalpha(cipher_text[i]))
        {
            key = ((toupper(argv[1][k]) - 'A') + 
                (toupper(cipher_text[i]) - 'A')) % 26;
            if (isupper(cipher_text[i]))
            {
                cipher_text[i] = 'A' + key;
            }
            else
            {
                cipher_text[i] = 'a' + key;
            }
            if (++k == key_len)
            {
                k = 0;
            }
        }
    }
    
    // print results
    printf("%s\n", cipher_text);

    return 0;
}