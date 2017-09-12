CXX=g++ -std=c++11
OBJS=sprite.o window.o main.o random.o fish.o ai.o shark.o
LFLAGS=-lSDL2 -lSDL2_image
DEPS=Lab309_ADT_Container.h Lab309_ADT_DoublyLinkedList.h Lab309_ADT_Matrix.h

%.o: %.cpp $(DEPS)
	$(CXX) -c $< $(LFLAGS)
	
main: $(OBJS)
	$(CXX) -o main $(OBJS) $(LFLAGS)
	
clean:
	rm -f *.o
	rm -f main
