#include "../../include/gui_mouse_service.h"
#include <stdio.h>

Mouse getMouseState(void){
    Mouse m;
    float x, y;
    m.buttons = SDL_GetMouseState(&x, &y);
    m.x = x; m.y = y;
    return m;
}

void destroyCursor(void * cursor){
    SDL_DestroyCursor(cursor);
}

CursorData createCursorData(void){
    CursorData o;

    o.cursors = HLS_createList();
    HLS_add(&o.cursors, GUI_CURSOR_ARROW, SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT), &destroyCursor);
    HLS_add(&o.cursors, GUI_CURSOR_HAND, SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER), &destroyCursor);
    HLS_add(&o.cursors, GUI_CURSOR_BEAM, SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT), &destroyCursor);

    o.currentCursorId = GUI_CURSOR_ARROW;

    return o;
}

void setCursor(CursorData * cursorData, int id){
    cursorData->currentCursorId = id;

    SDL_Cursor * newCursor = HLS_get(cursorData->cursors, id);
    SDL_SetCursor(newCursor);
}