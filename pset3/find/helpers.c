/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) //binary search
{
    if(n < 1)
    {
        return false;
    }
    
    int start = 0;
    int end = n - 1;
    int middle;
    
    while(start <= end)
    {
        middle = (start + end)/2;
        
        if(value == values[middle])
        {
            return true;
        } 
        else if(value < values[middle])
        {
            end = middle - 1;
        }
        else if(value > values[middle])
        {
            start = middle + 1;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
// void sort(int values[], int n) //selection sort
// {
//     int i, j, temp;
    
//     for(i = 0; i < n - 1; i++)
//     {
//         int min_i = i;
        
//         for(j = i + 1; j < n; j++)
//         {
//             if(values[j] < values[min_i])
//             {
//                 min_i = j;
//             }
//         }
        
//         if(min_i != i)
//         {
//             temp = values[i];
//             values[i] = values[min_i];
//             values[min_i] = temp;
//         }
//     }
    
//     return;
// }

// void sort(int values[], int n) //bubble sort
// {
//     int i, j, temp;
    
//     for(i = 0; i < n - 1; i++)
//     {
//         for(j = 0; j < n - 1; j++)
//         {
//             if(values[j] > values[j+1])
//             {
//                 temp = values[j];
//                 values[j] = values[j+1];
//                 values[j+1]= temp;
//             }
//         }
//     }
    
    
//     return;
// }

void sort(int values[], int n) //counting sort
{
    const int MAX = 65536;
    int array[MAX];
    for(int i = 0; i < MAX; i++)
    {
        array[i] = 0;
    }
    
    for(int j = 0; j < n; j++)
    {
        array[values[j]]++;
    }
    
    for(int i = 0, j = 0, count; i < MAX; i++)
    {
        count = array[i];
        while(count)
        {
            values[j] = i;
            j++;
            count--;
        }
    }
    
    return;
}