#ifndef __tetro_h_
#define __tetro_h_

class PlaySurf;

class Tetro
{
protected:
	int rotation;			// how the tetrino is rotate 0 - 3
	int maxRow;
	int maxCol;
	unsigned char color;

	PlaySurf* surface;

public:
	Tetro(PlaySurf *playSurf);
	int GetRotation();
	void SetRotation(int rot);
	int GetMaxRow();
	int GetMaxCol();

public:
	virtual void DrawTetro() = 0;

};

#endif