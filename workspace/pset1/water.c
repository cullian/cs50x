/*
water.c

William Cullian
cullian@msn.com

calculates how many bottles you use per minutes in shower

*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int minutes_in_shower = GetInt();
    printf("bottles: %i\n", minutes_in_shower * 12);
}