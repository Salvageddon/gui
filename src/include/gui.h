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

/*
    Convert Uint32 pixel into GUI_rgb
    \param color color stored in Uint32 pixel
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in GUI_rgb
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
GUI_rgb GUI_getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert GUI_rgb into Uint32 pixel
    \param color color stored in GUI_rgb
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in Uint32 pixel
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
Uint32 GUI_mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert Uint32 pixel into GUI_rgba
    \param color color stored inUint32 pixel
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in GUI_rgba
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
GUI_rgba GUI_getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert GUI_rgba into Uint32 pixel
    \param color stored in GUI_rgba
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in Uint32 pixel
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
Uint32 GUI_mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails);