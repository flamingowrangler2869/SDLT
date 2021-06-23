#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "utils.h"
#include "gfx.h"

#define uchar unsigned char
#define W 1
#define B 2
#define P -1

const int w = 800;
const int h = 800;

const int rect_size = 50;
const int rw = rect_size;
const int rh = rect_size;

const int mw = w/rw;
const int mh = h/rh;

const int cx = w/2;
const int cy = h/2;

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
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,W},
    {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
};

int main() {
	int plrW = rw;
	int plrH = rh;
	int plrX = cx;
	int plrY = cy;
	initGFX("window", w, h);
	for (int x = 0; x < mw; x++) {
		for (int y = 0; y < mh; y++) {
			if (map[x][y] == P) {
				plrX = rect_size*x;
				plrY = rect_size*y;
			}
		}
	}

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			
			// keyboard controls
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) return 0; // close on escape
				if (event.key.keysym.sym == SDLK_w && plrY != 0)	plrY -= rh; // up
				if (event.key.keysym.sym == SDLK_s && plrY != h-rh)	plrY += rh; // down
				if (event.key.keysym.sym == SDLK_a && plrX != 0)	plrX -= rw; // left
				if (event.key.keysym.sym == SDLK_d && plrX != w-rw)	plrX += rw; // right
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
							set_draw_color(0, 0, 0);
							break;
					}
					fill_rect(rect_size*y, rect_size*x, rw, rh);
				}
			}

			set_draw_color(236, 207, 55); // set player color
			fill_rect(plrX, plrY, plrW, plrH); // draw player
		}

		render_present(); // display the things
	}

	destroyGFX(); // clean up sdl
}