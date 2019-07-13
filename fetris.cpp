// tetris game 

#include "gameloop.h"

int main(int argc, char *argv[])
{
	GameLoop game;

	if (game.init())
	{
		while(1)
		{
			if (game.processInput() < 0)
			{
				break;
			}

			game.update();
			game.render();
		}
		
		game.shutdown();		
	}
	
	return 0;
}
