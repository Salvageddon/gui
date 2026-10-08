#include "../../include/gui_reader_service.h"
#include <salvagames/xmlReader.h>
#include <stdio.h>

void readChildren(GUI_context * context, xmlElement * el){
    for(int i = 0; i < el->elements.length; i++){
        xmlElement * xmlChild = LST_get(el->elements, i);

        if(xmlChild->type == XML_ELEMENT){
            GUI_context * child = createContext(context, GUI_CONTROL_BUTTON);
            readChildren(child, xmlChild);
        }
    }
}

GUI_context * readGui(const char * source){
    xmlElement * root = XML_read(source);
    
    if(!root){
        return NULL;
    }

    GUI_context * base = createContext(NULL, GUI_CONTROL_BUTTON);
    base->renderer = NULL;

    readChildren(base, root);

    XML_free(root);

    return base;
}