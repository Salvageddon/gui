#include "../../include/gui_context_service.h"
#include <stdlib.h>
#include <stdio.h>

GUI_context * createContext(int type){
    GUI_context * o = malloc(sizeof(GUI_context));

    o->type = type;
    o->controlRect = (GUI_irect){0, 0, 0, 0};
    o->bakeResult = NULL;
    o->parent = NULL;
    o->children = LST_createList();
    o->renderer = &renderButton;

    return o;
}

void destroyContext(void * context){
    GUI_context * ctx = context;

    for(int i = 0; i < ctx->children.length; i++){
        destroyContext(LST_get(ctx->children, i));
    }

    LST_clear(&ctx->children, 0);
    SDL_DestroySurface(ctx->bakeResult);

    free(context);
}