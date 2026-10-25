#include "../../include/gui_attribute_service.h"

AttributeData attributeDefinitions[ATTRCOUNT] = {
    {"orientation", GUI_ATTRIBUTE_ORIENTATION, AUTO_INT},
    {"width", GUI_ATTRIBUTE_WIDTH, AUTO_INT},
    {"height", GUI_ATTRIBUTE_HEIGHT, AUTO_INT},
    {"margin", GUI_ATTRIBUTE_MARGIN, AUTO_BOX},
    {"padding", GUI_ATTRIBUTE_PADDING, AUTO_BOX},
    {"item-alignment", GUI_ATTRIBUTE_ITEM_ALIGNMENT, AUTO_ALIGNMENT},
    {"id", GUI_ATTRIBUTE_ID, AUTO_HEX}
};

AllowedAttribute viewAttributes[VIEW_ATTRCNT] = {
    {1, 1}, 
    {2, 1}, 
    {3, 0}, 
    {4, 0},
    {6, 0}
};

AllowedAttribute buttonAttributes[BUTTON_ATTRCNT] = {
    {1, 1}, 
    {2, 1}, 
    {3, 0}, 
    {4, 0},
    {6, 0}
};

AllowedAttribute linearViewAttributes[LINEARVIEW_ATTRCNT] = {
    {0, 1}, 
    {1, 1}, 
    {2, 1}, 
    {3, 0}, 
    {4, 0}, 
    {5, 1},
    {6, 0}
};

int findAutoType(int attrType){
    int ret = -1;

    for(int i = 0; i < ATTRCOUNT; i++){
        if(attributeDefinitions[i].attrType == attrType){
            ret = attributeDefinitions[i].autoType;
            break;
        }
    }

    return ret;
}

int findAttribute(char * attributeName){
    int ret = -1;

    for(int i = 0; i < ATTRCOUNT; i++){
        if(!strcmp(attributeDefinitions[i].name, attributeName)){
            ret = attributeDefinitions[i].attrType;
            break;
        }
    }

    return ret;
}

void setAttribute(Hashlist * attributes, int attrType, void * value, int stringLength){
    Auto * au = createAuto(findAutoType(attrType), value, stringLength);
    
    if(HLS_get(*attributes, attrType)){
        HLS_set(*attributes, attrType, au, &destroyAuto, 1);
    }
    else{
        HLS_add(attributes, attrType, au, &destroyAuto);
    }
}

void unsetAttribute(Hashlist * attributes, int attrType){
    if(HLS_get(*attributes, attrType)){
        HLS_remove(attributes, attrType, 1);
    }
}

int getOrientation(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_ORIENTATION);
    if(!au) return GUI_ORIENTATION_VERTICAL;
    else return getInt(au);
}

int getWidth(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_WIDTH);
    if(!au) return GUI_SIZE_MIN;
    else return getInt(au);
}

int getHeight(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_HEIGHT);
    if(!au) return GUI_SIZE_MIN;
    else return getInt(au);
}

Box getMargin(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_MARGIN);
    if(!au) return (Box){0, 0, 0, 0};
    else return getBox(au);
}

Box getPadding(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_PADDING);
    if(!au) return (Box){0, 0, 0, 0};
    else return getBox(au);
}

Alignment getItemAlignment(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_ITEM_ALIGNMENT);
    if(!au) return (Alignment){GUI_ALIGNMENT_START, GUI_ALIGNMENT_START};
    else return getAlignment(au);
}

Uint32 getId(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_ID);
    if(!au) return 0;
    else return getHex(au);
}