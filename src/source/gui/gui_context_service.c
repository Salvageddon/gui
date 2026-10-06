#include "../../include/gui_context_service.h"
#include <stdlib.h>

GUI_context * createContext(int type){
    GUI_context * o = malloc(sizeof(GUI_context));

    o->type = type;
    o->controlRect = (GUI_irect){0, 0, 0, 0};
    o->renderer = &renderButton;

    return o;
}

void destroyContext(void * context){
    free(context);
}