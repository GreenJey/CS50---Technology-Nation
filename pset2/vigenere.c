#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Перевірка на введення аргументу
    if (argc != 2)
    {
        printf("Usage: \n");
        return 1;
    }
    
    //Ділення другого аргумента на символи
    int mass_argument1 = strlen(argv[1]);
    
    //Перевірка на алфавітні символи в масиві Аргумент1
    for (int i = 0; i < mass_argument1; i++)
    {   
        if (isalpha(argv[1][i]) == false)
        {
            printf("Введіть букви латинського алфавіту A-Z або a-z\n");
            return 1;
        }
    } 
    
    //Введення тексту від користувача
    string text = get_string();
    
    //Шифрування тексту від користувача
    for (int i = 0, b = 0, result = 0, n = strlen(text); i < n; i++)
    {
        int litera = text[i];
        
        //Рахунок символів масива Аргумента1 від першого(0)
        int key = argv[1][(b) % mass_argument1];  
        
        if (isupper(key)) 
        {
           key = key - 65; 
        }
        else if (islower(key))
        {
           key = key - 97;
        }
    
        if (isupper (litera))
        {
            result = (litera + key - 65) % 26 + 65;
            b++;
        }
        else if (islower (litera))
        {
            result = (litera + key - 97) % 26 + 97;
            b++;
        }
        else
        {
           result = litera;
        }
        printf("%c", result);
    }
    printf("\n");
}    