#ifndef _DRAW_H_
#define _DRAW_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define PI 3.1415926535


#include "draw.h"

// store in mem the minimum and maximum value of x for a given y
// mem must be initialized to -1 at the begining of the drawing
// for a given y, mem[2*y] is the minimum value of x drawn
// for a given y, mem[2*y+1] is the maximum value of x drawn
// points on line y with x coordinate between mem[2*y] and mem[2*y+1] are
// inside the polygon drawn by draw_polygon()
void maj_mem(int * mem, SDL_Surface * s, int x, int y);

// draw pixel at coordinates (x,y) in color c
void draw_pixel_mem(SDL_Surface * s, SDL_Color c, int x, int y, int * mem);

void draw_HLine_mem(SDL_Surface * s, SDL_Color c, int x1, int x2, int y, int * mem);

void draw_VLine_mem(SDL_Surface * s, SDL_Color c, int x, int y1, int y2, int * mem);

// draw the line joining (x1,y1) and (y2,y2)
void draw_line_mem(SDL_Surface * s, SDL_Color c, int x1, int y1, int x2, int y2, int * mem);

// draw and fill a regular polygon in color c with n sides (n >= 2),
// rotating it of origin radians
void draw_polygon(SDL_Surface * s, int n, float origin, SDL_Color c);

// write the number of fish in the middle of the surface
void draw_fish(SDL_Surface * s, int n);

// draw the picture of the player pawn in the middle of the surface
void draw_player(SDL_Surface * s, int n);

void itoa(int n, char s[]);

#endif // _DRAW_H_
