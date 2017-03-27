#include <stdio.h>
#include <cs50.h>

bool checksum(long long number);
int first_digit(long long number);

int main(void)
{
    long long input;
    printf("Enter Credit Card number: ");
    input = get_long_long();
    if(checksum(input))
    {
        switch(first_digit(input)) 
        {
            case 3:
                printf("AMEX\n");
                break;
        	
            case 5:
                printf("MASTERCARD\n");
                break;
            
            case 4:
                printf("VISA\n");
                break;
          
            default:
                printf("INVALID\n");
        }
    } else 
    {
        printf("INVALID\n");
    }
    
    return 0;
}

bool checksum(long long number)
{
    int sum2 = 0;
    int sum1 = 0;
    int temp;
    while(number)
    {
        sum1 += number%10;
        number /= 10;
        
        temp = (number%10)*2;
        if(temp < 10) {sum2 += temp;}
        else {sum2 += temp%10 + temp/10;}
        number /= 10;
    }

    return ((sum1+sum2)%10 == 0);
}

int first_digit(long long number)
{
    while(number > 9)
    {
        number /= 10;
    }
    return number;
}