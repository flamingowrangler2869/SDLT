#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>

#include "utils.h"

#define PI 3.141592653589793238462643382F
#define RAD 0.01745329251994329576923690768F
#define DEG 57.29577951308232087679815482F
#define uchar unsigned char
#define W 1

SDL_Renderer* renderer = NULL;

const int w = 800;
const int h = 800;


const int rect_size = 50;
const int rw = rect_size;
const int rh = rect_size;

const int mw = w/rw;
const int mh = h/rh;

const int cx = w/2;
const int cy = h/2;

const int8_t map[16][16] = {
    {W,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,W,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,W,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,W,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,W,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void fillRect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
}

int main(int argc, char** argv) {

	// initialize sdl
	SDL_Init(SDL_INIT_VIDEO);

	// create window
	SDL_Window* win = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);

	bool running = true;
	SDL_Event event;
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int x1 = cx;
	int y1 = cy;
	int x2 = rw;
	int y2 = rh;

	// set player colors
	uchar r = 255;
	uchar g = 0;
	uchar b = 255;



	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
			
			// keyboard controls
			switch(event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) return 0; // close on escape
					if (event.key.keysym.sym == SDLK_w && y1 != 0)		y1 -= rh; // not on the top
					if (event.key.keysym.sym == SDLK_s && y1 != h-rh)	y1 += rh; // not on the bottom
					if (event.key.keysym.sym == SDLK_a && x1 != 0)		x1 -= rw; // not on the left
					if (event.key.keysym.sym == SDLK_d && x1 != w-rw)	x1 += rw; // not on the right
					break;
				
				default: break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set background color
		SDL_RenderClear(renderer);
	
		{
			
			SDL_Rect plr = {x1, y1, x2, y2}; // setup player

			// boundary limits
			if (x1 < 0) x1 = 0;
			if (x1 > w-rw) x1 = w - rw;
			if (y1 < 0) y1 = 0;
			if (y1 > h-rh) y1 = h - rh;


			for (int x = 0; x < mw; x++) {
				for (int y = 0; y < mh; y++) {
					if (map[x][y] == 1) {
						SDL_Rect wall = {rect_size*y, rect_size*x, rw, rh}; // setup wall
						SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // set wall color
						SDL_RenderFillRect(renderer, &wall); // draw wall
					}
				}
			}

			// draw player
			SDL_SetRenderDrawColor(renderer, r, g, b, 255); // set player color
			SDL_RenderFillRect(renderer, &plr);

		}

		// display the things
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

}