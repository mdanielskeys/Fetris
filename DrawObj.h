#ifndef __DrawObj_h_
#define __DrawObj_h_

class BoGraphics;

class DrawObject {
	const BoGraphics& myGraphics;

public:
	DrawObject(BoGraphics& graphics);
	virtual void Draw();
};

#endif