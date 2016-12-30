/**
 * dictionary.c
 * William Cullian
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality using a trie.
 */

#include "dictionary.h"

// root node for trie
node* dic_root = NULL;

// global counter for words
unsigned long int word_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    if (dic_root == NULL)
        return false;
    node* ptr = dic_root;
    // iterate thru chars in word
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        // create hash for alphabet from char
        int alpha_hash = word[i] == '\'' ? TRIE_SIZE - 1 :
            tolower(word[i]) - 'a';
        // if the char is not a child, it is not in the dictionary
        if (ptr->child[alpha_hash] == NULL)
            return false;
        ptr = ptr->child[alpha_hash];
    }
    // we got to the end, is it a word??
    if (ptr->is_word) 
        return true;
    // otherwise
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary file and return false if it dosn't open
    FILE* dic = fopen(dictionary, "rb");
    if (dic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    fseek(dic, 0, SEEK_END);
    unsigned long int fsize = ftell(dic);
    fseek(dic, 0, SEEK_SET);

    // read words from dictionary into trie
    
    // need a char and a root and some nodes and an index
    unsigned long int index = 0;
    char ch;
    node* nodes = calloc(fsize < 100 ? 100 : fsize / 3, sizeof(node));
    dic_root = &nodes[index++];
    if (dic_root == NULL)
    {
        printf("Insufficient Memory.\n");
        unload();
        fclose(dic);
        return false;
    }
    // pointer to current node
    node* current_node = dic_root;
    // iterate over each char in the dictionary until eof
    while((ch = fgetc(dic)) != EOF)
    {
        if (ch == '\n')
        {
            // found a word
            current_node->is_word = true;
            // keep count
            word_count++;
            // ready for new word
            current_node = dic_root;
            continue;
        }
        // hash for alpha child
        int alpha_hash = ch == '\'' ? TRIE_SIZE - 1 :
            ch - 'a';
        // if child node for current char is null, make one
        if (current_node->child[alpha_hash] == NULL)
        {
            current_node->child[alpha_hash] = &nodes[index++];
            if (current_node->child[alpha_hash] == NULL)
            {
                printf("Insufficient Memory.\n");
                unload();
                fclose(dic);
                return false;
            }
        }
        // move to child node for current char
        current_node = current_node->child[alpha_hash];
    }
    if (ferror(dic))
    {
        printf("File Error.\n");
        unload();
        fclose(dic);
        return false;
    }
    fclose(dic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // already counted
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free(dic_root);
    return true;
}
