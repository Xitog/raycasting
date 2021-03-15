//-----------------------------------------------------------------------------
// Include
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include "SDL/SDL.h"
#include "draw.h"
#include "event.h"
#include "game.h"

//-----------------------------------------------------------------------------
// Global constants
//-----------------------------------------------------------------------------

const Uint32 SCREEN_WIDTH  = 640;
const Uint32 SCREEN_HEIGHT = 480;

#ifdef __linux__
#define OS                    "Linux"
#define TEX_PLACEHOLDER       "../../../assets/sets/fps/western/walls/0-placeholder.bmp"
#define TEX_GREY_STONE        "../../../assets/sets/fps/western/walls/1-grey_stone_wall.bmp"
#define TEX_GREY_STONE_STONE  "../../../assets/sets/fps/western/walls/2-grey_stone_wall_stone.bmp"
#define TEX_LIGHT_STONE       "../../../assets/sets/fps/western/walls/3-light_stone_wall.bmp"
#define TEX_LIGHT_STONE_STONE "../../../assets/sets/fps/western/walls/4-light_stone_wall_stone.bmp"
#define TEX_LIGHT_STONE_GRASS "../../../assets/sets/fps/western/walls/5-light_stone_wall_grass.bmp"
#define TEX_LIGHT_WOOD        "../../../assets/sets/fps/western/walls/6-light_wood_wall.bmp"
#define TEX_LIGHT_WOOD_WINDOW "../../../assets/sets/fps/western/walls/7-light_wood_wall_window.bmp"
#define TEX_DARK_WOOD         "../../../assets/sets/fps/western/walls/8-dark_wood_wall.bmp"
#define TEX_RED_BRICK         "../../../assets/sets/fps/western/walls/9-red_brick_wall.bmp"
#define TEX_RED_BRICK_LIGHT   "../../../assets/sets/fps/western/walls/10-red_brick_wall_light.bmp"
#define TEX_RED_BRICK_PILLAR  "../../../assets/sets/fps/western/walls/11-red_brick_wall_pillar.bmp"
#define TEX_RED_BRICK_BARS    "../../../assets/sets/fps/western/walls/12-red_brick_wall_bars.bmp"
#endif
#ifdef _WIN32
#define OS                    "Windows"
#define TEX_PLACEHOLDER       "..\\..\\..\\assets\\sets\\fps\\western\\walls\\0-placeholder.bmp"
#define TEX_GREY_STONE        "..\\..\\..\\assets\\sets\\fps\\western\\walls\\1-grey_stone_wall.bmp"
#define TEX_GREY_STONE_STONE  "..\\..\\..\\assets\\sets\\fps\\western\\walls\\2-grey_stone_wall_stone.bmp"
#define TEX_LIGHT_STONE       "..\\..\\..\\assets\\sets\\fps\\western\\walls\\3-light_stone_wall.bmp"
#define TEX_LIGHT_STONE_STONE "..\\..\\..\\assets\\sets\\fps\\western\\walls\\4-light_stone_wall_stone.bmp"
#define TEX_LIGHT_STONE_GRASS "...\\..\\..\\assets\\sets\\fps\\western\\walls\\5-light_stone_wall_grass.bmp"
#define TEX_LIGHT_WOOD        "..\\..\\..\\assets\\sets\\fps\\western\\walls\\6-light_wood_wall.bmp"
#define TEX_LIGHT_WOOD_WINDOW "..\\..\\..\\assets\\sets\\fps\\western\\walls\\7-light_wood_wall_window.bmp"
#define TEX_DARK_WOOD         "..\\..\\..\\assets\\sets\\fps\\western\\walls\\8-dark_wood_wall.bmp"
#define TEX_RED_BRICK         "..\\..\\..\\assets\\sets\\fps\\western\\walls\\9-red_brick_wall.bmp"
#define TEX_RED_BRICK_LIGHT   "..\\..\\..\\assets\\sets\\fps\\western\\walls\\10-red_brick_wall_light.bmp"
#define TEX_RED_BRICK_PILLAR  "..\\..\\..\\assets\\sets\\fps\\western\\walls\\11-red_brick_wall_pillar.bmp"
#define TEX_RED_BRICK_BARS    "..\\..\\..\\assets\\sets\\fps\\western\\walls\\12-red_brick_wall_bars.bmp"
#endif

