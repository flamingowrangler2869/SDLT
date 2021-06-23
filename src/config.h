#ifndef CONFIG_H
#define CONFIG_H

SDL_Event event;

// window width and height
#define WIN_WIDTH  800
#define WIN_HEIGHT 800

// centers of the window
#define cx WIN_WIDTH/2
#define cy WIN_HEIGHT/2

// map objects
#define P -1	// player start
#define W 1		// wall
#define R 2		// red tile
#define G 3		// green tile
#define B 4		// blue tile
#define V 5 	// light grey tile

// map size
#define mw WIN_WIDTH/rw
#define mh WIN_HEIGHT/rh

// tile size
#define RECT_SIZE 50
#define rw RECT_SIZE
#define rh RECT_SIZE

#endif /* CONFIG_H */
