#include "../../include/gui_settings_service.h"
#include <stdlib.h>

GuiSettings * createGuiSettings(void){
    GuiSettings * o = malloc(sizeof(GuiSettings));

    o->ids = HLS_createList();
    o->fonts = HLS_createList();
    o->hover = NULL;
    o->oldHover = NULL;
    o->mouse = (Mouse){0, 0, 0};
    o->focusedFont = 0;
    o->isBaked = 0;
    o->hasTheme = 0;
    o->cursorData = createCursorData();

    return o;
}

void setTheme(GuiSettings * settings, SDL_Surface * sur, Uint32 pColor1, Uint32 pColor2, Uint32 fg, int boMod, int bgMod, int defTextSize, int defBorderSize, int mapWidth, int mapHeight){
    settings->theme = createTheme(sur, pColor1, pColor2, fg, boMod, bgMod, defTextSize, defBorderSize, mapWidth, mapHeight);
}

void destroyGuiSettings(GuiSettings * settings){
    if(settings->hasTheme) destroyTheme(&settings->theme);
    HLS_clear(&settings->ids, 0);
    HLS_clear(&settings->fonts, 1);
    HLS_clear(&settings->cursorData.cursors, 1);
    free(settings);
}

GUI_context * findContextById(GuiSettings * base, unsigned int id){
    return HLS_get(base->ids, id);
}