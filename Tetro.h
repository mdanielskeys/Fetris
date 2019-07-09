#ifndef __tetro_h_
#define __tetro_h_

class PlaySurf;

typedef struct _point {
	int x;
	int y;
} point;

class Tetro
{
protected:
	int rotation;			// how the tetrino is rotate 0 - 3
	int maxRow;
	int maxCol;
	point tpoint[4];
	unsigned char color;

	PlaySurf* surface;

public:
	Tetro(PlaySurf *playSurf, int tetrinoType);
	int GetRotation();
	void SetRotation(int rot);
	int GetMaxRow();
	int GetMaxCol();
	void Rotate();

public:
	virtual void DrawTetro();

};

#endif