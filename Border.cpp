#include "Border.h"
#include "BoGraph.h"

Border::Border(BoGraphics& graphics) : DrawObject(graphics)
{
}

void DrawObject::Draw()
{
	int tx = 20;
	int ty = 20;
	int bx = 300;
	int by = 190;
	byte color = 8;

	for (word x = 0; x < SCREEN_WIDTH; x++)
	{
		for (word y = 10; y < SCREEN_HEIGHT; y++)
		{
			if (x < tx || x > bx || y < ty || y > by)
			{
				myGraphics.DrawPixel(x, y, color);
			}
		}
	}
}
