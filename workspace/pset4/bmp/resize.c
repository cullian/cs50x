/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
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
        printf("Usage: ./copy resize_factor infile outfile\n");
        return 1;
    }

    // remember resize factor
    int resize_factor = atoi(argv[1]);

    // ensure proper usage
    if (resize_factor < 1 || resize_factor > 100)
    {
        printf("Resize factor must be positive whole number less than or equal to 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
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

    // determine padding for scanlines of input file
    int padding_input =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // set variables before changing header info
    int biHeight = abs(bi.biHeight);
    int biWidth =  bi.biWidth;
    // change headers size attributes
    bi.biWidth *= resize_factor;
    bi.biHeight *= resize_factor;
    // determine padding for scanlines of output file
    int padding_output =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // change headers size attributes
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding_output) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(bf) + sizeof(bi);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < biHeight; i++)
    {
        // temporary storage array for scanline
        RGBTRIPLE triple[biWidth];
        // iterate over pixels in scanline
        for (int j = 0; j < biWidth; j++)
        {
            // read RGB triple from infile into temp array
            fread(&triple[j], sizeof(RGBTRIPLE), 1, inptr);
        }
        // skip over padding in input file, if any
        fseek(inptr, padding_input, SEEK_CUR);

        // write stored scanline resize_factor times
        for (int k = 0; k < resize_factor; k++)
        {
            // iterate over pixels in array and write them resize_factor times
            for (int l = 0; l < biWidth; l++)
            {
                for (int m = 0; m < resize_factor; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple[l], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // then add padding, if neccessary, to output file
            for (int n = 0; n < padding_output; n++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
