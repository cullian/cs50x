/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 1)
    {
        return false;
    }
    int first = 0, middle = n / 2, last = n - 1;

    while (first - last <= 0)
    {
        if (value == values[middle])
        {
            return true;
        }
        if (value < values[middle])
        {
            last = middle - 1;
            middle = first + ((last - first) / 2);
        }
        if (value > values[middle])
        {
            first = middle + 1;
            middle = first + ((last - first) / 2);
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if (n < 0)
    {
        return;
    }
    
    int swap_counter = -1;
    int swap_holder;
    
    while(swap_counter != 0)
    {
        swap_counter = 0;
        for(int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                swap_holder = values[i];
                values[i] = values[i + 1];
                values[i + 1] = swap_holder;
                swap_counter++;
            }
        
        }
        n--;
    }
    return;
}

