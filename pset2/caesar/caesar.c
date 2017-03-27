#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char shift(char p, int k);

int main(int argc, string argv[])
{
    if(argc != 2) 
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    printf("plaintext:  ");
    string input = get_string();
    
    printf("ciphertext: ");
    
    for(int i = 0, n = strlen(input); i < n; i++)
    {
        printf("%c", shift(input[i], k));
    }
    
    printf("\n");
    
    return 0;
}

char shift(char p, int k)
{
    char c;
    
    if(isupper(p))
    {
        int p_alpha = p - 65;
        int c_alpha = (p_alpha + k)%26;
        c = c_alpha + 65;
    }
    else if (islower(p))
    {
        int p_alpha = p - 97;
        int c_alpha = (p_alpha + k)%26;
        c = c_alpha + 97;
    }
    else
    {
        c = p;
    }
    
    return c;
}