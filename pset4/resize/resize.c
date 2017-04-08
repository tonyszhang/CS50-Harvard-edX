/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f input.bmp output.bmp\n");
        return 1;
    }

    // get factor & remember filenames
    float factor = atof(argv[1]);
    if (factor > 100 || factor <= 0)
    {
        fprintf(stderr, "Usage: f must be in (0.0, 100.0]\n");
        return 1;
    }
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // save dimension of original image
    LONG biWidth_o = bi.biWidth;
    LONG biHeight_o = bi.biHeight;
    int padding_o =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // modify output file's header info
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // new padding
    bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // save the input bitmap into a 2D array
    RGBTRIPLE bitmap[abs(biHeight_o)][biWidth_o];
    
    // iterate over infile's scanlines (more comfortable version)
    for (int i = 0, biHeight = abs(biHeight_o); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < biWidth_o; j++)
        {
            // read RGB triple from infile
            fread(&(bitmap[i][j]), sizeof(RGBTRIPLE), 1, inptr);
        }
        // skip over padding, if any
        fseek(inptr, padding_o, SEEK_CUR);
    }
    // write to output file by picking the right pixels
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple = bitmap[(int) (i/factor)][(int) (j/factor)];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        // skip over padding, if any
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    // less comfortable code for only scaling up (factor is int n >=1)
    //
    // for (int i = 0, biHeight = abs(biHeight_o); i < biHeight; i++)
    // {
    //     for(int ii = 0; ii < factor - 1; ii++)
    //     {    
    //         // iterate over pixels in 1 scanline
    //         for (int j = 0; j < biWidth_o; j++)
    //         {
    //             // temporary storage
    //             RGBTRIPLE triple;
    
    //             // read RGB triple from infile
    //             fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
    //             // for each pixel in a row
    //             for(int jj = 0; jj < factor; jj++)
    //             {
    //                 // write RGB triple to outfile
    //                 fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
    //             }
    //         }
    //         // add padding to output
    //         for (int k = 0; k < padding; k++)
    //         {
    //             fputc(0x00, outptr);
    //         }
    //         fseek(inptr, -1*(long int) (biWidth_o*sizeof(RGBTRIPLE)), SEEK_CUR);
    //     }
        
    //     // write last scanline
    //     for (int j2 = 0; j2 < biWidth_o; j2++)
    //     {
    //         // temporary storage
    //         RGBTRIPLE triple;

    //         // read RGB triple from infile
    //         fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
    //         // for each pixel in a row
    //         for(int jj2 = 0; jj2 < factor; jj2++)
    //         {
    //             // write RGB triple to outfile
    //             fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
    //         }
    //     }
    //     for (int k2 = 0; k2 < padding; k2++)
    //     {
    //         fputc(0x00, outptr);
    //     }
    //     // skip over padding, if any
    //     fseek(inptr, padding_o, SEEK_CUR);
    // }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
