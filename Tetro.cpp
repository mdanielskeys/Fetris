#include "Tetro.h"
#include "defs.h"
#include "PlaySurf.h"
#include <stdlib.h>
#include <stdio.h>

Tetro::Tetro(PlaySurf *playSurf, int tetrinoType)
{
	rotation = 0;
	minX = 0;
	minY = 0;
	surface = playSurf;

	switch (tetrinoType)
	{
	case 0:
		/*
			Tetrino Shape
				*	
				* * * 
		 */
		tpoint[0].x = 0; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = 1;
		tpoint[2].x = 1; tpoint[2].y = 0;
		tpoint[3].x = 2; tpoint[3].y = 0;
		color =  2;
		maxRow = 1;
		maxCol = 2;
		break;
	case 1:
		/*
			Tetrino Shape
				* * *
				*     
		 */
		tpoint[0].x = 0; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = -1;
		tpoint[2].x = 1; tpoint[2].y = 0;
		tpoint[3].x = 2; tpoint[3].y = 0;
		color =  3;
		maxRow = 1;
		maxCol = 2;
		break;
	case 2:
		/*
			Tetrino Shape
				* * * *				     
		 */
		tpoint[0].x = -1; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = 0;
		tpoint[2].x = 1; tpoint[2].y = 0;
		tpoint[3].x = 2; tpoint[3].y = 0;
		color =  4;
		maxRow = 0;
		maxCol = 3;
		break;
	case 3:
		/*
			Tetrino Shape
				  * 
				* *	*			     
		 */
		tpoint[0].x = -1; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = 0;
		tpoint[2].x = 0; tpoint[2].y = 1;
		tpoint[3].x = 1; tpoint[3].y = 0;
		color =  5;
		maxRow = 1;
		maxCol = 2;
		break;
	case 4:
		/*
			Tetrino Shape
				* *
				* *				     
		 */
		tpoint[0].x = 0; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = 1;
		tpoint[2].x = 1; tpoint[2].y = 0;
		tpoint[3].x = 1; tpoint[3].y = 1;
		color =  6;
		maxRow = 1;
		maxCol = 1;
		break;
	case 5:
		/*
			Tetrino Shape
				  *	*
				* *				     
		 */
		tpoint[0].x = -1; tpoint[0].y = 0;
		tpoint[1].x = 0; tpoint[1].y = 0;
		tpoint[2].x = 0; tpoint[2].y = 1;
		tpoint[3].x = 1; tpoint[3].y = 1;
		color =  7;
		maxRow = 1;
		maxCol = 1;
		break;
	case 6:
		/*
			Tetrino Shape
				* *	
				  * *				     
		 */
		tpoint[0].x = -1; tpoint[0].y = 1;
		tpoint[1].x = 0; tpoint[1].y = 1;
		tpoint[2].x = 0; tpoint[2].y = 0;
		tpoint[3].x = 1; tpoint[3].y = 0;
		color =  8;
		maxRow = 1;
		maxCol = 1;
		break;
	
	default:
		break;
	}
	SetMins();
	SetMaxs();
}

char * Tetro::PositionMsg()
{
	sprintf(msg, "coords: %d,%d %d,%d %d,%d %d,%d", 
					tpoint[0].x, tpoint[0].y,
					tpoint[1].x, tpoint[1].y,
					tpoint[2].x, tpoint[2].y,
					tpoint[3].x, tpoint[3].y
	);

	return msg;
}

int Tetro::IsDrawingOnScreen(int row, int LAST_ROW)
{
	int rc = 1;

	for (int i=0;i < 4; i++)
	{
		if (row + (tpoint[i].y - maxRow) >= LAST_ROW)
		{
			rc = 0;
			break;
		}
	}

	return rc;
}

int Tetro::WillTetroCollide(int row, int column, unsigned char* playGrid)
{
	int rc = 0;

	for (int i=0;i < 4; i++)
	{
		if (DoesBrickCollide(tpoint[i], row, column, playGrid))
		{
			rc = 1;
			break;
		}
	}

	return rc;
}

int Tetro::DoesBrickCollide(const point& brick, int row, int column, unsigned char* playGrid)
{
	int rc = 0;
	int dy = row + (brick.y - maxRow);
	if (dy < 0)
	{
		dy = 0;
	}
	int dx = column + (brick.x + abs(minX));
	if (playGrid[dy * COLUMNS + dx] != GRID_COLOR)
	{
		rc = 1;
	}

	return rc;
}

void Tetro::SetMaxs()
{
	maxCol = 0;
	maxRow = 0;
	// translate points back to 0
	for(int i=0; i<4; i++)
	{
		if (maxRow < tpoint[i].y)
		{
			maxRow = tpoint[i].y;
		}
		if (maxCol < tpoint[i].x)
		{
			maxCol = tpoint[i].x;
		}
	}
}

void Tetro::SetMins()
{
	minX = 0;
	minY = 0;

	for(int i=0;i<4;i++)
	{
		if (tpoint[i].x < minX)
		{
			minX = tpoint[i].x;
		}	

		if (tpoint[i].y < minY)
		{
			minY = tpoint[i].y;
		}
	}
}

int Tetro::GetRotation()
{
	return rotation;
}

void Tetro::SetRotation(int rot)
{
	rotation = rot;
}

int Tetro::GetMinRow()
{
	return minY;
}

int Tetro::GetMaxRow()
{
	return maxRow;
}

int Tetro::GetMaxCol()
{
	return maxCol + 1;
}

void Tetro::Rotate(int row, int column, unsigned char* playGrid)
{
	// Apply rotation matrix to each point
	int rc = 0;
	point newPos[4];
	for(int i=0; i<4; i++)
	{
		// rotate point
		newPos[i].x = tpoint[i].y;
		newPos[i].y = -tpoint[i].x;

		rc = DoesBrickCollide(newPos[i], row, column, playGrid);
		if (rc)
		{
			break;
		}
	}

	if (!rc)
	{
		for (int i=0; i<4; i++)
		{
			tpoint[i].x = newPos[i].x;
			tpoint[i].y = newPos[i].y;
		}

		SetMaxs();
		SetMins();
	}
}

void Tetro::DrawTetro()
{
	for (int i = 0; i < 4; i++)
	{
		int tx = tpoint[i].x + abs(minX);
		int ty = tpoint[i].y - maxRow;
		surface->PlaceGridCell(ty, tx, color);
	}
}