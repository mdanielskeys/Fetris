
fetris.exe: fetris.obj bitmap.obj bograph.obj border.obj drawobj.obj gameloop.obj pcx.obj playsurf.obj tetro.obj
	wlink name fetris @fetris

fetris.obj: fetris.cpp
	wpp386 fetris.cpp

bitmap.obj: bitmap.cpp
	wpp386 bitmap.cpp

bograph.obj: bograph.cpp
	wpp386 bograph.cpp

border.obj: border.cpp
	wpp386 border.cpp	

drawobj.obj: drawobj.cpp
	wpp386 drawobj.cpp	

gameloop.obj: gameloop.cpp
	wpp386 gameloop.cpp	

pcx.obj: pcx.cpp
	wpp386 pcx.cpp	

playsurf.obj: playsurf.cpp
	wpp386 playsurf.cpp	

tetro.obj: tetro.cpp
	wpp386 tetro.cpp	
