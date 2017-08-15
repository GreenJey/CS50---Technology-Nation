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
    // TODO: implement a searching algorithm
    // Встановити значення верхньої і нижньої межі пошуку  
    
    int lower = 0;  
    int upper = n - 1;   
    
    while(lower <= upper)  
    {    
        // Знайти середину   
        int middle = (upper + lower) / 2;
        
        //Порівняти значення в середині з шуканим    
        if(values[middle] == value)    
         	return true;    
        else if (values[middle] < value)    
            lower = middle + 1;    
        else 
            upper = middle - 1;    
    }  
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    //Оптимізація: перевірка на здійснення обмінів
    
    int swaps = 0;
    
    for(int i = 0; i < n - 1; i++)
    {
        //Перевірити елементи i та i+1
        if(values[i] > values[i+1])
        {
            int temp = values[i+1];
            values[i+1] = values[i];
            values[i] = temp;
            swaps++;
        }
        else if(swaps == 0)
            break;
    }
}