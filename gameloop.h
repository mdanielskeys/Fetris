// game loop steps

#ifndef __gameloop_h_
#define __gameloop_h_

#include "boGraph.h"
#include "bitmap.h"
#include "pcx.h"

class DrawObject;
class PlaySurf;

class GameLoop
{
private:
	const word* my_clock;	// point to the 18.2hz system close

	word tetra;

	//bitmapfile *startScreen;
	pcxfile *startScreen;
	DrawObject* border;
	BoGraphics graphics;
	PlaySurf*  playSurf;	
	int gameState; // 0 - splash 1 - playing
	int NoAdvance;
	RGB_color defaultPalette[256];

	void SavePalette();
	void LoadPalette(RGB_color *palette);
	
public:
	GameLoop();
	int processInput();
	void update();
	void render();
	bool init();
	int shutdown();
};

#endif
