#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char shift(char p, int k);

int main(int argc, string argv[])
{
    if(argc != 2) 
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    string key = argv[1];
    int n = strlen(key), key_arr[n];
    for(int i = 0; i < n; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Only alphabetical keywords!\n");
            return 1;
        }
        else if(isupper(key[i]))
        {
            key_arr[i] = key[i] - 65;
        }
        else if(islower(key[i]))
        {
            key_arr[i] = key[i] - 97;
        }
    }
    
    printf("plaintext:  ");
    string input = get_string();
    
    printf("ciphertext: ");

    for(int i = 0, j = 0, m = strlen(input), k; i < m; i++)
    {
        if(!isalpha(input[i]))
        {
            k = key_arr[j%n];
        }
        else
        {
            k = key_arr[j%n];
            j++;
        }
        
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