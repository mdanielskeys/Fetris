wpp386 tetro.cpp 
wpp386 tetro1.cpp 
wpp386 tetro2.cpp 
wpp386 tetro3.cpp 
wpp386 tetro4.cpp 
wpp386 tetro5.cpp

del tetro.lib
wlib tetro +tetro +tetro1 +tetro2 +tetro3 +tetro4 +tetro5

wcl386 breakout.cpp gameloop.cpp boGraph.cpp DrawObj.cpp Border.cpp PlaySurf.cpp Tetro.lib
