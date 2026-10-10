/*
    Attribute operation functions
    Heresy
*/

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"
#include "gui_enums.h"
#include <salvagames/hashlist.h>

#define ATTRCOUNT 3

typedef struct{
    char * name;
    int attrType, autoType;
} attributeData;

extern attributeData attributeDefinitions[ATTRCOUNT];

int findAutoType(int attrType);

void setAttribute(Hashlist * attributes, int attrType, void * value, int stringLength);
void unsetAttribute(Hashlist * attributes, int attrType);