#include "boGraphics.h"

void setVideoMode(byte mode)
{
	_asm {
		mov al, mode
		mov ah, SET_MODE
		int VIDEO_INT
	}
}

void SetGraphicsMode()
{
	setVideoMode(VGA_256_COLOR);
}

void SetTextMode()
{
	setVideoMode(TEXT_MODE);
}