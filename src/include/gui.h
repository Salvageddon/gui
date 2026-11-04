/*
    Salva GUI v1.0

    prototypes of every function visible to user
*/

#pragma once

#include "gui_types.h"
#include "gui_enums.h"

/*
    Read GUI from and XML file for SDL_Surface.
    \param source path to the XML file
    \param sur target SDL_Surface
    \returns a GUI base context
*/
GUI_context * GUI_readGUI(const char * source, SDL_Surface * sur);

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
    \warning before first rendering, GUI MUST be baked using GUI_bakeGUI()
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
    Activate event listeners for specified GUI.
    \param base base of the GUI. You can pass any context from your GUI tree here, but it will listen for events only from specified context and it's children
    \param event current SDL event state
    \warning Call this inside your update loop. Otherwise it's useless
*/
void GUI_listenForEvents(GUI_context * base, SDL_Event event);

/*
    Append an event handler of specified event to context. 
    Will replace an existing event handler.
    \param context target GUI_context
    \param eventId id of event from GUI_eventTypes
    \param handler event handler function
*/
void GUI_appendEventHandler(GUI_context * context, unsigned int eventId, void (*handler)(GUI_context * context));

/*
    Find context by specified id.
    \param base base of a GUI. You can also pass any context from your GUI tree here
    \param id id from your id XML attribute
    \returns GUI_context with coresponding id or NULL if not found
*/
GUI_context * GUI_findContextById(GUI_context * base, unsigned int id);

/*
    Create font from bitmap.
    If not appended to any gui, must be freed with GUI_destroyFont().
    \param src path to the font file
    \param charWidth width of one character in pixels
    \param charHeight height of one character in pixels
    \param charsPerRow how many characters are stored in one row of characters
    \param mask color of the bitmap background. This is needed for recognizing which pixels belong to the character
    \returns GUI_font with font data or NULL
*/
GUI_font * GUI_createFont(const char * source, int charWidth, int charHeight, int charsPerRow, Uint32 mask);

/*
    Destroy a GUI_font.
    \param font GUI_font to be destroyed
*/
void GUI_destroyFont(GUI_font * font);

/*
    Append a GUI_font to a gui.
    \param base could be any context belonging to the target gui
    \param font font to be added
    \param fontKey unique font key needed for adressing them later
*/
void GUI_addFont(GUI_context * base, GUI_font * font, unsigned int fontKey);

/*
    Return a GUI_font matched by font key.
    \param base could be any context belonging to the target gui
    \param fontKey font key of the target font
    \returns found GUI_font data or NULL
*/
GUI_font * GUI_getFont(GUI_context * base, unsigned int fontKey);

/*
    Remove a GUI_font matched by font key.
    \param base could be any context belonging to the target gui
    \param fontKey font key of the target font
    \returns GUI_font removed from gui. Free it using GUI_destroyFont()
*/
GUI_font * GUI_removeFont(GUI_context * base, unsigned int fontKey);

/*
    Select a font that will be used to render text.
    \param base could be any context belonging to the target gui
    \param fontKey font key of the target font
*/
void GUI_setFocusFont(GUI_context * base, unsigned int fontKey);

/*
    Draw a rectangle on SDL_Surface.
    \param sur target SDL_Surface
    \param x x coordinate of the rectangle
    \param y y coordinate of the rectangle
    \param w width of the rectangle
    \param h height of the rectangle
    \param color color of the rectangle
*/
void GUI_drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);

/*
    Draw a filled rectangle on SDL_Surface.
    \param sur target SDL_Surface
    \param x x coordinate of the rectangle
    \param y y coordinate of the rectangle
    \param w width of the rectangle
    \param h height of the rectangle
    \param color color of the rectangle
*/
void GUI_fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);

/*
    Set specified pixel on a SDL_Surface.
    \param sur target SDL_Surface
    \param x x coordinate of the pixel
    \param y y coordinate of the pixel
    \param pixel new pixel to be set
    \warning for optimisation purposes location (x, y) is not checked if it exists on the sur. Also the surface is not checked for NULL
*/
void GUI_setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel);

/*
    Get specified pixel from a SDL_Surface.
    \param sur target SDL_Surface
    \param x x coordinate of the pixel
    \param y y coordinate of the pixel
    \returns color of the pixel
    \warning for optimisation purposes location (x, y) is not checked if it exists on the sur. Also the surface is not checked for NULL
*/
Uint32 GUI_getPixel(SDL_Surface * sur, int x, int y);

/*
    Convert Uint32 pixel into GUI_rgb.
    \param color color stored in Uint32 pixel
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in GUI_rgb
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
GUI_rgb GUI_getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert GUI_rgb into Uint32 pixel.
    \param color color stored in GUI_rgb
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in Uint32 pixel
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
Uint32 GUI_mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert Uint32 pixel into GUI_rgba.
    \param color color stored inUint32 pixel
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in GUI_rgba
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
GUI_rgba GUI_getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails);

/*
    Convert GUI_rgba into Uint32 pixel.
    \param color stored in GUI_rgba
    \param formatDetails SDL formatdetails passed for example from your SDL_Surface
    \returns color stored in Uint32 pixel
    \warning for optimisation purposes formatDetails is not checked for NULL
*/
Uint32 GUI_mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails);

/*
    Get recent error message.
    \returns error message
*/
char * GUI_getErrorMessage(void);