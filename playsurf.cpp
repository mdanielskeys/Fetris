#include "BoGraph.h"
#include "playsurf.h"

PlaySurf::PlaySurf(const BoGraphics& graphics) : playGraphics(graphics) 
{
	currentRow = -1;
	currentCol = 0;
	currentRotation = 0;
	maxRow = 0;
	InitGrids();
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

void PlaySurf::AdvanceRow()
{
	if (currentRow + maxRow < (ROWS - 1))
	{
		currentRow += 1;
	}
	else
	{
		// copy current grid to saved grid
		SaveCurrentGrid();
		currentRow = 0;
	}

	DrawSavedGrid();
}

void PlaySurf::MoveRight()
{
	if (currentCol + 1 <= (COLUMNS - 3))
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
	if (currentRotation + 1 <= 3)
	{
		currentRotation += 1;
	}
	else
	{
		currentRotation = 0;
	}
	DrawTetro();
}

void PlaySurf::RotateCW()
{
	if (currentRotation - 1 >= 0)
	{
		currentRotation -= 1;
	}
	else
	{
		currentRotation = 3;
	}
	DrawTetro();
}

void PlaySurf::DrawTetro()
{
	DrawSavedGrid();
	switch(currentRotation)
	{
		case 0:
			PlaceGridCell(0,0, 4); PlaceGridCell(0,1,4); PlaceGridCell(0,2,4);
							   PlaceGridCell(1,1,4);			
		    maxRow = 1;
			break;
		case 1:
			PlaceGridCell(0,0,4);
			PlaceGridCell(1,0,4); PlaceGridCell(1,1,4);
			PlaceGridCell(2,0,4);
			maxRow = 2;
			break;
		case 2:
							   PlaceGridCell(0,1,4);
			PlaceGridCell(1,0,4); PlaceGridCell(1,1,4); PlaceGridCell(1,2,4);
			maxRow = 1;
			break;
		case 3:
								PlaceGridCell(0,1,4);
			PlaceGridCell(1,0,4);	PlaceGridCell(1,1,4);
								PlaceGridCell(2,1,4);
			maxRow = 2;
			break;
	}
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
}
