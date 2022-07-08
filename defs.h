#ifndef __defs_h_
#define __defs_h_

#define COLUMNS 10
#define ROWS 20
#define GRID_SIZE COLUMNS * ROWS
#define CELL_FILL_SIZE 7
#define GRID_DIMENSION 8

#define FRAME_COLOR 1
#define FRAME_SPACER 10
#define FRAME_LEFT_X 50
#define FRAME_TOP_Y 20
#define FRAME_RIGHT_X ((COLUMNS + 1) * GRID_DIMENSION) + FRAME_LEFT_X + FRAME_SPACER
#define FRAME_BOTTOM_Y ((ROWS + 1) * GRID_DIMENSION) + FRAME_TOP_Y

#define GRID_LEFT_X 60
#define GRID_TOP_Y 25
#define GRID_RIGHT_X (COLUMNS * GRID_DIMENSION) + GRID_LEFT_X 
#define GRID_BOTTOM_Y (ROWS * GRID_DIMENSION) + GRID_TOP_Y 

#define SPLASH 0
#define PLAYING 1

#define TETRINOS 7

#define VIDEO_INT			0x10
#define SET_MODE			0x00
#define VGA_256_COLOR 		0x13
#define TEXT_MODE			0x03
#define VRETRACE            0x08
#define INPUT_STATUS_1      0x03da
#define VERTICAL_RETRACE             /*  comment out this line for more
                                         accurate timing */
#define PALETTE_MASK        0x3c6
#define PALETTE_REGISTER_RD 0x3c7
#define PALETTE_REGISTER_WR 0x3c8
#define PALETTE_DATA        0x3c9                                         

#define SCREEN_WIDTH 		320
#define SCREEN_HEIGHT 		200
#define SCREEN_SIZE         (unsigned short)(SCREEN_WIDTH*SCREEN_HEIGHT)
#define NUM_COLORS    		256
#define CHAR_WIDTH 	  		8
#define CHAR_HEIGHT   		8

#define GRID_COLOR          1
#define ESC                 27

#define SGN(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a
                                         number */

typedef unsigned short word;
typedef unsigned char  byte;

typedef struct RGB_color_typ
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB_color, *RGB_color_ptr;

typedef struct pcx_header_typ
{
    char manufacturer;
    char version;
    char encoding;
    char bits_per_pixel;
    word  x, y;              // Upper left corner of image
    word  width, height;
    word  horz_res;
    word  vert_res;
    char ega_palette[48];
    char reserved;
    char num_color_planes;
    word  bytes_per_line;
    word  palette_type;
    char padding[58];
} pcx_header, *pcx_header_ptr;

typedef struct pcx_picture_typ
{
    pcx_header header;
    RGB_color palette[256];
    char * buffer;

} pcx_picture, *pcx_picture_ptr;

typedef struct tagBITMAP              /* the structure for a bitmap. */
{
  word width;
  word height;
  byte *data;
} BITMAP;

enum gamestate 
{
	playing,
	hold,
	gameover,
    splash
};

#endif