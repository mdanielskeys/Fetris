breakout: breakout.obj
	wlink breakout.obj 

breakout.obj: breakout.cpp
	wpp386 breakout.cpp