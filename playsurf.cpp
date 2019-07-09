#include "BoGraph.h"
#include "Tetro.h"
#include "Tetro1.h"
#include "Tetro2.h"
#include "Tetro3.h"
#include "tetro4.h"
#include "tetro5.h"
#include "playsurf.h"
#include <stdio.h>

PlaySurf::PlaySurf(const BoGraphics& graphics) : playGraphics(graphics) 
{
	currentRow = -1;
	currentCol = 3;
	maxRow = 0;
	currentTetroIndex = 0;
	InitGrids();

	tetro[0] = new Tetro1(this);
	tetro[1] = new Tetro2(this);
	tetro[2] = new Tetro3(this);
	tetro[3] = new Tetro4(this);
	tetro[4] = new Tetro5(this);

	currentTetro = tetro[currentTetroIndex];
}

void PlaySurf::InitGrids()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		savedGrid[i] = 1;
		playGrid[i] = 1;
	}

}

void PlaySurf::DrawFrame()
{
	playGraphics.DrawRect(FRAME_LEFT_X, FRAME_TOP_Y, FRAME_RIGHT_X, FRAME_BOTTOM_Y, FRAME_COLOR);
}

int PlaySurf::CanAdvanceRow()
{
	int rc = 1; // true
	rc = currentRow + currentTetro->GetMaxRow() < (ROWS - 1);

	// for each next cell in the tetrino
	return rc;
}

void PlaySurf::AdvanceRow()
{
	if (CanAdvanceRow())
	{
		currentRow += 1;
	}
	else
	{
		// copy current grid to saved grid
		SaveCurrentGrid();

		currentRow = 0;
		currentCol = 3;
		currentTetroIndex += 1;
		if (currentTetroIndex > 4)
		{
			currentTetroIndex = 0;
		}
		currentTetro = tetro[currentTetroIndex];
	}

	DrawSavedGrid();
}

void PlaySurf::MoveRight()
{
	if (currentCol + 1 <= (COLUMNS - currentTetro->GetMaxCol()))
	{
		currentCol += 1;
	}
	DrawTetro();
}

void PlaySurf::MoveLeft()
{
	if (currentCol - 1 >= 0)
	{
		currentCol -= 1;
	}
	DrawTetro();
}

void PlaySurf::RotateCC()
{
	int currentRotation  = currentTetro->GetRotation();

	if (currentRotation + 1 <= 3)
	{
		currentRotation += 1;
	}
	else
	{
		currentRotation = 0;
	}
	currentTetro->SetRotation(currentRotation);
	DrawTetro();
}

void PlaySurf::RotateCW()
{
	int currentRotation  = currentTetro->GetRotation();
	if (currentRotation - 1 >= 0)
	{
		currentRotation -= 1;
	}
	else
	{
		currentRotation = 3;
	}
	currentTetro->SetRotation(currentRotation);
	DrawTetro();
}

void PlaySurf::DrawTetro()
{
	DrawSavedGrid();

	currentTetro->DrawTetro();
}

void PlaySurf::PlaceGridCell(int row, int col, unsigned char color)
{
	int rowOffset = row + currentRow;
	int colOffset = col + currentCol;
	playGrid[(rowOffset*COLUMNS)+colOffset] = color;
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
	sprintf(msg,"currentTetroIndex %d					\n", currentTetroIndex);
	playGraphics.Gputs(1, 1, msg, 15, 0);
}
