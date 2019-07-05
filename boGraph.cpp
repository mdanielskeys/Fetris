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
	memset(double_buffer, 0, SCREEN_SIZE);
}

void BoGraphics::DrawPixel(word x, word y, byte color) const 
{
	double_buffer[(y<<8) + (y<<6) + x] = color;
}

void BoGraphics::Gputch(int x, int y, int c, int fc, int bc)
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
						DrawPixel(x + xOff>>1, y + yOff>>1, fc);
					}
					else if (bc >= 0)
					{
						DrawPixel(x + xOff>>1, y + yOff>>1, bc);
					}
					bit >>= 1;
				}
			}
			workChar++;
		}
	}
}

void BoGraphics::Gputs(int x, int y, char * string, int fc, int bc)
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
