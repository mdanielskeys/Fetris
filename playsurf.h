#ifndef __playsurf_h_
#define __playsurf_h_

#include "defs.h"

class BoGraphics;
class pcxfile;
class Tetro;


class PlaySurf
{
private:
	const BoGraphics &playGraphics;
	char msg[255];
	Tetro *tetro[TETRINOS];
	Tetro *currentTetro;
	Tetro *nextTetro;
	pcxfile *playScreen;
	int currentTetroIndex;
	int nextTetroIndex;
	unsigned char playGrid[GRID_SIZE];
	unsigned char savedGrid[GRID_SIZE];
	void DrawGridCell(int row, int col, unsigned char color);
	void SaveCurrentGrid();
	int CanAdvanceRow();
	int currentRow;
	int currentCol;
	int maxRow;
	gamestate state;
	void InitTetroIndex();
	void NextTetroIndex();
	void DrawNextTetro();
	int  score;
	
public:
	PlaySurf(const BoGraphics& graphics);
	~PlaySurf();

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
	void InitGrids();
	void CheckCompleteLines();
	gamestate GetCurrentState() { return state; }
};

#endif