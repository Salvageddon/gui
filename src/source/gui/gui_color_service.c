#include "../../include/gui_color_service.h"

GUI_rgb getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    GUI_rgb ret;
    SDL_GetRGB(color, formatDetails, NULL, &ret.r, &ret.g, &ret.b);
    return ret;
}

Uint32 mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails){
    return SDL_MapRGB(formatDetails, NULL, color.r, color.g, color.b);
}

GUI_rgba getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    GUI_rgba ret;
    SDL_GetRGBA(color, formatDetails, NULL, &ret.r, &ret.g, &ret.b, &ret.a);
    return ret;
}

Uint32 mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails){
    return SDL_MapRGBA(formatDetails, NULL, color.r, color.g, color.b, color.a);
}