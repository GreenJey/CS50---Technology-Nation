#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    // Введення даних від користувача
    do 
    {
        printf("Введіть висоту піраміди (не вище 23): ");
        height = GetInt();
    }
    while(height < 0 || height > 23);
    
    // Формування піраміди
    for (int stovp = 0; stovp < height; stovp++)
    {
      for (int probil = 1; probil < height - stovp; probil++)
      {
          printf (" ");
      }
      
      for (int hash = 0; hash < stovp + 2; hash++)
      {
          printf("#");
      }
      printf("\n");
    }
}