all: main

main:
	cc sdl.c utils.c -lSDL2 -lm -o sdl && ./sdl
