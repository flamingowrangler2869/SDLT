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
    {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,B,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
};

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
				plrX = rw*x;
				plrY = rh*y;
			}
		}
	}

	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			
			// keyboard controls
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) return 0; // close on escape
				if (event.key.keysym.sym == SDLK_w && plrY != 0)				plrY -= rh; // up
				if (event.key.keysym.sym == SDLK_s && plrY != WIN_HEIGHT-rh)	plrY += rh; // down
				if (event.key.keysym.sym == SDLK_a && plrX != 0)				plrX -= rw; // left
				if (event.key.keysym.sym == SDLK_d && plrX != WIN_WIDTH-rw)		plrX += rw; // right
			}
		}

		set_draw_color(0, 0, 0); // set background color
		render_clear();

		{
			for (int x = 0; x < mw; x++) {
				for (int y = 0; y < mh; y++) {
					switch (map[x][y]) {
						case W:
							set_draw_color(86, 98, 246); // wall color
							break;
						case B:
							set_draw_color(0xFF, 0, 0); // B tile color
							break;
						default:
							set_draw_color(0, 0, 0); // background color
							break;
					}
					fill_rect(rh*y, rw*x, rw, rh);
				}
			}

			set_draw_color(236, 207, 55); // set player color
			fill_rect(plrX, plrY, plrW, plrH); // draw player
		}

		render_present(); // display the things
	}

	destroyGFX(); // clean up sdl
}
