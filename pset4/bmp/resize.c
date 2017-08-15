#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // Перевірка на кількість аргументів
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    // Переведення 2 аргумента в тип Integer
    int n = atoi(argv[1]);
    
    // Перевірка діапазонів
    if (n > 100 || n < 0)
    {
        printf("n > 100 АБО n < 0\n");
        return 2;
    }

    // Вказівник на вхідний та вихідний файл
    char* infile = argv[2];
    char* outfile = argv[3];

    // Відкриття вхідного файла 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // Відкриття вихідного файла
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }
    
    // Визначити відступи для ліній розгортки вхідного файлу
    int paddingIn =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // width and height вхідного файлу   
    int width = bi.biWidth;
    int height = bi.biHeight;
    
    // width and height вихідного файлу
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // Визначити відступи для ліній розгортки вихідного файлу
    int paddingOut =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine outfile's size and image size.
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingOut) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
    
        // Зберегти позицію вказівника вхідного файлу
        long positionIn = ftell(inptr);
        
        for (int p = 0; p < n; p++)
        {
        
            // Отримати позицію введення покажчика, щоб скопіювати його n раз    
            fseek(inptr, positionIn, SEEK_SET);
            
            // Перейти по кожному пікселю в рядках
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);  
                    
                for (int m = 0; m < n; m++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, paddingIn, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingOut; k++)
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