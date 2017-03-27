#include <stdio.h>
#include <cs50.h>

void print_hashes(int n);
void print_line(int m, int n);

int main(void)
{
    int base;
    do {
        printf("Height: ");
        base = get_int();
    } while (base > 23 || base < 0);
    int front = base;
    for(int i = 1; i <= base; i++)
    {
        print_line(front, i);
        front--;
    }
}

void print_hashes(int n)
{
    //prints n hash marks in a row
    for(int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_line(int m, int n)
{
    //prints one line of hashes, starting after m spaces
    for(int i = 1; i < m; i++)
    {
        printf(" ");
    }
    print_hashes(n);
    printf("  ");
    print_hashes(n);
    printf("\n");
}