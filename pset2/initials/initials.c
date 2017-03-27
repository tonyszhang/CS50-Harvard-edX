#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool isSpace(char letter);

int main(void)
{
    string input = get_string();
    
    for(int i = 0, n = strlen(input); i < n; i++)
    {
        if(!isSpace(input[i]) && (i==0 || isSpace(input[i-1])))
        {
            printf("%c", toupper(input[i]));
        }
    }
    printf("\n");
}

bool isSpace(char letter)
{
    if(letter == ' ')
    {
        return true;
    } else 
    {
        return false;
    }
}