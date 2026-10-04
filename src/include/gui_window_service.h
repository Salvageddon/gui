/*
    Window management functions
*/

#pragma once

#include "gui_init_service.h"

#include "gui_types.h"

GUI_window * createWindow(char * title, int w, int h, Uint32 flags);
void destroyWindow(GUI_window * win);