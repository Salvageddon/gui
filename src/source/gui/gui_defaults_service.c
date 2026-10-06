#include "../../include/gui_defaults_service.h"

void renderButton(SDL_Surface * sur, GUI_irect rect){
    fillRectNV(sur, rect.x, rect.y, rect.w, rect.h, 0x0000FF);
}