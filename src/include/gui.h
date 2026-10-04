/*
    Salva GUI v1.0

    prototypes of every function visible to user
*/

#pragma once

#include "gui_types.h"

/*
    Create and show a window.
    \param title title of the window
    \param w width of the window
    \param h height of the window
    \param flags additional SDL flags
    \return a GUI window
*/
GUI_window * GUI_createWindow(char * title, int w, int h, Uint32 flags);

/*
    Free a window.
    \param window window to be destroyed
*/
void GUI_destroyWindow(GUI_window * window);

/*
    Init SDL. Use this for SDL_Init().
    \param flags SDL flags
*/
void GUI_init(Uint32 flags);

/*
    Quit SDL. Use this for SDL_Quit().
*/
void GUI_quit(void);