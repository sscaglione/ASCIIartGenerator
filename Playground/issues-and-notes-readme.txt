 Using this to compile (not sure if this is a correct method but it seems to compile)
 Reference Manual: http://www.itgroup.ro/WSX/wsx_content/en/tutorials/Magick++/Magick++_tutorial.pdf
-------------------------USING THIS TO COMPILE WITH MAGICK++--------
g++ `Magick++-config --cxxflags --cppflags` -o try grayscaletotext.cpp `Magick++-config --ldflags --libs`
---------------------------------------------------------------------

Getting the error: error while loading shared libraries: libMagick++.so.4: cannot open shared object file: No such file or directory
	--FIXED
When I locate libMagick++ only the libMagick++.so.2 and libMagick.so.2.0.0 are shown
	--FIXED: Talked to MadDog and he installed the correct libraries
