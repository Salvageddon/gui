#include "../../include/gui_context_service.h"
#include <stdlib.h>
#include <stdio.h>

controlData controlDefinitions[CONTROLCOUNT] = {
    {"view", GUI_CONTROL_VIEW},
    {"button", GUI_CONTROL_BUTTON},
    {"linearView", GUI_CONTROL_LINEARVIEW}
};

void fakeEventListener(ListenerData hewwo){}

GUI_context * createContext(GUI_context * parent, int type){
    GUI_context * o = malloc(sizeof(GUI_context));

    o->type = type;
    o->renderData = (RenderData){0, 0, 0, 0, 1};
    o->controlRect = (GUI_irect){0, 0, 0, 0};
    o->paddingRect = (GUI_irect){0, 0, 0, 0};
    o->marginRect = (GUI_irect){0, 0, 0, 0};
    o->contentRect = (GUI_irect){0, 0, 0, 0};
    o->bakeResult = NULL;
    o->parent = parent;
    o->children = LST_createList();
    o->attributes = HLS_createList();
    o->eventHandlers = HLS_createList();

    switch(type){
        case GUI_CONTROL_BUTTON:
            o->renderer = &renderButton;
            o->possibleAttributes = (PossibleAttributes){buttonAttributes, BUTTON_ATTRCNT};
            o->listener = &buttonEventListener;
        break;

        case GUI_CONTROL_LINEARVIEW:
            o->renderer = &renderLinearView;
            o->possibleAttributes = (PossibleAttributes){linearViewAttributes, LINEARVIEW_ATTRCNT};
            o->listener = &fakeEventListener;
        break;

        case GUI_CONTROL_VIEW:
            o->renderer = &renderView;
            o->possibleAttributes = (PossibleAttributes){viewAttributes, VIEW_ATTRCNT};
            o->listener = &fakeEventListener;
        break;

        case GUI_CONTROL_BASE: 
            o->renderData.renderable = 0;
            o->listener = &fakeEventListener;
        break;

        default:
            free(o);
        return NULL;
    }

    if(parent){
        o->generation = parent->generation + 1;
        LST_add(&parent->children, o, &destroyContext);
        o->target = parent->target;
        o->settings = parent->settings;
    }
    else{
        o->generation = 0;
        o->target = NULL;
        o->settings = createGuiSettings();
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
    HLS_clear(&ctx->eventHandlers, 0);
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

void * getRenderArgs(GUI_context * context){
    switch(context->type){
        case GUI_CONTROL_BUTTON:
            ButtonRenderArgs * buttonRA = malloc(sizeof(ButtonRenderArgs));
            buttonRA->sur = context->bakeResult;
            buttonRA->rect = context->paddingRect;
            buttonRA->controlRect = context->controlRect;
            buttonRA->generation = context->generation;
            buttonRA->text = getText(context->attributes);
            buttonRA->textSize = getTextSize(context->attributes);
            buttonRA->font = HLS_get(context->settings->fonts, context->settings->focusedFont);
        return buttonRA;

        default:
            RenderArgs * ra = malloc(sizeof(RenderArgs));
            ra->sur = context->bakeResult;
            ra->rect = context->paddingRect;
            ra->generation = context->generation;
            return ra;
    }
}