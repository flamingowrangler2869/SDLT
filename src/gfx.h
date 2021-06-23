#ifndef GFX_H
#define GFX_H

int initGFX(char* title, int width, int height);
void fill_rect(int x, int y, int w, int h);
void set_draw_color(unsigned char r, unsigned char g, unsigned char b);
void render_clear();
void render_present();
void destroyGFX();

#endif /* GFX_H */