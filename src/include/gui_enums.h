/*
    Enum values visible to user
*/

#pragma once

enum GUI_controlTypes{
    GUI_CONTROL_BUTTON = 0xA00000
};

enum GUI_AttributeTypes{
    GUI_ATTRIBUTE_ORIENTATION = 0xB00000,
    GUI_ATTRIBUTE_WIDTH,
    GUI_ATTRIBUTE_HEIGHT,
};

enum GUI_attributeValues{
    GUI_ORIENTATION_VERTICAL = 0xC00100,
    GUI_ORIENTATION_HORIZONTAL
};