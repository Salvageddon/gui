/*
    Attribute operation functions
    Heresy
*/

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"
#include "gui_font_service.h"

#include "gui_enums.h"
#include <salvagames/hashlist.h>

#define ATTRCOUNT 9
#define VIEW_ATTRCNT 5
#define BUTTON_ATTRCNT 7
#define LINEARVIEW_ATTRCNT 7

typedef struct{
    char * name;
    int attrType, autoType;
} AttributeData;

typedef struct{
    char id, mandatory;
} AllowedAttribute;

typedef struct{
    AllowedAttribute * attributes;
    int count;
} PossibleAttributes;

extern AttributeData attributeDefinitions[ATTRCOUNT];

extern AllowedAttribute viewAttributes[VIEW_ATTRCNT];
extern AllowedAttribute buttonAttributes[BUTTON_ATTRCNT];
extern AllowedAttribute linearViewAttributes[LINEARVIEW_ATTRCNT];

int findAutoType(int attrType);
int findAttribute(char * attributeName);
void setAttribute(Hashlist * attributes, int attrType, void * value, int stringLength);
void unsetAttribute(Hashlist * attributes, int attrType);
int getOrientation(Hashlist attributes);
int getWidth(Hashlist attributes);
int getHeight(Hashlist attributes);
Box getMargin(Hashlist attributes);
Box getPadding(Hashlist attributes);
Alignment getItemAlignment(Hashlist attributes);
Uint32 getId(Hashlist attributes);
char * getText(Hashlist attributes);
int getTextSize(Hashlist attributes);