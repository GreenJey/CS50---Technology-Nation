#include <cs50.h>
#include <stdio.h>

int mat();

int main (void)
{
    int minutes;
    do
    {
        printf("Minutes: ");
        minutes = get_int();
    }
    while (minutes <= 0);
    
    int a = mat(minutes);
    printf("Botels: %i\n", a);
}

int mat(int a)
{
    return a * 12;
}