/*
    Salva GUI v1.0

    prototypes of every function visible to user
*/

#pragma once

#include "gui_types.h"

/*
    Read GUI from and XML file.
    \param source path to the XML file
    \returns a GUI base context
*/
GUI_context * GUI_readGUI(const char * source);

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
    Prepare GUI for rendering.
    \param context baking starting point
    \param format pixel format to bake controls in. Using one in your GUI_window->sur is recommended
*/
void GUI_bakeGUI(GUI_context * context, SDL_PixelFormat format);

/*
    Render baked GUI on the SDL_Surface.
    \param context rendering starting point
    \param sur target SDL_Surface
    \warning before rendering, GUI MUST be baked using GUI_bakeGUI()
*/
void GUI_renderGUI(GUI_context * context, SDL_Surface * sur);

/*
    Free all GUI controls recursively.
    \param context deletion starting point. Pass base to delete all GUI on a window
*/
void GUI_destroyGUI(GUI_context * context);

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
    Draw a rectangle on SDL_Surface
    \param sur target SDL_Surface
    \param x x coordinate of the rectangle
    \param y y coordinate of the rectangle
    \param w width of the rectangle
    \param h height of the rectangle
    \param color color of the rectangle
*/
void GUI_drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);

/*
    Draw a filled rectangle on SDL_Surface
    \param sur target SDL_Surface
    \param x x coordinate of the rectangle
    \param y y coordinate of the rectangle
    \param w width of the rectangle
    \param h height of the rectangle
    \param color color of the rectangle
*/
void GUI_fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);

/*
    Set specified pixel on a SDL_Surface
    \param sur target SDL_Surface
    \param x x coordinate of the pixel
    \param y y coordinate of the pixel
    \param pixel new pixel to be set
    \warning for optimisation purposes location (x, y) is not checked if it exists on the sur. Also the surface is not checked for NULL
*/
void GUI_setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel);

/*
    Get specified pixel from a SDL_Surface
    \param sur target SDL_Surface
    \param x x coordinate of the pixel
    \param y y coordinate of the pixel
    \returns color of the pixel
    \warning for optimisation purposes location (x, y) is not checked if it exists on the sur. Also the surface is not checked for NULL
*/
Uint32 GUI_getPixel(SDL_Surface * sur, int x, int y);

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