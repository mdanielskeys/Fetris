#ifndef __pcx_h_
#define __pcx_h_
#include "defs.h"

class BoGraphics;

class pcxfile
{
private:
    pcx_picture image;
    const BoGraphics &graphics;

public:
    pcxfile(char *filename, const BoGraphics& graphics, int enable_pallette);
    ~pcxfile();

    void DrawImage();
    void LoadPalette();
};

#endif
