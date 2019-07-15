#ifndef __bitmap_h_
#define __bitmap_h_
#include "defs.h"
#include <stdio.h>

class BoGraphics;

class bitmapfile
{
private:
    BITMAP image;
    void fskip(FILE *fp, int num_bytes);

public:
    bitmapfile(char *filename);
    ~bitmapfile();

    void DrawImage(const BoGraphics& graphics);
};

#endif
