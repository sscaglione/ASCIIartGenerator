CMP = g++
FLAGS = -std=c++14 -Wall
MCMP = c++
MAGICK1 = `Magick++-config --cxxflags --cppflags`
MAGICK2 = `Magick++-config --ldflags --libs`
CLASS = functions
MAIN = asciiconverter
EXEC = runascii

$(EXEC): $(CLASS).o $(MAIN).cpp
		$(MCMP) $(MAGICK1) -O2 -o $(EXEC) $(MAIN).cpp \
			$(MAGICK2)

$(CLASS).o: $(CLASS).cpp
		$(CMP) $(FLAGS) -c $(CLASS).cpp -o $(CLASS).o

clean:
		rm *.o
		rm $(EXEC)
