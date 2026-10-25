#include "../../include/gui_settings_service.h"
#include <stdlib.h>

GuiSettings * createGuiSettings(void){
    GuiSettings * o = malloc(sizeof(GuiSettings));

    o->ids = HLS_createList();
    o->hover = NULL;
    o->oldHover = NULL;
    o->mouse = (Mouse){0, 0, 0};

    return o;
}

void destroyGuiSettings(GuiSettings * settings){
    HLS_clear(&settings->ids, 0);
    free(settings);
}

GUI_context * findContextById(GuiSettings * base, unsigned int id){
    return HLS_get(base->ids, id);
}