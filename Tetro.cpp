#include "Tetro.h"
#include "defs.h"
#include "PlaySurf.h"
#include <stdlib.h>

Tetro::Tetro(PlaySurf *playSurf)
{
	rotation = 0;
	surface = playSurf;
	color = rand()%256 + 1;
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
	return maxCol;
}
