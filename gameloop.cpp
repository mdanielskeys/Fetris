// gameloop.c

#include "gameloop.h"
#include "Border.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>

unsigned short startTime;
unsigned short tick;

/*


void draw5x5Box(unsigned short x, unsigned short y, unsigned char color)
{
	for (int px = 0; px < 5; px++)
	{
		for (int py = 0; py < 5; py++)
		{
			drawPixel(x + px, y+py, color);
		}
	}
}

void drawTetrino1(unsigned char color)
{
	int x = 30;
	int y = 30;

	draw5x5Box(x, y, color);
	draw5x5Box(x+6, y, color);
	draw5x5Box(x+12, y, color);
	draw5x5Box(x+18, y, color);
}

void drawTetrino2(unsigned char color)
{
	int x = 60;
	int y = 30;

	draw5x5Box(x, y, color);
	draw5x5Box(x+6, y, color);
	draw5x5Box(x, y+6, color);
	draw5x5Box(x+6, y+6, color);
}

void drawTetrino3(unsigned char color)
{
	int x = 80;
	int y = 30;

	draw5x5Box(x, y, color);
	draw5x5Box(x+6, y, color);
	draw5x5Box(x, y+6, color);
	draw5x5Box(x, y+12, color);
}

void drawTetrino4(unsigned char color)
{
	int x = 100;
	int y = 30;

	draw5x5Box(x, y, color);
	draw5x5Box(x, y+6, color);
	draw5x5Box(x+6, y+6, color);
	draw5x5Box(x+6, y+12, color);
}

void drawTetrino5(unsigned char color)
{
	int x = 120;
	int y = 30;

	draw5x5Box(x, y, color);
	draw5x5Box(x+6, y, color);
	draw5x5Box(x+6, y+6, color);
	draw5x5Box(x+12, y, color);
}
*/

GameLoop::GameLoop()
{
	my_clock = (word*)0x046C;	// point to the 18.2hz system close	
}

bool GameLoop::init()
{
	srand (time(NULL));

	if (!graphics.SetGraphicsMode())
	{
		return false;
	}

	// Initilize my graphics objects
	border = new Border(graphics);
	if (border == NULL)
	{
		return false;
	}

	startTime = *my_clock;
	tick = startTime;

	return true;
}

int GameLoop::shutdown()
{
	graphics.SetTextMode();

	return 0;
}

int GameLoop::processInput()
{
	if (kbhit())
	{
		unsigned char key = getch();

		if (key == 'Q' || key == 'q')
		{
			return -1;
		}
	}

	float dt = (*my_clock - tick)/18.2;
	if (dt > 2.0)
	{
		tick = *my_clock;
	}

	return 0;
}

void GameLoop::update()
{
	graphics.ClearScreen();	
	border->Draw();
}

void GameLoop::render()
{
	graphics.FlipVideoBuffer();
}
