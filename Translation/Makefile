CMP = g++
FLAGS = -std=c++14 -Wall 
MAIN = translate
EXEC = runtranslate

$(EXEC): $(MAIN).o
		$(CMP) $(FLAGS) $(MAIN).o -o $(EXEC)

$(MAIN).o: $(MAIN).cpp
		$(CMP) $(FLAGS) -c $(MAIN).cpp -o $(MAIN).o

clean:
		rm *.o
		rm $(EXEC)
