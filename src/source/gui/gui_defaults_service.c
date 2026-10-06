#include "../../include/gui_defaults_service.h"

void renderButton(SDL_Surface * sur, GUI_irect rect){
    fillRectNV(sur, 0, 0, rect.w, rect.h, 0x0000FF);
}