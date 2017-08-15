#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s = get_string();
    
    if (s != NULL)
    {
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            if (i == 0)
            {
                printf("%c", toupper(s[i]));
            }
            else if (s[i] == ' ')
            {
                printf("%c", toupper(s[i + 1]));
            }
        }
        printf("\n");
    }
}