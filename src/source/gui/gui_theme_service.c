#include "../../include/gui_theme_service.h"
#include <stdio.h>

Uint32 changeColor(Uint32 color, int mod, const SDL_PixelFormatDetails * details){
    GUI_rgb col = getRGB(color, details), newCol;

    newCol.r = ADDUINT8(col.r, mod);
    newCol.g = ADDUINT8(col.g, mod);
    newCol.b = ADDUINT8(col.b, mod);

    return mapRGB(newCol, details);
}

Uint32 changeAndAverageColor(Uint32 color, int mod, const SDL_PixelFormatDetails * details){
    GUI_rgb col = getRGB(color, details), newCol;

    int avg = (col.r, col.g, col.b) / 3;

    newCol.r = ADDUINT8(avg, mod);
    newCol.g = ADDUINT8(avg, mod);
    newCol.b = ADDUINT8(avg, mod);

    return mapRGB(newCol, details);
}

EventColor makeEventColor(Uint32 color, const SDL_PixelFormatDetails * details){
    return(EventColor){
        color,
        changeColor(color, HOVERMOD, details),
        changeColor(color, CLICKMOD, details),
        changeAndAverageColor(color, DISABLEDMOD, details),
    };
}

SDL_Surface * makeGradient(SDL_Surface * sur, Uint32 col1, Uint32 col2, int mapWidth, int mapHeight){
    SDL_Surface * o = SDL_CreateSurface(mapWidth, mapHeight, sur->format);
    fillRectGNV(o, 0, 0, mapWidth, mapHeight, col1, col2);
    return o;
}

EventSurface makeEventSurface(SDL_Surface * sur, EventColor col1, EventColor col2, int mapWidth, int mapHeight){
    return (EventSurface){
        makeGradient(sur, col1.normal, col2.normal, mapWidth, mapHeight),
        makeGradient(sur, col1.hover, col2.hover, mapWidth, mapHeight),
        makeGradient(sur, col1.click, col2.click, mapWidth, mapHeight),
        makeGradient(sur, col1.disabled, col2.disabled, mapWidth, mapHeight)
    };
}

Theme createTheme(SDL_Surface * sur, Uint32 pColor1, Uint32 pColor2, Uint32 fg, int boMod, int bgMod, int defTextSize, int defBorderSize, int mapWidth, int mapHeight){
    const SDL_PixelFormatDetails * details = SDL_GetPixelFormatDetails(sur->format);
    Theme o;

    o.primaryColor1 = makeEventColor(pColor1, details);
    o.primaryColor2 = makeEventColor(pColor2, details);

    o.borderColor1 = makeEventColor(changeColor(pColor1, boMod, details), details);
    o.borderColor2 = makeEventColor(changeColor(pColor2, boMod, details), details);

    o.backgroundColor1 = makeEventColor(changeColor(pColor1, bgMod, details), details);
    o.backgroundColor2 = makeEventColor(changeColor(pColor2, bgMod, details), details);

    o.foregroundColor = makeEventColor(fg, details);

    o.primaryGradient = makeEventSurface(sur, o.primaryColor1, o.primaryColor2, mapWidth, mapHeight);
    o.borderGradient = makeEventSurface(sur, o.borderColor1, o.borderColor2, mapWidth, mapHeight);
    o.backgroundGradient = makeEventSurface(sur, o.backgroundColor1, o.backgroundColor2, mapWidth, mapHeight);

    o.defaultTextSize = defTextSize;
    o.defaultBorderThickness = defBorderSize;
    o.mapWidth = mapWidth;
    o.mapHeight = mapHeight;

    o.invMapWidth = (float)mapWidth / (float)sur->w;
    o.invMapHeight = (float)mapHeight / (float)sur->h;

    return o;
}

void destroyEventSurface(EventSurface * eventSurface){
    SDL_DestroySurface(eventSurface->normal);
    SDL_DestroySurface(eventSurface->hover);
    SDL_DestroySurface(eventSurface->click);
    SDL_DestroySurface(eventSurface->disabled);
}

void destroyTheme(Theme * theme){
    destroyEventSurface(&theme->primaryGradient);
    destroyEventSurface(&theme->borderGradient);
    destroyEventSurface(&theme->backgroundGradient);
}