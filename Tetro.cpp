#include "Tetro.h"
#include "defs.h"
#include <stdlib.h>

	Tetro::Tetro()
	{
		color = rand()%256 + 1;
	}

	Tetro::~Tetro()
	{
	}

	void Tetro::RotateCW()
	{

	}

	void Tetro::RotateCC()
	{

	}

	void Tetro::MoveLeft()
	{
		if (column - 1 > 0)
		{
			column -= 1;
		}
	}

	void Tetro::MoveRight()
	{
		if (column + 1 < COLUMNS )
		{
			column += 1;
		}
	}

	void Tetro::AdvanceVertical()
	{		
		if (row + 1 < ROWS)
		{
			row += 1;
		}
	}

