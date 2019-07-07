#ifndef __playsurf_h_
#define __playsurf_h_

#include "defs.h"

class BoGraphics;

class PlaySurf
{
private:
	const BoGraphics &playGraphics;
	unsigned char playGrid[GRID_SIZE];
	unsigned char savedGrid[GRID_SIZE];
	void DrawGridCell(int row, int col, unsigned char color);
	void InitGrids();
	void SaveCurrentGrid();
	int currentRow;
	int currentCol;
	int currentRotation;
	int maxRow;

public:
	PlaySurf(const BoGraphics& graphics);

	void PlaceGridCell(int row, int col, unsigned char color);
	void AdvanceRow();
	void MoveLeft();
	void MoveRight();
	void RotateCC();
	void RotateCW();
	void DrawFrame();
	void DrawGrid();
	void DrawTetro();
	void DrawSavedGrid();
};

#endif