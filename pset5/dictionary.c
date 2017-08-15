#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// створення структури для звязних списків
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

int HASH_SIZE = 143091;

// розмір словника
int lines = 0;

node* hashtable[143091];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // визначення довжини слова
    int len = strlen(word);
    
    // виділення памяті для букв нижнього регустру 
    char* lower_word = malloc(sizeof(char)*(len + 1));
    if (lower_word == NULL)
    {
        printf("Error\n");
        return false;
    }
    
    // перетворення букви до нижнього регістру
    for (int i = 0; i < len; i++)
    {
        if (isupper(word[i]))
        {  
            lower_word[i] = tolower(word[i]);
        }
        else
        {
            lower_word[i] = word[i];
        }
    }
    lower_word[len] = '\0';
    
    // використання функції hash
    long key = hash(lower_word);   
    node* new = hashtable[key];
    
    // перевірити чи є слово у словнику
    while (new != NULL)
    { 
        if (strcmp (new->word, lower_word) == 0)
        {
            free(lower_word);
            return true;
        }
        else
        {
            new = new->next;
        }
    }
    free(lower_word);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // відкрити словник
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Error %s.\n", dictionary);
        return 1;
    }
    
    int ch;
    
    // підрахунок кількості слів в словнику
    while ((ch = fgetc(dic)) != EOF)
    {
        if(ch == '\n')
        {
            lines++;
            ch = '\0';
        }
    }
    
    // встановити позицію файлу потоку в початок файлу
    fseek( dic, 0, SEEK_SET );
      
    while (1)
    {
        // виділення пам'яті для кожного нового слова
        node* new_node = malloc(sizeof(node));
        
        if (new_node == NULL)
        {
            printf("Error\n");
            return false;
        } 
    
        // сканувати рядок з нашого файлу словника 
        fscanf(dic, "%s", new_node->word);
        
        // перевірити чи наступив кінець файла
        if(feof(dic))
        {
            free(new_node);
            break;
        }
        
        // використання функції hash
        long key = hash(new_node->word);
    
        // додати новий вузол в початок списку
        new_node->next = hashtable[key];
        hashtable[key] = new_node;
       
    }
    
    // закрити словник
    fclose(dic);
      
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return lines;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        node* tab = hashtable[i];
        node* temp = NULL;    
    
        // звільнити всі вузли в списку
        while (tab != NULL)
        {
            temp = tab;
            tab = temp->next;
            free(temp);
        }
    }
    return true;
}

unsigned long hash(char *str)
{
    
    int has = tolower(str[0]) - 'a';
    
    return has % HASH_SIZE;
}