#include <cs50.h>
#include <stdio.h>

double money;
int ostacha;
int perevod;

void vvedennya_koristuvscha(void);
void obrahunok_vuvedennya(void);

int main (void)
{
    vvedennya_koristuvscha();
    obrahunok_vuvedennya();
}

void vvedennya_koristuvscha(void)
{
    do
    {
        printf("O hai! How much change is owed?\n");
        money = GetDouble();
    
    }
    while(money <= 0); 
    perevod = money * 100;
}


void obrahunok_vuvedennya(void)
{
    int counter = 0;
        while(perevod >= 25)
        {
            counter++;
            ostacha = perevod - 25;
            perevod = ostacha;
            
        }
        while(perevod >= 10)
        {
            counter++;
            ostacha = perevod - 10;
            perevod = ostacha;
           
        }
         while(perevod >= 5)
        {
            counter++;
            ostacha = perevod - 5;
            perevod = ostacha;
           
        }
         while(perevod >= 1)
        {
            counter++;
            ostacha = perevod - 1;
            perevod = ostacha;
            
        }
    printf("%i\n", counter);
}