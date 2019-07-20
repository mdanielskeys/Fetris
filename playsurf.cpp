#include "BoGraph.h"
#include "Tetro.h"
#include "pcx.h"
#include "playsurf.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

PlaySurf::PlaySurf(const BoGraphics& graphics) : playGraphics(graphics) 
{
	currentRow = -1;
	currentCol = 3;
	currentTetroIndex = 0;
	score = 0;

	playScreen = new pcxfile("mscreen.pcx", graphics, 1);

	tetro[0] = new Tetro(0);
	tetro[1] = new Tetro(1);
	tetro[2] = new Tetro(2);
	tetro[3] = new Tetro(3);
	tetro[4] = new Tetro(4);
	tetro[5] = new Tetro(5);
	tetro[6] = new Tetro(6);

	InitGrids();
}

PlaySurf::~PlaySurf()
{
	delete tetro[0];
	delete tetro[1];
	delete tetro[2];
	delete tetro[3];
	delete tetro[4];
	delete tetro[5];
	delete tetro[6];

	delete playScreen;
}

void PlaySurf::InitGrids()
{
	currentRow = -1;
	currentCol = 3;
	score = 0;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		savedGrid[i] = GRID_COLOR;
		playGrid[i] = GRID_COLOR;
	}

	InitTetroIndex();

	state = playing;
}

void PlaySurf::InitTetroIndex()
{
	srand(time(0));
	currentTetroIndex = rand()/(RAND_MAX/TETRINOS);
	if (currentTetroIndex > TETRINOS - 1)
	{
		currentTetroIndex = 0;
	}
	currentTetro = tetro[currentTetroIndex];

	nextTetroIndex = rand()/(RAND_MAX/TETRINOS);
	if (nextTetroIndex > TETRINOS - 1)
	{
		nextTetroIndex = 0;
	}

	if (nextTetro != NULL)
	{
		delete nextTetro;
	}
	nextTetro = new Tetro(nextTetroIndex);
}

void PlaySurf::NextTetroIndex()
{
	score += 10;

	currentTetroIndex = nextTetroIndex;
	currentTetro = tetro[currentTetroIndex];
	currentTetro->Init();

	nextTetroIndex = rand()/(RAND_MAX/TETRINOS);
	if (nextTetroIndex > TETRINOS - 1)
	{
		nextTetroIndex = 0;
	}

	if (nextTetro != NULL)
	{
		delete nextTetro;
	}
	nextTetro = new Tetro(nextTetroIndex);
}

void PlaySurf::DrawFrame()
{
	playScreen->DrawImage();

	DrawNextTetro();

	char msg[10];
	sprintf(msg, "%05d", score);
	playGraphics.Gputs(190, 105, msg, GRID_COLOR, 0);
}

void PlaySurf::DrawNextTetro()
{
	for (int i = 0; i < 4; i++)
	{
		int lx = ((*nextTetro)[i].x * GRID_DIMENSION) + 215;
		int ty = ((*nextTetro)[i].y * GRID_DIMENSION) + 40;
		int rx = lx + CELL_FILL_SIZE;
		int by = ty + CELL_FILL_SIZE;		

		playGraphics.DrawSolidRect(lx, ty, rx, by, nextTetro->color());
	}
}

int PlaySurf::CanAdvanceRow()
{
	int rc = 1; // true

	return rc;
}

