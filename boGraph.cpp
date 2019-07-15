#include "defs.h"
#include "boGraph.h"

#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

BoGraphics::BoGraphics()
{
	VGA = (byte*)0xA0000;				// VGA memory start
	charSet = (byte*)0xF0000;		    // Points to all characters in ROM character set 
}

void BoGraphics::setVideoMode(byte mode)
{
	_asm {
		mov al, mode
		mov ah, SET_MODE
		int VIDEO_INT
	}
}

bool BoGraphics::SetGraphicsMode()
{
	double_buffer = new byte[SCREEN_SIZE];
	if (double_buffer == NULL)
	{
		printf("Not enough memory for double buffer\n");
		return false;
	}

	setVideoMode(VGA_256_COLOR);

	return true;
}

void BoGraphics::SetTextMode()
{
	if (double_buffer != NULL)
	{
		delete[] double_buffer;
	}

	setVideoMode(TEXT_MODE);
}

void BoGraphics::FlipVideoBuffer()
{

#ifdef VERTICAL_RETRACE
	while ((inp(INPUT_STATUS_1) & VRETRACE));
	while (!(inp(INPUT_STATUS_1) & VRETRACE));
#endif
	memcpy(VGA, double_buffer, SCREEN_SIZE);
}

void BoGraphics::ClearScreen()
{
	memset(double_buffer, 253, SCREEN_SIZE);
}

void BoGraphics::DrawPixel(word x, word y, byte color) const 
{
	// check to make sure that we are within bounds
	if (x > 0 && x < 320 && y > 0 && y < 200)
	{
		double_buffer[(y<<8) + (y<<6) + x] = color;
	}
}

void BoGraphics::Gputch(int x, int y, int c, int fc, int bc) const 
{
	byte *workChar;			// points to the character rendered
	byte bit; 		// bit mask

	// get character to be rendered
	workChar = &(charSet +  0xFA6E)[(c & 0xFF) * CHAR_HEIGHT];
	for (int yOff = 0; yOff < CHAR_HEIGHT; yOff++)
	{
		if (y + yOff < SCREEN_HEIGHT) 
		{
			bit = 0x80;
			for (int xOff = 0; xOff < CHAR_WIDTH; xOff++)
			{
				if (x + xOff < SCREEN_WIDTH)
				{
					if (*workChar & bit)
					{
						DrawPixel(x + xOff, y + yOff, fc);
					}
					else if (bc >= 0)
					{
						DrawPixel(x + xOff, y + yOff, bc);
					}
					bit >>= 1;
				}
			}
			workChar++;
		}
	}
}

void BoGraphics::Gputs(int x, int y, char * string, int fc, int bc) const 
{
	for (int i = 0; string[i]; i++)
	{
		Gputch(x + (i << 3), y, string[i], fc, bc);
	}
}

void BoGraphics::DrawLine(int x1, int y1, int x2, int y2, byte color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int dxabs = abs(dx);
	int dyabs = abs(dy);
	int sdx = SGN(dx);
	int sdy = SGN(dy);
	int x = dyabs>>1;
	int y = dxabs>>1;

	int px = x1;
	int py = y1;

	DrawPixel(px, py, color);

	if (dxabs >= dyabs)		// the line is more horizontal than vertical		
	{
		for (int i = 0; i < dxabs; i++)
		{
			y += dyabs;
			if (y >= dxabs)
			{
				y -= dxabs;
				py += sdy;
			}
			px += sdx;
			DrawPixel(px, py, color);
		}
	}
	else 
	{
		for (int i = 0; i < dyabs; i++)
		{
			x += dxabs;
			if (x >= dyabs)
			{
				x -= dyabs;
				px += sdx;
			}
			py += sdy;
			DrawPixel(px, py, color);
		}
	}
}

void BoGraphics::Polygon (int num_vertices, int *vertices, byte color)
{
	// draw a set of lines connecting the endpoint of the previous
	// line with the beginning of the next line
	for (int i = 0; i < num_vertices - 1; i++)
	{
		DrawLine(vertices[(i<<1)+0],
				vertices[(i<<1)+1],
				vertices[(i<<1)+2],
				vertices[(i<<1)+3],
				color);
	}

	// draw the final line to connect back with the first line
	DrawLine(vertices[0],
			vertices[1],
			vertices[(num_vertices<<1)-2],
			vertices[(num_vertices<<1)-1],
			color);

}

void BoGraphics::DrawSolidRect(int x1, int y1, int x2, int y2, byte color) const
{
	for (int py = y1; py < y2; py++)
	{
		for (int px = x1; px < x2; px++)
		{
			DrawPixel(px, py, color);
		}
	}
}

void BoGraphics::DrawRect(int x1, int y1, int x2, int y2, byte color) const
{
	// draw top and bottom lines
	for (int px = x1; px < x2; px++)
	{
		DrawPixel(px, y1, color);
		DrawPixel(px, y2, color);
	}

	// draw vertical lines
	for (int py = y1; py < y2; py++)
	{
		DrawPixel(x1, py, color);
		DrawPixel(x2, py, color);
	}
}

void BoGraphics::SetPaletteRegister(int index, const RGB_color_ptr color) const
{
	outp(PALETTE_MASK, 0xff);

	outp(PALETTE_REGISTER_WR, index);
	outp(PALETTE_DATA, color->red);
	outp(PALETTE_DATA, color->green);
	outp(PALETTE_DATA, color->blue);
}

void BoGraphics::ReadPaletteRegister(int index, RGB_color_ptr color) const
{
	outp(PALETTE_MASK, 0xff);

	outp(PALETTE_REGISTER_RD, index);

	color->red = inp(PALETTE_DATA);
	color->green = inp(PALETTE_DATA);
	color->blue = inp(PALETTE_DATA);
}

void BoGraphics::ScreenCopy(char * image) const
{
	memcpy(double_buffer, image, SCREEN_HEIGHT * SCREEN_WIDTH);
}