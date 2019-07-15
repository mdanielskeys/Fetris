#ifndef __boGraphics_h_
#define __boGraphics_h_
#include "defs.h"

class BoGraphics
{
private:
	byte* VGA; 				// VGA memory start
	byte* charSet;		    // Points to all characters in ROM character set 
	

	byte* double_buffer;					// buffer of screen

	void setVideoMode(byte mode);

public:
	BoGraphics();

	bool SetGraphicsMode();
	void SetTextMode();
	void FlipVideoBuffer();
	void ClearScreen();
	void Gputch(int x, int y, int c, int fc, int bc) const;
	void Gputs(int x, int y, char * string, int fc, int bc) const;
	void DrawLine(int x1, int y1, int x2, int y2, byte color);
	void Polygon (int num_vertices, int *vertices, byte color);
	void DrawSolidRect(int x1, int y1, int x2, int y2, byte color) const;
	void DrawRect(int x1, int y1, int x2, int y2, byte color) const;
	
	void DrawPixel(word x, word y, byte color) const;
	void ScreenCopy(char * image) const ;
	void SetPaletteRegister(int index, RGB_color_ptr color) const;
	void ReadPaletteRegister(int index, RGB_color_ptr color) const;
};

#endif
