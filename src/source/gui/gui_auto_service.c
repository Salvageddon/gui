#include "../../include/gui_auto_service.h"
#include <stdlib.h>
#include <stdio.h>

Auto * typeAuto(Auto * o, int type, void * value, int stringLength){
    o->type = type;
    o->stringLength = stringLength;

    switch(type){
        case AUTO_INT:
            o->value = malloc(sizeof(int));
            *((int*)o->value) = *((int*)value);
        break;

        case AUTO_FLOAT:
            o->value = malloc(sizeof(float));
            *((float*)o->value) = *((float*)value);
        break;

        case AUTO_HEX:
            o->value = malloc(sizeof(Uint32));
            *((Uint32*)o->value) = *((Uint32*)value);
        break;

        case AUTO_STRING:
            char * text = malloc(sizeof(char) * (stringLength + 1));
            for(int i = 0; i < stringLength + 1; i++){
                text[i] = ((char*)value)[i];
            }
            o->value = text;
        break;

        case AUTO_BOX:
            o->value = malloc(sizeof(Box));
            *((Box*)o->value) = *((Box*)value);
        break;

        case AUTO_ALIGNMENT:
            o->value = malloc(sizeof(Alignment));
            *((Alignment*)o->value) = *((Alignment*)value);
        break;

        default:
            free(o);
            o = NULL;
        break;
    }

    return o;
}

Auto * createAuto(int type, void * value, int stringLength){
    Auto * o = malloc(sizeof(Auto));
    return typeAuto(o, type, value, stringLength);
}

Auto * changeAutoValue(Auto * au, int ntype, void * nvalue, int stringLength){
    free(au->value);
    return typeAuto(au, ntype, nvalue, stringLength);
}

int getInt(Auto * au){
    return *((int*)au->value);
}

float getFloat(Auto * au){
    return *((float*)au->value);
}

Uint32 getHex(Auto * au){
    return *((Uint32*)au->value);
}

char * getString(Auto * au){
    return au->value;
}

Box getBox(Auto * au){
    return *((Box*)au->value);
}

Alignment getAlignment(Auto * au){
    return *((Alignment*)au->value);
}

void destroyAuto(void * au){
    Auto * a = au;

    free(a->value);
    free(a);
}