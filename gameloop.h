// game loop steps

#ifndef __gameloop_h_
#define __gameloop_h_

#include "boGraph.h"

class DrawObject;

class GameLoop
{
private:
	const word* my_clock;	// point to the 18.2hz system close

	DrawObject* border;
	BoGraphics graphics;

public:
	GameLoop();
	int processInput();
	void update();
	void render();
	bool init();
	int shutdown();
};

#endif
