#include "../../include/gui_attribute_service.h"

attributeData attributeDefinitions[ATTRCOUNT] = {
    {"orientation", GUI_ATTRIBUTE_ORIENTATION, AUTO_INT},
    {"width", GUI_ATTRIBUTE_WIDTH, AUTO_INT},
    {"height", GUI_ATTRIBUTE_HEIGHT, AUTO_INT},
};

char buttonAttributes[2] = {1, 2};
char linearViewAttributes[3] = {0, 1, 2};

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
    if(!au) return -1;
    else return getInt(au);
}

int getWidth(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_WIDTH);
    if(!au) return -1;
    else return getInt(au);
}

int getHeight(Hashlist attributes){
    Auto * au = HLS_get(attributes, GUI_ATTRIBUTE_HEIGHT);
    if(!au) return -1;
    else return getInt(au);
}