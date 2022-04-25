COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

uno-plus: src/main.o src/player.o src/deck.o src/card.o
	$(LINKER) src/*.o -o uno-plus

main.o : src/main.cpp src/player.h src/deck.h src/card.h
	$(COMPILER) $(COMPILER_FLAGS) src/main.cpp

player.o : src/player.cpp src/player.h src/card.h
	$(COMPILER) $(COMPILER_FLAGS) src/player.cpp

deck.o : src/deck.cpp src/deck.h src/card.h
	$(COMPILER) $(COMPILER_FLAGS) src/deck.cpp

card.o : src/card.cpp src/card.h
	$(COMPILER) $(COMPILER_FLAGS) src/card.cpp

clean:
	-rm -f src/*.o uno-plus

