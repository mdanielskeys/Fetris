fetris.exe: ./obj/fetris.obj ./obj/bitmap.obj ./obj/bograph.obj ./obj/border.obj ./obj/drawobj.obj ./obj/gameloop.obj ./obj/pcx.obj ./obj/playsurf.obj ./obj/tetro.obj
	wlink name fetris @fetris

./obj/fetris.obj: fetris.cpp
	wpp386 fetris.cpp -fo=./obj/fetris.obj

./obj/bitmap.obj: bitmap.cpp
	wpp386 bitmap.cpp -fo=./obj/bitmap.obj

./obj/bograph.obj: bograph.cpp
	wpp386 bograph.cpp -fo=./obj/bograph.obj

./obj/border.obj: border.cpp
	wpp386 border.cpp	-fo=./obj/border.obj

./obj/drawobj.obj: drawobj.cpp
	wpp386 drawobj.cpp	-fo=./obj/drawobj.obj

./obj/gameloop.obj: gameloop.cpp
	wpp386 gameloop.cpp	-fo=./obj/gameloop.obj

./obj/pcx.obj: pcx.cpp
	wpp386 pcx.cpp	-fo=./obj/pcx.obj

./obj/playsurf.obj: playsurf.cpp
	wpp386 playsurf.cpp	-fo=./obj/playsurf.obj

./obj/tetro.obj: tetro.cpp
	wpp386 tetro.cpp -fo=./obj/tetro.obj

