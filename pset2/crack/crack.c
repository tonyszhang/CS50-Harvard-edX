#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc != 2) 
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    string hash = argv[1];
    
    char password[5];
    
    //try length 1
    password[1] = '\0';
    for(int i = 'A'; i <= 'z'; i++) {
        password[0] = i;
        //printf("%s\n", password);
        if(!strcmp(crypt(password,"50"), hash)) {
            printf("%s\n", password);
            return 0;
        }
    }
    
    //try length 2
    password[2] = '\0';
    for(int i = 'A'; i <= 'z'; i++) {
        password[0] = i;
        for(int j = 'A'; j <= 'z'; j++) {
            password[1] = j;
            //printf("%s\n", password);
            if(!strcmp(crypt(password,"50"), hash)) {
                printf("%s\n", password);
                return 0;
            }
        }
    }
    
    //try length 3
    password[3] = '\0';
    for(int i = 'A'; i <= 'z'; i++) {
        password[0] = i;
        for(int j = 'A'; j <= 'z'; j++) {
            password[1] = j;
            for(int k = 'A'; k <= 'z'; k++) {
                password[2] = k;
                //printf("%s\n", password);
                if(!strcmp(crypt(password,"50"), hash)) {
                    printf("%s\n", password);
                    return 0;
                }
            }
        }
    }
    
    //try length 4
    password[4] = '\0';
    for(int i = 'A'; i <= 'z'; i++) {
        password[0] = i;
        for(int j = 'A'; j <= 'z'; j++) {
            password[1] = j;
            for(int k = 'A'; k <= 'z'; k++) {
                password[2] = k;
                for(int l = 'A'; l <= 'z'; l++) {
                    password[3] = l;
                    //printf("%s\n", password);
                    if(!strcmp(crypt(password,"50"), hash)) {
                        printf("%s\n", password);
                        return 0;
                    }
                }
            }
        }
    }
    
}