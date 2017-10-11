FLAGS = -lpython2.7
PYEMB = python_embedder
TARGET = test_py
$(TARGET): $(TARGET).cpp $(PYEMB).cpp $(PYEMB).h
	g++ -o $@ $(TARGET).cpp $(PYEMB).cpp $(FLAGS)

clean:
	rm $(TARGET)
