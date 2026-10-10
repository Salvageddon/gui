/*
    Automatic type operation functions
    Violence
*/

#pragma once

#include "gui_color_service.h"

enum AutoTypes{
    AUTO_INT = 0xF000A1,
    AUTO_FLOAT,
    AUTO_HEX,
    AUTO_STRING,
};

typedef struct{
    void * value;
    int type, stringLength;
} Auto;

Auto * createAuto(int type, void * value, int stringLength);
Auto * changeAutoValue(Auto * au, int ntype, void * nvalue, int stringLength);
int getInt(Auto * au);
float getFloat(Auto * au);
Uint32 getHex(Auto * au);
char * getString(Auto * au);
void destroyAuto(void * au);