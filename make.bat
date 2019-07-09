REM Remove the executable and object files
del *.exe
del *.obj
del *.lib

wcl386 fetris.cpp gameloop.cpp boGraph.cpp DrawObj.cpp Border.cpp PlaySurf.cpp Tetro.lib tetro.cpp
