#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//first 3 bytes of JPEG: 0xff 0xd8 0xff
//fourth byte’s first four bits are 1110 (0xe_)
typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    
    // open input file 
    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open input file.\n");
        return 2;
    }
    
    // declare variables
    BYTE block[512];
    int nBytes;
    int nFile = 0;
    char filename[8];
    FILE* output = NULL;
    
    do
    {
        nBytes = fread(&block, 1, 512, input);
        if(nBytes != 512) {break;}
        
        // is start of new jpeg (a star)
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            if(output != NULL) 
            {
                fclose(output);
                nFile++;
            }
            
            sprintf(filename, "%03i.jpg", nFile);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                fclose(input);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            
            fwrite(&block, 1, 512, output);
        }
        else if(output != NULL)
        {
            fwrite(&block, 1, 512, output);
        }
    } while(nBytes == 512);
    
    // close input/output file
    fclose(output);
    fclose(input);

    // success
    return 0;
}