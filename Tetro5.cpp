#include "Tetro5.h"
#include "Tetro.h"
#include "PlaySurf.h"

Tetro5::Tetro5(PlaySurf *playSurf) : Tetro(playSurf)
{
    color = 6;
}

void Tetro5::DrawTetro()
{
    switch(rotation)
	{
		case 0:
			surface->PlaceGridCell(0,0, color);	surface->PlaceGridCell(0,1,color);	
												surface->PlaceGridCell(1,1,color);
												surface->PlaceGridCell(2,1,color);			
		    maxRow = 2;
			maxCol = 2;
			break;
		case 1:
			surface->PlaceGridCell(0,0,color);	surface->PlaceGridCell(0,1,color);	surface->PlaceGridCell(0,2,color); 
			surface->PlaceGridCell(1,0,color);
			maxRow = 1;
			maxCol = 3;
			break;
		case 2:
			surface->PlaceGridCell(0,0,color);
			surface->PlaceGridCell(1,0,color);	
			surface->PlaceGridCell(2,0,color);	surface->PlaceGridCell(2,1,color);
			maxRow = 2;
			maxCol = 2;
			break;
		case 3:
																					surface->PlaceGridCell(0,2,color);
			surface->PlaceGridCell(1,0,color);	surface->PlaceGridCell(1,1,color);	surface->PlaceGridCell(1,2,color);												
			maxRow = 1;
			maxCol = 3;
			break;
	}
}