#ifndef __playsurf_h_
#define __playsurf_h_

#include "defs.h"

class BoGraphics;
class Tetro;

class PlaySurf
{
private:
	const BoGraphics &playGraphics;
	char msg[255];
	Tetro *tetro[5];
	Tetro *currentTetro;
	int currentTetroIndex;
	unsigned char playGrid[GRID_SIZE];
	unsigned char savedGrid[GRID_SIZE];
	void DrawGridCell(int row, int col, unsigned char color);
	void InitGrids();
	void SaveCurrentGrid();
	int CanAdvanceRow();
	int currentRow;
	int currentCol;
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