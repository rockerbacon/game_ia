CXX=g++ -std=c++11
OBJS=sprite.o window.o main.o
LFLAGS=-lSDL2 -lSDL2_image

%.o: %.cpp
	$(CXX) -c $^ $(LFLAGS)
	
main: $(OBJS)
	$(CXX) -o main $(OBJS) $(LFLAGS)
	
clean:
	rm -f *.o
