#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(void)
{
    int array[] = {76, 5, 6, 3, 10, 6, 0, 35, 34, 1, 0};
    int n = 11;
    
    sort(array, n);
    
    for(int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
    
    return 0;
}