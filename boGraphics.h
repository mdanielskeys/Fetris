#ifndef __boGraphics_h_
#define __boGraphics_h_

#define VIDEO_INT			0x10
#define SET_MODE			0x00
#define VGA_256_COLOR 		0x13
#define TEXT_MODE			0x03
#define VRETRACE            0x08
#define INPUT_STATUS_1      0x03da
#define VERTICAL_RETRACE             /*  comment out this line for more
                                         accurate timing */

#define SCREEN_WIDTH 		320
#define SCREEN_HEIGHT 		200
#define SCREEN_SIZE         (unsigned short)(SCREEN_WIDTH*SCREEN_HEIGHT)
#define NUM_COLORS    		256

typedef unsigned short word;
typedef unsigned char  byte;

class BoGraphics
{
private:
	void setVideoMode(byte mode);

public:
	void SetGraphicsMode();
	void SetTextMode();

	void DrawPixel(word x, word y, byte color);
}

#endif
