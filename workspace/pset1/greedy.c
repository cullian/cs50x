/*
greedy.c

William Cullian
cullian@msn.com

calculates how many coins you get for change

*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get input
    float change;
    int num_pennies;
    do
    {
        printf("O hai! How much change is owed? ");
        change = GetFloat();
    }
    while(change < 0);
    
    // convery change into int value for number of pennies
    change *= 100.0;
    num_pennies = (int) (change);
    if (change > num_pennies)
    {
        if ((change - num_pennies) >= .50)
        {
            num_pennies++;
        }
    }
    
    // find out how many coins to make change
    int num_coins;
    num_coins = num_pennies / 25;
    num_pennies = num_pennies % 25;
    num_coins += num_pennies / 10;
    num_pennies = num_pennies % 10;
    num_coins += num_pennies / 5;
    num_pennies = num_pennies % 5;
    num_coins += num_pennies;
    printf("%i\n", num_coins);
}