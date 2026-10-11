#include "../../include/gui_context_service.h"
#include <stdlib.h>
#include <stdio.h>

controlData controlDefinitions[CONTROLCOUNT] = {
    {"button", GUI_CONTROL_BUTTON},
    {"linearView", GUI_CONTROL_LINEARVIEW}
};

GUI_context * createContext(GUI_context * parent, int type){
    GUI_context * o = malloc(sizeof(GUI_context));

    o->type = type;
    o->controlRect = (GUI_irect){0, 0, 0, 0};
    o->bakeResult = NULL;
    o->parent = parent;
    o->children = LST_createList();
    o->attributes = HLS_createList();

    switch(type){
        case GUI_CONTROL_BUTTON:
            o->renderer = &renderButton;
            o->possibleAttributes = (possibleAttributes){buttonAttributes, BUTTON_ATTRCNT};
        break;

        case GUI_CONTROL_LINEARVIEW:
            o->renderer = &renderLinearView;
            o->possibleAttributes = (possibleAttributes){linearViewAttributes, LINEARVIEW_ATTRCNT};
        break;

        default:
            free(o);
        return NULL;
    }

    if(parent){
        o->generation = parent->generation + 1;
        LST_add(&parent->children, o, &destroyContext);
    }
    else{
        o->generation = 0;
    }

    return o;
}

void destroyContext(void * context){
    GUI_context * ctx = context;

    for(int i = 0; i < ctx->children.length; i++){
        destroyContext(LST_get(ctx->children, i));
    }

    LST_clear(&ctx->children, 0);
    HLS_clear(&ctx->attributes, 1);
    SDL_DestroySurface(ctx->bakeResult);

    free(context);
}

int getControlType(char * controlName){
    int ret = -1;

    for(int i = 0; i < ATTRCOUNT; i++){
        if(!strcmp(controlDefinitions[i].name, controlName)){
            ret = controlDefinitions[i].type;
            break;
        }
    }

    return ret;
}