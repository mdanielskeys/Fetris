// game loop steps

#ifndef __gameloop_h_
#define __gameloop_h_

#include "boGraph.h"

class DrawObject;
class PlaySurf;

class GameLoop
{
private:
	const word* my_clock;	// point to the 18.2hz system close

	word tetra;

	DrawObject* border;
	BoGraphics graphics;
	PlaySurf*  playSurf;	

public:
	GameLoop();
	int processInput();
	void update();
	void render();
	bool init();
	int shutdown();
};

#endif
