#ifndef DRAW_H
#define DRAW_H

//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------

#include <stdbool.h>
#include "SDL/SDL.h"

//-----------------------------------------------------------------------------
// Type
//-----------------------------------------------------------------------------

typedef enum {
    WHITE     = 255 * 256*256 + 255 * 256 + 255,
    YELLOW    = 255 * 256*256 + 255 * 256 +   0,
    BLUE      =   0 * 256*256 +   0 * 256 + 255,
    RED       = 255 * 256*256 +   0 * 256 +   0,
    GREEN     =   0 * 256*256 + 255 * 256 +   0,
    LIGHTGREY = 211 * 256*256 + 211 * 256 + 211,
    DARKGREY  = 169 * 256*256 + 169 * 256 + 169,
    FLOORGREY = 112 * 256*256 + 112 * 256 + 112,
    CEILGREY  =  57 * 256*256 +  57 * 256 +  57,
    BLACK     =   0 * 256*256 +   0 * 256 +   0,
    PURPLE    = 128 * 256*256 +  64 * 256 + 128,
} Colors;

//-----------------------------------------------------------------------------
// Global variable
//-----------------------------------------------------------------------------

extern SDL_Surface * screen;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

void fill(Uint32 color);

int init(char * title, int width, int height, int color, bool fullscreen);

void horizontal(int x1, int x2, int y, Uint32 color);

void line(int x1, int y1, int x2, int y2, Uint32 color);

void vertical(int x, int y1, int y2, Uint32 color);

void rect(int x, int y, int w, int h, Uint32 color, bool fill);

void render(void);

Uint32 get_pixel(SDL_Surface * surf, int x, int y);

void set_pixel(int x, int y, Uint32 color);

void display(SDL_Surface * surf, int x, int y);

#endif
