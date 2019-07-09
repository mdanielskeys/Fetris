#include "tetro3.h"
#include "Tetro.h"
#include "PlaySurf.h"

Tetro3::Tetro3(PlaySurf *playSurf) : Tetro(playSurf)
{
	color = 4;
}

void Tetro3::DrawTetro()
{
    switch(rotation)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			surface->PlaceGridCell(0,0, color);	surface->PlaceGridCell(0,1,color);	
			surface->PlaceGridCell(1,0,color); surface->PlaceGridCell(1,1,color);			
		    maxRow = 1;
			maxCol = 2;
			break;
	}
}