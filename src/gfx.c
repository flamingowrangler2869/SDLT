#include <SDL2/SDL.h>

SDL_Renderer* renderer = NULL;
SDL_Window* win = NULL;

int initGFX(char* title, int width, int height) {

	// initialize sdl
	SDL_Init(SDL_INIT_VIDEO);

	// create window
	win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	// create renderer
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void fill_rect(int x, int y, int w, int h) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
}

void set_draw_color(unsigned char r, unsigned char g, unsigned char b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void render_clear() {
	SDL_RenderClear(renderer);
}

void render_present() {
	SDL_RenderPresent(renderer);
}

void destroyGFX() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}