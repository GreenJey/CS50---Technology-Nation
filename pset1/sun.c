#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    do
    {
        int a = get_int();
        int b = get_int();
        printf("%i\n", a % b);
    }
    while(true);
}