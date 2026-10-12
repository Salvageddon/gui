#include "../../include/gui_reader_service.h"
#include <salvagames/xmlReader.h>
#include <stdio.h>
#include <string.h>

int readOrientation(char * value){
    if(!strcmp(value, "horizontal")){
        return GUI_ORIENTATION_HORIZONTAL;
    }
    else{
        return GUI_ORIENTATION_VERTICAL;
    }
}

Box readBox(char * value){
    Box o;

    List tokens = tokenize(value);

    switch(tokens.length){
        case 1:
            char * token = LST_get(tokens, 0);
            int size = stringToInt(token);
            o = (Box){size, size, size, size};
        break;

        case 2:
            char * token1 = LST_get(tokens, 0);
            char * token2 = LST_get(tokens, 1);

            int hor = stringToInt(token1);
            int ver = stringToInt(token2);

            o = (Box){hor, ver, hor, ver};
        break;

        case 4:
            char * tokenl = LST_get(tokens, 0);
            char * tokent = LST_get(tokens, 1);
            char * tokenr = LST_get(tokens, 2);
            char * tokenb = LST_get(tokens, 3);

            int sizel = stringToInt(tokenl);
            int sizet = stringToInt(tokent);
            int sizer = stringToInt(tokenr);
            int sizeb = stringToInt(tokenb);

            o = (Box){sizel, sizet, sizer, sizeb};
        break;

        default:
            o = (Box){0, 0, 0, 0};
    }

    LST_clear(&tokens, 1);

    return o;
}

void readAttributes(GUI_context * context, xmlElement * el){
    for(int i = 0; i < el->attributes.length; i++){
        xmlAttribute * attr = LST_get(el->attributes, i);

        int attrType = findAttribute(attr->name);

        switch(attrType){
            case GUI_ATTRIBUTE_ORIENTATION:
                int orientation = readOrientation(attr->value);
                setAttribute(&context->attributes, attrType, &orientation, 0);
            break;

            case GUI_ATTRIBUTE_MARGIN:
            case GUI_ATTRIBUTE_PADDING:
                Box padding = readBox(attr->value);
                setAttribute(&context->attributes, attrType, &padding, 0);
            break;
        }
    }
}

void readChildren(GUI_context * context, xmlElement * el){
    for(int i = 0; i < el->elements.length; i++){
        xmlElement * xmlChild = LST_get(el->elements, i);

        if(xmlChild->type == XML_ELEMENT){
            GUI_context * child = createContext(context, getControlType(xmlChild->name));
            if(!child) break;

            readAttributes(child, xmlChild);
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

    int baseOrientation = GUI_ORIENTATION_HORIZONTAL;
    setAttribute(&base->attributes, GUI_ATTRIBUTE_ORIENTATION, &baseOrientation, 0);

    readChildren(base, root);

    XML_free(root);

    return base;
}