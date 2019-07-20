#include "Tetro.h"
#include "defs.h"
#include "PlaySurf.h"
#include <stdlib.h>
#include <stdio.h>

Tetro::Tetro()
{
	Init(0);
}

Tetro::Tetro(int tetrinoType)
{
	Init(tetrinoType);
}

Tetro::Tetro(Tetro &p2)
{
	for (int i = 0; i < 4; i++)
	{
		localp[i].x = p2[i].x;
		localp[i].y = p2[i].y;
	}
	this->_color = p2.color();
	
	TranslateNormal();
}

void Tetro::Init(int tetrinoType)
{
	switch (tetrinoType)
	{
	case 0:
		/*
			Tetrino Shape
				*	
				* * * 
		 */
		localp[0].x = 0; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = 1;
		localp[2].x = 1; localp[2].y = 0;
		localp[3].x = 2; localp[3].y = 0;
		_color =  2;
		break;
	case 1:
		/*
			Tetrino Shape
				* * *
				*     
		 */
		localp[0].x = 0; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = -1;
		localp[2].x = 1; localp[2].y = 0;
		localp[3].x = 2; localp[3].y = 0;
		_color =  3;
		break;
	case 2:
		/*
			Tetrino Shape
				* * * *				     
		 */
		localp[0].x = -1; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = 0;
		localp[2].x = 1; localp[2].y = 0;
		localp[3].x = 2; localp[3].y = 0;
		_color =  4;
		break;
	case 3:
		/*
			Tetrino Shape
				  * 
				* *	*			     
		 */
		localp[0].x = -1; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = 0;
		localp[2].x = 0; localp[2].y = 1;
		localp[3].x = 1; localp[3].y = 0;
		_color =  5;
		break;
	case 4:
		/*
			Tetrino Shape
				* *
				* *				     
		 */
		localp[0].x = 0; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = 1;
		localp[2].x = 1; localp[2].y = 0;
		localp[3].x = 1; localp[3].y = 1;
		_color =  6;
		break;
	case 5:
		/*
			Tetrino Shape
				  *	*
				* *				     
		 */
		localp[0].x = -1; localp[0].y = 0;
		localp[1].x = 0; localp[1].y = 0;
		localp[2].x = 0; localp[2].y = 1;
		localp[3].x = 1; localp[3].y = 1;
		_color =  7;
		break;
	case 6:
		/*
			Tetrino Shape
				* *	
				  * *				     
		 */
		localp[0].x = -1; localp[0].y = 1;
		localp[1].x = 0; localp[1].y = 1;
		localp[2].x = 0; localp[2].y = 0;
		localp[3].x = 1; localp[3].y = 0;
		_color =  8;
		break;
	
	default:
		break;
	}
	TranslateNormal();
}

void Tetro::TranslateNormal()
{
	point transmatrix = {0, 0};

	// calculate the minimums on local points
	for (int i = 0; i < 4; i++)
	{
		if (localp[i].x < transmatrix.x)
		{
			transmatrix.x = localp[i].x;
		}
		if (localp[i].y < transmatrix.y)
		{
			transmatrix.y = localp[i].y;
		}
	}

	// only move if the local cordinates are fall outside of normal
	if (transmatrix.x >= 0 && transmatrix.y >= 0)
	{
		// if local are normal already then set movement to 0
		transmatrix.x = 0;
		transmatrix.y = 0;
	}

	// move the coordinates so that they are normal to zero
	for (int i= 0; i<4; i++)
	{
		// transmatrix should be 0 or negative therefore
		// subtracting the negative is the same as adding
		// the positive
		transp[i].x = localp[i].x - transmatrix.x;
		transp[i].y = localp[i].y - transmatrix.y;
	}
}

Tetro& Tetro::operator=(Tetro& lhs)
{
	for (int i= 0; i< 4; i++)
	{
		lhs[i].x = (*this)[i].x;
		lhs[i].y = (*this)[i].y;
	}
	lhs._color = this->_color;

	return lhs;
}

void Tetro::Rotate()
{
	// Apply rotation matrix to each point
	int rc = 0;
	for(int i=0; i<4; i++)
	{
		// rotate point
		int temp = localp[i].x;
		localp[i].x = localp[i].y;
		localp[i].y = -temp;
	}
	TranslateNormal();
}

