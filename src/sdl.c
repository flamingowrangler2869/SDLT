#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "utils.h"
#include "gfx.h"
#include "config.h"

const char map[16][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,P,W,R,G,B,V,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,W,W,W,W,W,W,W,W,W,W,W,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

char collision(int plrX, int plrY, const char map[16][16]) {
	for (int x = 0; x < mw; x++) {
		for (int y = 0; y < mh; y++) {
			if (map[x][y] != 0) {
				if (x - plrX == rw) return 1; // player is on the right
				if (plrX - x == rw) return 2; // player is on the left
				if (y - plrY == rh) return 3; // player is above
				if (plrY - y == rh) return 4; // player is below
			}
		}
	}
}

int main() {

	initGFX("window", WIN_WIDTH, WIN_HEIGHT);

	// if P is on the map, the player
	// starts there; otherwise,
	// it starts in the middle
	int plrW = rw;
	int plrH = rh;
	int plrX = cx;
	int plrY = cy;
	for (int x = 0; x < mw; x++) {
		for (int y = 0; y < mh; y++) {
			if (map[x][y] == P) {
				plrX = rh*y;
				plrY = rw*x;
			}
		}
	}

	// main loop
	bool running = true;
	while (running) {

		// event loop
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			// keyboard controls
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: return 0; break; // close on escape
					 // up
					case SDLK_w:
					case SDLK_UP:
						if (plrY != 0 && collision(plrX, plrY, map) != 4) plrY -= rh;
						break;
					// down
					case SDLK_s:
					case SDLK_DOWN:
						if (plrY != WIN_HEIGHT-rh && collision(plrX, plrY, map) != 3) plrY += rh;
						break;
					// left
					case SDLK_a:
					case SDLK_LEFT:
						if (plrX != 0 && collision(plrX, plrY, map) != 2) plrX -= rw;
						break;
					// right
					case SDLK_d:
					case SDLK_RIGHT:
						if (plrX != WIN_WIDTH-rw && collision(plrX, plrY, map) != 1) plrX += rw; 
						break;
				}
			}
		}

		set_draw_color(0, 0, 0); // set background color
		render_clear();

		// scans through the map and draws colored squares█
		for (int x = 0; x < mw; x++) {
			for (int y = 0; y < mh; y++) {
				switch (map[x][y]) {
					case W:
						set_draw_color(223, 102, 200);  // wall color
						break;
					case R:
						set_draw_color(240, 36, 24);   // red tile color
						break;
					case G:
						set_draw_color(106, 153, 85);  // green tile color
						break;
					case B:
						set_draw_color(0, 117, 196);   // blue tile color
						break;
					case V:
						set_draw_color(242, 242, 242); // white tile color
						break;
					default:
						set_draw_color(0, 0, 0); 	   // background color
						break;
				}
				fill_rect(rh*y, rw*x, rw, rh);
			}
		}

		set_draw_color(236, 207, 55); // set player color
		fill_rect(plrX, plrY, plrW, plrH); // draw player

		render_present(); // display everything
	}
	destroyGFX(); // clean up sdl
}
