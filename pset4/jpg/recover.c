/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include<stdio.h>
#include<stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(void)
{
    //Відкриваємо файл із флешкарти
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("Cloud not open\n");
        return 1;
    }
    
    //Створення масиву розміром 1 JPG
    BYTE buffer[512];
    
    //Лічильник кл. зображень
    int counter = 0;
    
    char* title = malloc(sizeof(char));
    
    FILE* images = NULL;
   
    while (fread(&buffer, 512 * sizeof(BYTE), 1, card) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (counter != 0)
            {
                fclose(images);
            }
            counter++;
            
            sprintf(title, "%03d.jpg", (counter - 1));
            
            images = fopen(title, "w");
            
            if(images == NULL)
            {
                printf("Cloud not open\n");
                return 2;
            }
           
            fwrite(&buffer, 512 * sizeof(BYTE), 1, images);
        }
        
        //Запис
        else if (counter!= 0)
        {
            fwrite(&buffer, 512 * sizeof(BYTE), 1, images);
        }
    }
    
    //Закриття відкритих файлів
    fclose(card);
    fclose(images);
    free(title);
}