#include "BoGraph.h"
#include "Tetro.h"
#include "playsurf.h"
#include <stdio.h>

PlaySurf::PlaySurf(const BoGraphics& graphics) : playGraphics(graphics) 
{
	currentRow = -1;
	currentCol = 3;
	maxRow = 0;
	currentTetroIndex = 0;
	InitGrids();

	tetro[0] = new Tetro(this, 0);
	tetro[1] = new Tetro(this, 1);
	tetro[2] = new Tetro(this, 2);
	tetro[3] = new Tetro(this, 3);
	tetro[4] = new Tetro(this, 4);
	tetro[5] = new Tetro(this, 5);
	tetro[6] = new Tetro(this, 6);

	currentTetro = tetro[currentTetroIndex];
}

void PlaySurf::InitGrids()
{
	currentRow = -1;
	currentCol = 3;
	currentTetroIndex = 0;
	
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
	int rc = currentTetro->IsDrawingOnScreen(currentRow+1, ROWS); // true

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
		if (currentTetroIndex > TETRINOS)
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
	currentTetro->Rotate();

	DrawTetro();
}

void PlaySurf::RotateCW()
{
	currentTetro->Rotate();

	DrawTetro();
}

void PlaySurf::DrawTetro()
{
	DrawSavedGrid();

	// brace the tetro to the side
	if (currentCol + currentTetro->GetMaxCol() > COLUMNS)
	{
		currentCol = COLUMNS - currentTetro->GetMaxCol();
	} 
	if (currentRow + currentTetro->GetMinRow() < 0)
	{
		currentRow += currentRow - currentTetro->GetMinRow();
	}

	currentTetro->DrawTetro();
}

void PlaySurf::PlaceGridCell(int row, int col, unsigned char color)
{
	int rowOffset = row + currentRow;
	int colOffset = col + currentCol;
	if (rowOffset < 0)
	{
		rowOffset = 0;
	}
	if (rowOffset > ROWS)
	{
		rowOffset = ROWS;
	}
	if (colOffset < 0)
	{ 
		colOffset = 0;
	}
	if (colOffset > COLUMNS - 1)
	{
		colOffset = COLUMNS - 1;
	}
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
	sprintf(msg,"%s cRow %d cCol %d", currentTetro->PositionMsg(), currentRow, currentCol);
	playGraphics.Gputs(1, 1, msg, 15, 0);
}