void PlaySurf::AdvanceRow()
{
	if (state != playing) return;

	int newrow = currentRow + 1;
	if (newrow < ROWS)
	{
		// copy the current tetro locally
		Tetro localt = *currentTetro;
		
		// translate the copy of the tetro to grid coordinates
		for (int i = 0; i < 4; i++)
		{
			localt[i].x += currentCol;
			localt[i].y += newrow;
		}

		// check if the local translation is still within bounds
		int isOutOfBounds = 0;
		for (int i = 0; i < 4; i++)
		{
			if (localt[i].y > (ROWS - 1)) // out of rows?
			{
				isOutOfBounds = 1;
				break;
			}
			else if (localt[i].x < 0 || localt[i].x > (COLUMNS - 1)) // extend beynd the screen
			{
				isOutOfBounds = 1;
				break;
			}
			else 
			{
				// check if any of the new squares will touch a square already filled in
				unsigned char gridColor = savedGrid[(localt[i].y * COLUMNS) + localt[i].x];
				if (gridColor != GRID_COLOR)
				{
					isOutOfBounds = 1;
					break;
				}
			}
		}

		if (!isOutOfBounds)
		{
			currentRow = newrow;
			DrawTetro();
		}
		else if (currentRow <= 0)
		{
			state = gameover;
		}
		else 
		{
			// copy current grid to saved grid
			SaveCurrentGrid();

			currentRow = 0;
			currentCol = 3;

			NextTetroIndex();
		}
	}
	else if (currentRow <= 0)
	{
		state = gameover;
	}
	else
	{
		// copy current grid to saved grid
		SaveCurrentGrid();

		currentRow = 0;
		currentCol = 3;

		NextTetroIndex();
	}

	DrawSavedGrid();
}

void PlaySurf::MoveRight()
{
	if (state != playing) return;

	int newcol = currentCol + 1;
	if (newcol < COLUMNS)
	{
		// copy the current tetro locally
		Tetro localt = *currentTetro;
		
		// translate the copy of the tetro to grid coordinates
		for (int i = 0; i < 4; i++)
		{
			localt[i].x += newcol;
			localt[i].y += currentRow;
		}

		// check if the local translation is still within bounds
		int isOutOfBounds = 0;
		for (int i = 0; i < 4; i++)
		{
			if (localt[i].y > (ROWS - 1)) // out of rows?
			{
				isOutOfBounds = 1;
				break;
			}
			else if (localt[i].x < 0 || localt[i].x > (COLUMNS - 1)) // extend beynd the screen
			{
				isOutOfBounds = 1;
				break;
			}
			else 
			{
				// check if any of the new squares will touch a square already filled in
				unsigned char gridColor = savedGrid[(localt[i].y * COLUMNS) + localt[i].x];
				if (gridColor != GRID_COLOR)
				{
					isOutOfBounds = 1;
					break;
				}
			}
		}

		if (!isOutOfBounds)
		{
			currentCol = newcol;
			DrawTetro();
		}
	}
}

void PlaySurf::MoveLeft()
{
	if (state != playing) return;

	int newcol = currentCol - 1;
	if (newcol >= 0)
	{
		// copy the current tetro locally
		Tetro localt = *currentTetro;
		
		// translate the copy of the tetro to grid coordinates
		for (int i = 0; i < 4; i++)
		{
			localt[i].x += newcol;
			localt[i].y += currentRow;
		}

		// check if the local translation is still within bounds
		int isOutOfBounds = 0;
		for (int i = 0; i < 4; i++)
		{
			if (localt[i].y > (ROWS - 1)) // out of rows?
			{
				isOutOfBounds = 1;
				break;
			}
			else if (localt[i].x < 0 || localt[i].x > (COLUMNS - 1)) // extend beynd the screen
			{
				isOutOfBounds = 1;
				break;
			}
			else 
			{
				// check if any of the new squares will touch a square already filled in
				unsigned char gridColor = savedGrid[(localt[i].y * COLUMNS) + localt[i].x];
				if (gridColor != GRID_COLOR)
				{
					isOutOfBounds = 1;
					break;
				}
			}
		}

		if (!isOutOfBounds)
		{
			currentCol = newcol;
			DrawTetro();
		}
	}
}

void PlaySurf::RotateCC()
{	
	if (state != playing) return;

	RotateCW();
}

