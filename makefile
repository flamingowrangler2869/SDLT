all: main

main:
	cc src/*.c -lSDL2 -lm -o bin/sdl && bin/sdl
