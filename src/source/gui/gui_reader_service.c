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

int readSize(char * value){
    if(!strcmp(value, "size-min")){
        return GUI_SIZE_MIN;
    }
    else if(!strcmp(value, "size-max")){
        return GUI_SIZE_MAX;
    }
    else{
        return stringToInt(value);
    }
}

Alignment readAligment(char * value){
    Alignment o;

    List tokens = tokenize(value);

    if(tokens.length == 2){
        int alignment[2];

        for(int i = 0; i < 2; i++){
            char * token = LST_get(tokens, i);

            if(!strcmp("center", token)){
                alignment[i] = GUI_ALIGNMENT_CENTER;
            }
            else if(!strcmp("end", token)){
                alignment[i] = GUI_ALIGNMENT_END;
            }
            else if(!strcmp("stretch-between", token)){
                alignment[i] = GUI_ALIGNMENT_STRETCH_BETWEEN;
            }
            else if(!strcmp("stretch-around", token)){
                alignment[i] = GUI_ALIGNMENT_STRETCH_AROUND;
            }
            else{
                alignment[i] = GUI_ALIGNMENT_START;
            }
        }

        o.horizontal = alignment[0];
        o.vertical = alignment[1];
    }
    else{
        o = (Alignment){GUI_ALIGNMENT_START, GUI_ALIGNMENT_START};
    }

    LST_clear(&tokens, 1);

    return o;
}

int readAttributes(GUI_context * context, xmlElement * el){
    int hasErrored = 0;

    for(int i = 0; i < el->attributes.length; i++){
        xmlAttribute * attr = LST_get(el->attributes, i);

        int attrType = findAttribute(attr->name);

        switch(attrType){
            case GUI_ATTRIBUTE_ORIENTATION:
                int orientation = readOrientation(attr->value);
                setAttribute(&context->attributes, attrType, &orientation, 0);
            break;

            case GUI_ATTRIBUTE_WIDTH:
            case GUI_ATTRIBUTE_HEIGHT:
            case GUI_ATTRIBUTE_TEXT_SIZE:
                int size = readSize(attr->value);
                setAttribute(&context->attributes, attrType, &size, 0);
            break;

            case GUI_ATTRIBUTE_MARGIN:
            case GUI_ATTRIBUTE_PADDING:
                Box box = readBox(attr->value);
                setAttribute(&context->attributes, attrType, &box, 0);
            break;

            case GUI_ATTRIBUTE_ITEM_ALIGNMENT:
                Alignment itemAlignment = readAligment(attr->value);
                setAttribute(&context->attributes, attrType, &itemAlignment, 0);
            break;

            case GUI_ATTRIBUTE_ID:
                Uint32 id = stringToHex(attr->value);
                if(id == 0){
                    setErrorMessage("Control ID cannot equal 0.\n");
                    hasErrored = 1;
                }
                else if(HLS_get(context->settings->ids, id)){
                    setErrorMessage("Control with this ID already exists in the GUI.\n");
                    hasErrored = 1;
                }
                else{
                    setAttribute(&context->attributes, attrType, &id, 0);
                    HLS_add(&context->settings->ids, id, context, &destroyContext);
                }
            break;

            case GUI_ATTRIBUTE_TEXT:
                setAttribute(&context->attributes, attrType, attr->value, attr->valueLength);
            break;
        }

        if(hasErrored) break;
    }

    return hasErrored;
}

char hasAllMandatoryAttributes(GUI_context * context){
    char ret = 1;

    for(int i = 0; i < context->possibleAttributes.count; i++){
        AllowedAttribute allowed = context->possibleAttributes.attributes[i];

        if(allowed.mandatory){
            AttributeData attribute = attributeDefinitions[allowed.id];
            
            if(!HLS_get(context->attributes, attribute.attrType)){
                ret = 0;
                break;
            }
        }
    }

    return ret;
}

int readChildren(GUI_context * context, xmlElement * el){
    int hasErrored = 0;

    for(int i = 0; i < el->elements.length; i++){
        xmlElement * xmlChild = LST_get(el->elements, i);

        if(xmlChild->type == XML_ELEMENT){
            GUI_context * child = createContext(context, getControlType(xmlChild->name));
            if(!child) break;

            hasErrored = readAttributes(child, xmlChild);
            if(hasErrored){
                break;
            }

            if(!hasAllMandatoryAttributes(child)){
                setErrorMessage("Element doesn't have all necessary attributes.\n");
                hasErrored = 1;
                break;
            }
            
            hasErrored = readChildren(child, xmlChild);
        }
    }

    return hasErrored;
}

GUI_context * readGui(const char * source, SDL_Surface * sur){
    xmlElement * root = XML_read(source);
    
    if(!root){
        setErrorMessage("XML GUI reading failed due to syntax errors.\n");
        return NULL;
    }

    GUI_context * base = createContext(NULL, GUI_CONTROL_BASE);
    base->renderer = NULL;
    base->target = sur;

    int baseOrientation = GUI_ORIENTATION_HORIZONTAL, 
        baseSize = GUI_SIZE_MAX;

    setAttribute(&base->attributes, GUI_ATTRIBUTE_ORIENTATION, &baseOrientation, 0);
    setAttribute(&base->attributes, GUI_ATTRIBUTE_WIDTH, &baseSize, 0);
    setAttribute(&base->attributes, GUI_ATTRIBUTE_HEIGHT, &baseSize, 0);

    int hasErrored = readChildren(base, root);

    if(hasErrored){
        destroyContext(base);
        base = NULL;
    }

    XML_free(root);

    return base;
}