void PlaySurf::RotateCW()
{	
	if (state != playing) return;

	// copy the current tetro locally
	Tetro localt = *currentTetro;
	localt.Rotate();

	// translate the copy of the tetro to grid coordinates
	for (int i = 0; i < 4; i++)
	{
		localt[i].x += currentCol;
		localt[i].y += currentRow;
	}

	// check if the local translation is still within bounds
	int isOutOfBounds = 0;
	for (int i = 0; i < 4; i++)
	{
		if (localt[i].y > (ROWS - 1)) // out of rows?
		{
			isOutOfBounds = 1;
			break;
		}
		else if (localt[i].x < 0 || localt[i].x > (COLUMNS - 1)) // extend beynd the screen
		{
			isOutOfBounds = 1;
			break;
		}
		else 
		{
			// check if any of the new squares will touch a square already filled in
			unsigned char gridColor = savedGrid[(localt[i].y * COLUMNS) + localt[i].x];
			if (gridColor != GRID_COLOR)
			{
				isOutOfBounds = 1;
				break;
			}
		}
	}

	// only rotate and draw if it is not out of bounds
	if (!isOutOfBounds)
	{
		currentTetro->Rotate();
		DrawTetro();
	}
}

void PlaySurf::DrawTetro()
{
	DrawSavedGrid();

	// copy the current tetro locally
	Tetro localt = *currentTetro;

	// translate the copy of the tetro to grid coordinates
	for (int i = 0; i < 4; i++)
	{
		localt[i].x += currentCol;
		localt[i].y += currentRow;
	}

	// check if the local translation is still within bounds
	int isOutOfBounds = 0;
	for (int i = 0; i < 4; i++)
	{
		if (localt[i].y > (ROWS - 1)) // out of rows?
		{
			isOutOfBounds = 1;
			break;
		}
		else if (localt[i].x < 0 || localt[i].x > (COLUMNS - 1)) // extend beynd the screen
		{
			isOutOfBounds = 1;
			break;
		}
		else 
		{
			// check if any of the new squares will touch a square already filled in
			unsigned char gridColor = savedGrid[(localt[i].y * COLUMNS) + localt[i].x];
			if (gridColor != GRID_COLOR)
			{
				isOutOfBounds = 1;
				break;
			}
		}
	}

	if (!isOutOfBounds)
	{
		for(int i=0;i<4; i++)
		{
			PlaceGridCell(localt[i].y, localt[i].x, localt.color());
		}
	}
}

void PlaySurf::PlaceGridCell(int row, int col, unsigned char color)
{
	playGrid[(row*COLUMNS)+col] = color;
}

void PlaySurf::DrawGridCell(int row, int col, unsigned char color)
{
	// calculates the pixel position
	int lx = (col * GRID_DIMENSION) + GRID_LEFT_X;
	int ty = (row * GRID_DIMENSION) + GRID_TOP_Y;
	int rx = lx + CELL_FILL_SIZE;
	int by = ty + CELL_FILL_SIZE;

	playGraphics.DrawSolidRect(lx, ty, rx, by, color);
}

void PlaySurf::DrawSavedGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		playGrid[i] = savedGrid[i];
	}
}

void PlaySurf::SaveCurrentGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		savedGrid[i] = playGrid[i];
	}
}

void PlaySurf::DrawGrid()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			DrawGridCell(row, col, playGrid[(row*COLUMNS)+col]);
		}
	}
}

void PlaySurf::CheckCompleteLines()
{
	// look for all rows completed
	for (int row = ROWS -1 ; row >= 0; row--)
	{
		int rowfilled = 1;
		for (int col = 0; col < COLUMNS; col++)
		{
			// if a square on the row has a grid color then
			// the row is not complete
			if (GRID_COLOR == savedGrid[(row * COLUMNS) + col])
			{
				rowfilled = 0;
				break;
			}
		}

		if (rowfilled)
		{
			score += 100;
			// Remove the row by shifting everyting down
			int filledRow = row;
			int aboveRow = row - 1;
			while (aboveRow >= 0)
			{
				// move the above row into the lower row
				for(int tcol = 0; tcol < COLUMNS; tcol++)
				{
					savedGrid[(filledRow * COLUMNS) + tcol] = savedGrid[(aboveRow * COLUMNS) + tcol];
				}

				// move one row set up the grid
				aboveRow--;
				filledRow--;
			}

			// make the top row blank from the move down
			for(int tcol = 0; tcol < COLUMNS; tcol++)
			{
				savedGrid[tcol] = GRID_COLOR;
			}
			
			// test again
			CheckCompleteLines();
			break;
		}
	}
}