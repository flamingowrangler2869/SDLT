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
    {B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,0,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,W,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,W,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,W,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,W,0,0,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,0,0,0,0,0,0,0,0,0,0,0,B},
    {B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B}
};

int main() {
	
	initGFX("window", w, h);

	int plrX = cx;
	int plrY = cy;
	int plrW = rw;
	int plrH = rh;

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			
			// keyboard controls
			// switch(event.type) {
			// 	case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) return 0; // close on escape
					if (event.key.keysym.sym == SDLK_w && plrY != 0)	plrY -= rh; // top border
					if (event.key.keysym.sym == SDLK_s && plrY != h-rh)	plrY += rh; // bottom border
					if (event.key.keysym.sym == SDLK_a && plrX != 0)	plrX -= rw; // left border
					if (event.key.keysym.sym == SDLK_d && plrX != w-rw)	plrX += rw; // right border
					// break;
			// }
		}

		set_draw_color(0, 0, 0); // set background color
		render_clear();
	
		{
			set_draw_color(236, 207, 55); // set player color
			fill_rect(plrX, plrY, plrW, plrH); // draw player

			// boundary limits
			if (plrX < 0) plrX = 0;
			if (plrX > w-rw) plrX = w - rw;
			if (plrY < 0) plrY = 0;
			if (plrY > h-rh) plrY = h - rh;


			for (int x = 0; x < mw; x++) {
				for (int y = 0; y < mh; y++) {
					switch (map[x][y]) {
						case W:
							// SDL_Rect wall = {rect_size*y, rect_size*x, rw, rh}; // setup wall
							set_draw_color(86, 98, 246); // set wall color
							// SDL_RenderFillRect(renderer, &wall); // draw wall
						case B:
							set_draw_color(255, 0, 0);
					}
				}
			}
		}

		// display the things
		render_present();
	}


}