// gameloop.c

#include "gameloop.h"
#include "Border.h"
#include "PlaySurf.h"
#include "defs.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

GameLoop::GameLoop()
{
	state = splash;
	my_clock = (word*)0x046C;	// point to the 18.2hz system close	
}

GameLoop::~GameLoop()
{
	if (playSurf != NULL)
	{
		delete playSurf;
	}

	if (startScreen != NULL)
	{
		delete startScreen;
	}
}

bool GameLoop::init()
{
	srand (time(NULL));

	if (!graphics.SetGraphicsMode())
	{
		return false;
	}

	// Initilize my graphics objects
	//border = new Border(graphics);
	//if (border == NULL)
	//{
	//	return false;
	//}

	playSurf = new PlaySurf(graphics);
	//startScreen = new bitmapfile("title.bmp");
	SavePalette();
	startScreen = new pcxfile("title.pcx", graphics, 1);

	tetra = *my_clock;

	return true;
}

void GameLoop::SavePalette()
{
	for (int i=0;i<256;i++)
	{
		graphics.ReadPaletteRegister(i, &defaultPalette[i]);
	}
}

void GameLoop::LoadPalette(RGB_color *palette)
{
	for (int i=0; i<256; i++)
	{
		graphics.SetPaletteRegister(i, palette + i);
	}
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



		if (state == playing)
		{
			if (int(key) == ESC) // escape key pressed
			{
				state = splash;
				startScreen->LoadPalette();
			}
			if (key == 'd')
			{
				playSurf->MoveRight();
			}
			if (key == 'a')
			{
				playSurf->MoveLeft();
			}
			if (key == 'e')
			{
				playSurf->RotateCC();		
			}
			if (key == 'w')
			{
				playSurf->RotateCW();
			}
		}
		else if (state == gameover)
		{
			if (key == 'Q' || key == 'q' || int(key) == ESC)
			{
				state = splash;
				startScreen->LoadPalette();
			}
			if (key == 'G' || key == 'g')
			{
				playSurf->InitGrids();
				state = playing;
			}
		}
		else
		{
			if (key == 'G' || key == 'g')
			{
				playSurf->InitGrids();
				state = playing;
			}
			if (key == 'Q' || key == 'q' || int(key) == ESC)
			{
				return -1;
			}
		}
		
	}

	return 0;
}

void GameLoop::update()
{
	if (state == playing)
	{
		if (((*my_clock - tetra)/18.2) > .3)
		{
			playSurf->AdvanceRow();
			if (playSurf->GetCurrentState() == gameover)
			{
				state = gameover;
			}
			playSurf->CheckCompleteLines();
			playSurf->DrawTetro();

			tetra = *my_clock;
		}
	}
}

void GameLoop::render()
{
	graphics.ClearScreen();	

	if (state == playing)
	{
		if (playSurf != NULL)
		{
			playSurf->DrawFrame();
			playSurf->DrawGrid();
		}
	}
	else if (state == gameover)
	{
		char msg[255];
		sprintf(msg, "Game Over");
		playSurf->DrawFrame();
		playSurf->DrawGrid();
		graphics.Gputs(100, 100, msg, 4, 0);
	}
	else
	{
		startScreen->DrawImage();
	}
	

	graphics.FlipVideoBuffer();
}
