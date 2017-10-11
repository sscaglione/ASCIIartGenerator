CMP = c++
MAGICK1 = `Magick++-config --cxxflags --cppflags`
MAGICK2 = `Magick++-config --ldflags --libs`
MAIN = magicktest
EXEC = runmagick

$(EXEC): $(MAIN).cpp
		$(CMP) $(MAGICK1) -O2 -o $(EXEC) $(MAIN).cpp \
			$(MAGICK2)

clean:
		rm *.o
		rm $(EXEC)
