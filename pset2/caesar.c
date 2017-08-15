#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Перевірка на вхідні командні дані від користувача
    if (argc != 2)
    {
        printf("Usage: ./caesar kay\n");
        return 1;
    } 
    
    int k = atoi(argv [1]);
    if (k < 0)
    {
        printf("Usage: key < 0\n");
        return 1;
    }
    
    //Введення тексту для шифрування
    string text = get_string();
    
    //Шифрування вхідного тексту
    for (int i = 0, result = 0, n = strlen(text); i < n; i++)
    {
        if (isupper (text[i]))
        {
            result = ((((text[i] - 65) + k) % 26) + 65);
        }
        else if (islower (text[i]))
        {
            result = ((((text[i] - 97) + k) % 26) + 97);
        }
        else
        {
            result = text[i];
        }
        printf("%c", result);
    }
    printf("\n");
}