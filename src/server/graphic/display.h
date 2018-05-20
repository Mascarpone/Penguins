#ifndef _DISPLAY_H_
#define _DISPLAY_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "draw.h"

#define PI 3.1415926535

extern int WIDTH;
extern int HEIGHT;
extern int g_n;
extern float g_o;
extern int POLYGON_RADIUS;

#define ERROR 1
#define OK 0

#define TRANS ((SDL_Color) {255, 255, 255, 0  })
#define WHITE ((SDL_Color) {255, 255, 255, 255})
#define BLACK ((SDL_Color) {0  , 0,   0,   255})
#define BLUE  ((SDL_Color) {10 , 104, 191, 255})


struct Display {
    SDL_Window * w;
    SDL_Renderer * r;
};


int display_init(struct Display * d);
void display_free(struct Display * d);
void wait_event(struct Display * d);

void draw_tile(SDL_Surface * s, struct tile * t);

#endif // _DISPLAY_H_
