#include "../../include/gui_defaults_service.h"

void renderButton(SDL_Surface * sur, GUI_irect rect, int generation){
    GUI_rgb color;
    color.r = 0;
    color.g = 0;
    color.b = 255 - generation * 20;

    fillRectNV(sur, 0, 0, rect.w, rect.h, mapRGB(color, SDL_GetPixelFormatDetails(sur->format)));
}