#include "Tetro2.h"
#include "Tetro.h"
#include "PlaySurf.h"

Tetro2::Tetro2(PlaySurf *playSurf) : Tetro(playSurf)
{
	color = 3;
}

void Tetro2::DrawTetro()
{
    switch(rotation)
	{
		case 0:
		case 1:
			surface->PlaceGridCell(0,0, color);	surface->PlaceGridCell(0,1,color);	surface->PlaceGridCell(0,2,color); surface->PlaceGridCell(0,3,color);			
		    maxRow = 0;
			maxCol = 4;
			break;
		case 2:
		case 3:
			surface->PlaceGridCell(0,0,color);
			surface->PlaceGridCell(1,0,color);	
			surface->PlaceGridCell(2,0,color);
			surface->PlaceGridCell(3,0,color);
			maxRow = 3;
			maxCol = 1;
			break;
	}
}