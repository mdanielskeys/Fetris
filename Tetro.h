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
	int minX;
	int minY;
	point tpoint[4];
	point zpoint[4];
	unsigned char color;
	void SetZPoints();
	void SetMins();
	void TranslateToZero();
	
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