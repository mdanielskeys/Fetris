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
	gameState = SPLASH;
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

	playSurf = new PlaySurf(graphics);

	tetra = *my_clock;

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



		if (gameState == PLAYING)
		{
			if (key == 'Q' || key == 'q')
			{
				gameState = SPLASH;
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
		else
		{
			if (key == 'G' || key == 'g')
			{
				playSurf->InitGrids();
				gameState = PLAYING;
			}
			if (key == 'Q' || key == 'q')
			{
				return -1;
			}
		}
		
	}

	return 0;
}

void GameLoop::update()
{
	if (gameState == PLAYING)
	{
		if (((*my_clock - tetra)/18.2) > .4)
		{
			//playSurf->PlaceGridCell(0,0,4);
			playSurf->AdvanceRow();
			playSurf->DrawTetro();
			tetra = *my_clock;
		}
	}
}

void GameLoop::render()
{
	graphics.ClearScreen();	
	border->Draw();

	if (gameState == PLAYING)
	{
		if (playSurf != NULL)
		{
			playSurf->DrawFrame();
			playSurf->DrawGrid();
		}
	}
	else
	{
		char * msg1 = "Press 'G' to start the game.";
		char * msg2 = "Press 'Q' to quit.";
		char * msg = "Fetris - A Poor Tetris Clone";
		graphics.Gputs(160 - (8*strlen(msg))/2, 50, msg, 2, 0);
		graphics.Gputs(160 - (8*strlen(msg1))/2, 100, msg1, 3, 0);
		graphics.Gputs(160 - (8*strlen(msg2))/2, 110, msg2, 3, 0);
	}
	

	graphics.FlipVideoBuffer();
}
