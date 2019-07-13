#include "pcx.h"
#include "bograph.h"

#include <stdio.h>

pcxfile::~pcxfile()
{
    // deallocate memory
    delete[] image.buffer;
}

pcxfile::pcxfile(char *filename, BoGraphics& gr, int enable_pallette) : graphics(gr)
{
    FILE *fp;
    int num_bytes, index;
    long count;
    unsigned char data;
    char *temp_buffer;

    image.buffer = new char[SCREEN_HEIGHT * SCREEN_WIDTH + 1];

    // open file
    fp = fopen(filename, "rb");

    // load the header
    temp_buffer = (char *)&image;

    for (index=0; index < 128; index++)
    {
        temp_buffer[index] = getc(fp);
    } // end for index (header)

    count = 0;
    while (count < SCREEN_WIDTH * SCREEN_HEIGHT)
    {
        // get first piece of data
        data = getc(fp);

        // Is this an RLE?
        if (data >= 192 && data <= 255)
        {
            // How many bytes are in the run
            num_bytes = data - 192;

            // Get the actual data for the run
            data = getc(fp);

            // Replicate the data in the buffer num_bytes times
            while (num_bytes-- > 0)
            {
                image.buffer[count++] = data;
            } // end while
        } // end if rle
        else
        {
            // Copy the actual data in the buffer at the next location
            image.buffer[count++] = data;
        } // end else not rle
        
    } // end while

    // Move to the end of the file then back up 768 bytes (pallette info)
    fseek(fp, -768, SEEK_END);

    // Load the palette into the VGA registers
    for (index = 0; index<256; index++)
    {
        image.palette[index].red = (getc(fp) >> 2);

        image.palette[index].green = (getc(fp) >> 2);

        image.palette[index].blue = (getc(fp) >> 2);
    } // end for index

    fclose(fp);

    if (enable_pallette)
    {
        for(index = 0; index <256; index++)
        {
            graphics.SetPaletteRegister(index, &image.palette[index]);
        }
    } // end if change palette
}

void pcxfile::LoadPalette()
{
    for(int index = 0; index <256; index++)
    {
        graphics.SetPaletteRegister(index, &image.palette[index]);
    }    
}

void pcxfile::DrawImage()
{
    graphics.ScreenCopy(image.buffer);
}