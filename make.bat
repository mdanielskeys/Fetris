REM Remove the executable and object files
del *.exe
del *.obj
del *.lib

wcl386 /d2 fetris.cpp pcx.cpp bitmap.cpp gameloop.cpp boGraph.cpp DrawObj.cpp Border.cpp PlaySurf.cpp tetro.cpp
