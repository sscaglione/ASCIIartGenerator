# Gives location for header files to include and imagemagick library
IPATH= /afs/nd.edu/user37/ccl/software/external/imagemagick/include/ImageMagick
LPATH= /afs/nd.edu/user37/ccl/software/external/imagemagick/lib
LIBARGS= -L$(LPATH) -lMagick++ -lMagickCore -lMagickWand
TARGET= asciify
FLAGS= -Wall -std=c++11

all: $(TARGET)

$(TARGET): asciify.o translate.o
	@echo Linking to ImageMagick libraries...
	@g++ -o $@ $^ $(FLAGS) $(LIBARGS)
	@echo Run the ASCII art converter with \'$(TARGET)\'
	@echo If the program returns \"error while loading shared libraries\", please add the ImageMagick library directory to your LD_LIBRARY_PATH:
	@echo sh: LD_LIBRARY_PATH=$(LPATH):\$$LD_LIBRARY_PATH
	@echo bash: export LD_LIBRARY_PATH=$(LPATH):\$$LD_LIBRARY_PATH
	@echo csh: setenv LD_LIBRARY_PATH \"$(LPATH):\$$LD_LIBRARY_PATH\"

asciify.o: asciify.cpp asciify.h
	@echo Compiling $@...
	@g++ -c -o $@ $< $(FLAGS)

translate.o: translate.cpp asciify.h
	@echo Compiling $@...
	@g++ -c -o $@ $< $(FLAGS) -I $(IPATH)

clean:
	@echo Cleaning...
	@rm -f $(TARGET) *.o