//-----------------------------------------------------------------------------
// Function
//-----------------------------------------------------------------------------

void infosurf(SDL_Surface * surf) {
    printf("%lu\n", sizeof(*surf)); // 60
    printf("%lu\n", sizeof(*(surf->format))); // 40
    printf("PixelFormat.BytesPexPixel = %d\n", surf->format->BytesPerPixel); // 4
    printf("Surface.Pitch = %d\n", surf->pitch); // 2560
}

void load_textures(void) {
    // Textures
    TEXTURES[0] = SDL_ConvertSurface(SDL_LoadBMP(TEX_PLACEHOLDER), screen->format, SDL_SWSURFACE);
    TEXTURES[1] = SDL_ConvertSurface(SDL_LoadBMP(TEX_GREY_STONE), screen->format, SDL_SWSURFACE);
    TEXTURES[2] = SDL_ConvertSurface(SDL_LoadBMP(TEX_GREY_STONE_STONE), screen->format, SDL_SWSURFACE);
    TEXTURES[3] = SDL_ConvertSurface(SDL_LoadBMP(TEX_LIGHT_STONE), screen->format, SDL_SWSURFACE);
    TEXTURES[4] = SDL_ConvertSurface(SDL_LoadBMP(TEX_LIGHT_STONE_STONE), screen->format, SDL_SWSURFACE);
    TEXTURES[5] = SDL_ConvertSurface(SDL_LoadBMP(TEX_LIGHT_STONE_GRASS), screen->format, SDL_SWSURFACE);
    TEXTURES[6] = SDL_ConvertSurface(SDL_LoadBMP(TEX_LIGHT_WOOD), screen->format, SDL_SWSURFACE);
    TEXTURES[7] = SDL_ConvertSurface(SDL_LoadBMP(TEX_LIGHT_WOOD_WINDOW), screen->format, SDL_SWSURFACE);
    TEXTURES[8] = SDL_ConvertSurface(SDL_LoadBMP(TEX_DARK_WOOD), screen->format, SDL_SWSURFACE);
    TEXTURES[9] = SDL_ConvertSurface(SDL_LoadBMP(TEX_RED_BRICK), screen->format, SDL_SWSURFACE);
    TEXTURES[10] = SDL_ConvertSurface(SDL_LoadBMP(TEX_RED_BRICK_LIGHT), screen->format, SDL_SWSURFACE);
    TEXTURES[11] = SDL_ConvertSurface(SDL_LoadBMP(TEX_RED_BRICK_PILLAR), screen->format, SDL_SWSURFACE);
    TEXTURES[12] = SDL_ConvertSurface(SDL_LoadBMP(TEX_RED_BRICK_BARS), screen->format, SDL_SWSURFACE);
    //infosurf(TEXTURES[0]);
}

int main(int argc, char * argv[]) {
    
    printf("Start of program\n");
    printf("Using SDL 1.2.15 on %s\n", OS);
    
    /*
    FILE * fp = fopen("D:\\Tools\\Perso\\Projets\\map_editor\\New map.bin", "rb");
    short s1;
    fread(&s1, 2, 1, fp);
    int l1;
    fread(&l1, 4, 1, fp);
    float f1;
    fread(&f1, 4, 1, fp);
    printf("%hd %d %f\n", s1, l1, f1);
    */

    int err = init("Woolfy 2.5 FLAT", SCREEN_WIDTH, SCREEN_HEIGHT, 32, false);
    if (err == EXIT_FAILURE) {
        return err;
    } else {
        printf("Textures loaded.");
    }
    
    load_textures();

    // Time
    double tick_current = 0.0;
    double tick_previous = 0.0;
    double frame_time = 0.0;
    
    event_init();
    game_init();
    
    while (!action_state[A_ESCAPE]) {
        // Draw
        game_draw();
        render();
 
        // Input
        event_input();

        // Time
        tick_previous = tick_current;
        tick_current = SDL_GetTicks();
        frame_time = (tick_current - tick_previous);

        // Update
        game_update(frame_time);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
