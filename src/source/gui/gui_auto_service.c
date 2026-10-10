#include "../../include/gui_auto_service.h"
#include <stdlib.h>

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
            o->value = malloc(sizeof(stringLength));
            o->value = value;
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
    return typeAuto;
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

void destroyAuto(void * au){
    Auto * a = au;

    free(a->value);
    free(a);
}