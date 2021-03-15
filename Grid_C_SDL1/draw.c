//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------

#include "draw.h"

//-----------------------------------------------------------------------------
// Global variable
//-----------------------------------------------------------------------------

SDL_Surface * screen;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Fill the screen with a color
void fill(Uint32 color) {
    SDL_FillRect(screen, NULL, color);
}

// Init SDL subsystems
int init(char * title, int width, int height, int color, bool fullscreen) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        perror("Error when initializing SDL");
        return EXIT_FAILURE;
    }
    if (fullscreen) {
        screen = SDL_SetVideoMode(width, height, color, SDL_SWSURFACE | SDL_FULLSCREEN);
    } else {
        screen = SDL_SetVideoMode(width, height, color, SDL_SWSURFACE | SDL_HWPALETTE);
    }
    if (screen == NULL) {
        printf("Error when setting video mode : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption(title, NULL);
    SDL_EnableUNICODE(true);
    return EXIT_SUCCESS;
}

// Draw horizontal, x1 must be < x2
void horizontal(int x1, int x2, int y, Uint32 color) {
    //Uint32 pix_per_line = screen->pitch >> 2;
    Uint32 * px = (Uint32*) screen->pixels + y * screen->w + x1;
    for (int x=x1; x < x2; x++) {
        *px = color;
        px += 1;
    }
}

// Use Bresenham algorithm
void line(int x1, int y1, int x2, int y2, Uint32 color) {
    if (x1 < 0) x1 = 0;
    if (x2 < 0) x2 = 0;
    if (y1 < 0) y1 = 0;
    if (y2 < 0) y2 = 0;
    if (x1 >= screen->w) x1 = screen->w - 1;
    if (x2 >= screen->w) x2 = screen->w - 1;
    if (y1 >= screen->h) y1 = screen->h - 1;
    if (y2 >= screen->h) y2 = screen->h - 1;
    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int x = x1;
    int y = y1;
    int modx1;
    int modx2;
    int mody1;
    int mody2;
    int num;
    int den;
    int numadd;
    int numpixels;
    if (x2 >= x1) {
        modx1 = 1;
        modx2 = 1;
    } else {
        modx1 = -1;
        modx2 = -1;
    }
    if (y2 >= y1) {
        mody1 = 1;
        mody2 = 1;
    } else {
        mody1 = -1;
        mody2 = -1;
    }
    if (deltax >= deltay) {
        modx1 = 0;
        mody2 = 0;
        den = deltax;
        num = deltax >> 1;
        numadd = deltay;
        numpixels = deltax;
    } else {
        modx2 = 0;
        mody1 = 0;
        den = deltay;
        num = deltay >> 1;
        numadd = deltax;
        numpixels = deltay;
    }
    for (int pix = 0; pix <= numpixels; pix++) {
        //Uint32 pix_per_line = screen->pitch >> 2;
        Uint32 * px = (Uint32*) screen->pixels + y * screen->w + x;
        *px = color;
        num += numadd;
        if (num >= den) {
            num -= den;
            x += modx1;
            y += mody1;
        }
        x += modx2;
        y += mody2;
    }
}

// Draw a vertical line of a color
void vertical(int x, int y1, int y2, Uint32 color) {
    // Swap
    if (y2 < y1) {
        y1 += y2;
        y2 = y1 - y2;
        y1 -= y2;
    }
    if (y2 < 0 || y1 >= screen->h || x < 0 || x >= screen->w) {
        return;
    }
    // Clip
    if (y1 < 0) {
        y1 = 0;
    }
    if (y2 >= screen->h) {
        y2 = screen->h - 1;
    }

    //Uint32 pix_per_line = screen->pitch >> 2;
    Uint32 * px = (Uint32*) screen->pixels + y1 * screen->w + x;
    for (int y=y1; y < y2; y++) {
        *px = color;
        px += screen->w;
    }

    return;
}

// Draw rect
void rect(int x, int y, int w, int h, Uint32 color, bool fill) {
    if (fill) {
        SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = w;
        r.h = h;
        SDL_FillRect(screen, &r, color);
        return;
    }
    //Uint32 pix_per_line = screen->pitch >> 2;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= screen->w) return;
    if (y >= screen->h) return;
    if (x + w >= screen->w) w = screen->w - x;
    if (y + h >= screen->h) h = screen->h - y;

    // 2 horizontal lines
    Uint32 * px = (Uint32*) screen->pixels + y * screen->w + x;
    for (int col=x; col < x + w; col++) {
        *px = color;
        px += 1;
    }
    px = (Uint32*) screen->pixels + (y + h) * screen->w + x;
    for (int col=x; col < x + w; col++) {
        *px = color;
        px += 1;
    }
    
    // 2 vertical lines
    px = (Uint32*) screen->pixels + y * screen->w + x;
    for (int row=y; row < y + h; row++) {
        *px = color;
        px += screen->w;
    }
    px = (Uint32*) screen->pixels + y * screen->w + x + w;
    for (int row=y; row < y + h; row++) {
        *px = color;
        px += screen->w;
    }
}

// Render the surface to the screen
void render(void) {
    SDL_UpdateRect(screen, 0, 0, 0, 0);
}

Uint32 get_pixel(SDL_Surface * surf, int x, int y) {
    Uint32 * px = (Uint32 *) surf->pixels + y * surf->w + x;
    return *px;
}

void set_pixel(int x, int y, Uint32 color) {
    if (x < 0 || y < 0 || x >= screen->w || y >= screen->h) {
        return;
    }
    Uint32 * px = (Uint32*) screen->pixels + y * screen->w + x;
    *px = color;
}

void display(SDL_Surface * surf, int x, int y) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_BlitSurface(surf, NULL, screen,  &r);
}
