/*
    Attribute operation functions
    Heresy
*/

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"
#include "gui_enums.h"
#include <salvagames/hashlist.h>

#define ATTRCOUNT 5
#define VIEW_ATTRCNT 4
#define BUTTON_ATTRCNT 4
#define LINEARVIEW_ATTRCNT 5

typedef struct{
    char * name;
    int attrType, autoType;
} attributeData;

typedef struct{
    char * attributes;
    int count;
} possibleAttributes;

extern attributeData attributeDefinitions[ATTRCOUNT];

extern char viewAttributes[VIEW_ATTRCNT];
extern char buttonAttributes[BUTTON_ATTRCNT];
extern char linearViewAttributes[LINEARVIEW_ATTRCNT];

int findAutoType(int attrType);
int findAttribute(char * attributeName);
void setAttribute(Hashlist * attributes, int attrType, void * value, int stringLength);
void unsetAttribute(Hashlist * attributes, int attrType);
int getOrientation(Hashlist attributes);
int getWidth(Hashlist attributes);
int getHeight(Hashlist attributes);
Box getMargin(Hashlist attributes);
Box getPadding(Hashlist attributes);