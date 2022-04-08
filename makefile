all: tetris

tetris: tetris.o primlib.o
	gcc -fsanitize=undefined -g $^ -o $@ -lm -lSDL2_gfx `sdl2-config --libs`

.c.o: 
	gcc -fsanitize=undefined -g -Wall -pedantic `sdl2-config --cflags` -c  $<

primlib.o: primlib.c primlib.h

tetris.o: tetris.c primlib.h

clean:
	-rm primlib.o tetris.o tetris	
