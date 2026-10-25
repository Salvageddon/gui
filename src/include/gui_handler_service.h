/*
    Event handler calling functions
    Heresy
*/

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"

#include "gui_enums.h"
#include "gui_types.h"
#include <salvagames/hashlist.h>

void callEventHandler(GUI_context * context, Hashlist * eventHandlers, unsigned int eventType);