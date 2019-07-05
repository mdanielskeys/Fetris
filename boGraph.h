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
#define CHAR_WIDTH 	  		8
#define CHAR_HEIGHT   		8

#define SGN(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a
                                         number */

typedef unsigned short word;
typedef unsigned char  byte;

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
	void Gputch(int x, int y, int c, int fc, int bc);
	void Gputs(int x, int y, char * string, int fc, int bc);
	void DrawLine(int x1, int y1, int x2, int y2, byte color);
	void Polygon (int num_vertices, int *vertices, byte color);

	void DrawPixel(word x, word y, byte color) const;
};

#endif
