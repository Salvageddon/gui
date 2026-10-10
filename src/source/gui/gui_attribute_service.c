#include "../../include/gui_attribute_service.h"

extern attributeData attributeDefinitions[ATTRCOUNT] = {
    {"orientation", GUI_ATTRIBUTE_ORIENTATION, AUTO_INT},
    {"width", GUI_ATTRIBUTE_WIDTH, AUTO_INT},
    {"height", GUI_ATTRIBUTE_HEIGHT, AUTO_INT},
};

int findAutoType(int attrType){
    int ret = -1;

    for(int i = 0; i < ATTRCOUNT; i++){
        if(attributeDefinitions[i].attrType == attrType){
            ret = attributeDefinitions[i].autoType;
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