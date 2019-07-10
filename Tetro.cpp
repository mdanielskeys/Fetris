#include "Tetro.h"
#include "defs.h"
#include "PlaySurf.h"
#include <stdlib.h>

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
		tpoint[1].x = 1; tpoint[1].y = 0;
		tpoint[2].x = 2; tpoint[2].y = 0;
		tpoint[3].x = 2; tpoint[3].y = 1;
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
		tpoint[1].x = 1; tpoint[1].y = 0;
		tpoint[2].x = 2; tpoint[2].y = 0;
		tpoint[3].x = 2; tpoint[3].y = -1;
		color =  3;
		maxRow = 1;
		maxCol = 2;
		break;
	case 2:
		/*
			Tetrino Shape
				* * * *				     
		 */
		tpoint[0].x = 0; tpoint[0].y = 0;
		tpoint[1].x = 1; tpoint[1].y = 0;
		tpoint[2].x = 2; tpoint[2].y = 0;
		tpoint[3].x = 3; tpoint[3].y = 0;
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
		tpoint[0].x = 0; tpoint[0].y = 0;
		tpoint[1].x = 1; tpoint[1].y = 0;
		tpoint[2].x = 2; tpoint[2].y = 0;
		tpoint[3].x = 1; tpoint[3].y = 1;
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
	
	default:
		break;
	}
	SetZPoints();		
}

void Tetro::SetZPoints()
{
	for(int i=0;i<4;i++)
	{
		zpoint[i].x = tpoint[i].x;
		zpoint[i].y = tpoint[i].y;
	}
	SetMins();
	TranslateToZero();
}

void Tetro::TranslateToZero()
{
	int tranx = 0;
	int trany = 0;

	if (minX < tranx)
	{
		tranx = abs(minX);
	}
	if (minY < trany)
	{
		trany = abs(minY);
	}
	
	maxCol = 0;
	maxRow = 0;
	// translate points back to 0
	for(int i=0; i<4; i++)
	{
		zpoint[i].x += tranx;
		zpoint[i].y += trany;
		if (maxRow < zpoint[i].y)
		{
			maxRow = zpoint[i].y;
		}
		if (maxCol < zpoint[i].x)
		{
			maxCol = zpoint[i].x;
		}
	}

}

void Tetro::SetMins()
{
	minX = 0;
	minY = 0;

	for(int i=0;i<4;i++)
	{
		if (zpoint[i].x < minX)
		{
			minX = zpoint[i].x;
		}	

		if (zpoint[i].y < minY)
		{
			minY = zpoint[i].y;
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

int Tetro::GetMaxRow()
{
	return maxRow;
}

int Tetro::GetMaxCol()
{
	return maxCol + 1;
}

void Tetro::Rotate()
{
	minX = 0;
	minY = 0;

	// Apply rotation matrix to each point
	for(int i=0; i<4; i++)
	{
		// rotate point
		int newX = -1 * tpoint[i].y;
		int newY = tpoint[i].x;

		// keep track of minimums to translate after
		if (newX < minX)
		{
			minX = newX;
		}

		if (newY < minY)
		{
			minY = newY;
		}

		tpoint[i].x = newX;
		tpoint[i].y = newY;
	}

	SetZPoints();
	TranslateToZero();
}

void Tetro::DrawTetro()
{
	for (int i = 0; i < 4; i++)
	{
		surface->PlaceGridCell(zpoint[i].y, zpoint[i].x, color);
	}
}