#include "../../include/gui_reader_service.h"
#include <salvagames/xmlReader.h>
#include <stdio.h>

GUI_context * readGui(const char * source){
    xmlElement * root = XML_read(source);
    
    if(!root){
        return NULL;
    }

    GUI_context * base = createContext(GUI_CONTROL_BUTTON);
    base->renderer = NULL;

    for(int i = 1; i < root->elements.length; i++){
        GUI_context * child = createContext(GUI_CONTROL_BUTTON);
        LST_add(&base->children, child, &destroyContext);
        child->parent = base;
    }

    XML_free(root);

    return base;
}