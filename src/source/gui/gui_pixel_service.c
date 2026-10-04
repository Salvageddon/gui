#include "../../include/gui_pixel_service.h"

void setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel){
    Uint32 * pixels = sur->pixels;
    pixels[y * sur->w + x] = pixel;
}

Uint32 getPixel(SDL_Surface * sur, int x, int y){
    Uint32 * pixels = sur->pixels;
    return pixels[y * sur->w + x];
}