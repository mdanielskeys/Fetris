#include "Border.h"
#include "BoGraph.h"

Border::Border(BoGraphics& graphics) : DrawObject(graphics)
{
}

void DrawObject::Draw()
{
	int tx = 10;
	int ty = 10;
	byte color = 8;

	// draw top box
	myGraphics.DrawSolidRect(0, 0, SCREEN_WIDTH, ty, color);

	// draw bottom box
	myGraphics.DrawSolidRect(0, SCREEN_HEIGHT - ty, SCREEN_WIDTH, SCREEN_HEIGHT, color);

	// left pillar
	myGraphics.DrawSolidRect(0, ty, tx, SCREEN_HEIGHT, color);

	// right pillar
	myGraphics.DrawSolidRect(SCREEN_WIDTH - tx, ty, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}
