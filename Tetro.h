#ifndef __tetro_h_
#define __tetro_h_

class PlaySurf;

typedef struct _point {
	int x;
	int y;
} point, *point_ptr;

typedef point points[4];

class Tetro
{
protected:
	point localp[4];
	point transp[4];
	unsigned char _color;

	void TranslateNormal();
	
public:	
	Tetro();
	Tetro(int tetrinoType);
	Tetro(Tetro &p2);
	void Init(int tetrinoType);
	void Rotate();
	point& operator[](int idx) { return transp[idx]; }
	Tetro& operator=(Tetro& lhs);
	const points& get() const { return transp; }
	unsigned char color() { return _color; }
};

#endif