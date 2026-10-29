#include "../../include/gui.h"
#include "../../include/gui_reader_service.h"
#include <stdio.h>

GUI_context * GUI_readGUI(const char * source, SDL_Surface * sur){
    if(!source){
        printf("GUI (readGUI()): Source cannot be NULL.\n");
        return NULL;
    }

    if(!sur){
        printf("GUI (readGUI()): Surface cannot be NULL.\n");
        return NULL;
    }

    return readGui(source, sur);
}

GUI_window * GUI_createWindow(char * title, int w, int h, Uint32 flags){
    return createWindow(title, w, h, flags);
}

void GUI_destroyWindow(GUI_window * window){
    if(!window){
        printf("GUI (destroyWindow()): Window cannot be NULL.\n");
        return;
    }

    destroyWindow(window);
}

void GUI_bakeGUI(GUI_context * context, SDL_PixelFormat format){
    if(!context){
        printf("GUI (bakeGUI()): Context cannot be NULL.\n");
        return;
    }

    bakeGui(context, format);
}

void GUI_renderGUI(GUI_context * context, SDL_Surface * sur){
    if(!context){
        printf("GUI (renderGUI()): Context cannot be NULL.\n");
        return;
    }

    if(!sur){
        printf("GUI (renderGUI()): Surface cannot be NULL.\n");
        return;
    }

    renderGui(context, sur);
}

void GUI_destroyGUI(GUI_context * context){
    if(!context){
        printf("GUI (destroyGUI()): Context cannot be NULL.\n");
        return;
    }

    destroyContext(context);
}

void GUI_init(Uint32 flags){
    init(flags);
}

void GUI_quit(void){
    quit();
}

void GUI_listenForEvents(GUI_context * base, SDL_Event event){
    if(!base){
        printf("GUI (listenForEvents()): Base cannot be NULL.\n");
        return;
    }

    listenForEvents(base, event);
}

void GUI_appendEventHandler(GUI_context * context, unsigned int eventId, void (*handler)(GUI_context * context)){
    if(!context){
        printf("GUI (appendEventHandler()): Context cannot be NULL.\n");
        return;
    }

    if(!handler){
        printf("GUI (appendEventHandler()): Handler cannot be NULL.\n");
        return;
    }

    setEventHandler(context, eventId, handler);
}

GUI_context * GUI_findContextById(GUI_context * base, unsigned int id){
    if(!base){
        printf("GUI (findContextById()): Base cannot be NULL.\n");
        return NULL;
    }

    return findContextById(base->settings, id);
}

GUI_font * GUI_createFont(const char * source, int charWidth, int charHeight, int charsPerRow, Uint32 mask){
    if(!source){
        printf("GUI (createFont()): Source path cannot be NULL.\n");
        return NULL;
    }

    return createFont(source, charWidth, charHeight, charsPerRow, mask);
}

void GUI_destroyFont(GUI_font * font){
    if(!font){
        printf("GUI (desroyFont()): Target font cannot be NULL.\n");
        return;
    }

    destroyFont(font);
}

void GUI_addFont(GUI_context * base, GUI_font * font, unsigned int fontKey){
    if(!base){
        printf("GUI (addFont()): Base cannot be NULL.\n");
        return;
    }

    if(!font){
        printf("GUI (addFont()): Font cannot be NULL.\n");
        return;
    }
    
    if(HLS_get(base->settings->fonts, fontKey)){
        printf("GUI (addFont()): Font with this key already exists.\n");
        return;
    }

    font->isAppended = 1;
    HLS_add(&base->settings->fonts, fontKey, font, &destroyFont);
}

GUI_font * GUI_getFont(GUI_context * base, unsigned int fontKey){
    if(!base){
        printf("GUI (getFont()): Base cannot be NULL.\n");
        return NULL;
    }

    return HLS_get(base->settings->fonts, fontKey);
}

GUI_font * GUI_removeFont(GUI_context * base, unsigned int fontKey){
    if(!base){
        printf("GUI (removeFont()): Base cannot be NULL.\n");
        return NULL;
    }

    GUI_font * font = HLS_get(base->settings->fonts, fontKey);
    if(!font){
        printf("GUI (removeFont()): Font with this key doesn't exist.\n");
        return NULL;
    }

    font->isAppended = 0;
    HLS_remove(&base->settings->fonts, fontKey, 0);

    return font;
}

void GUI_setFocusFont(GUI_context * base, unsigned int fontKey){
    if(!base){
        printf("GUI (setFocusFont()): Base cannot be NULL.\n");
        return;
    }

    if(!HLS_get(base->settings->fonts, fontKey)){
        printf("GUI (setFocusFont()): Font with this key doesn't exist.\n");
        return;
    }

    base->settings->focusedFont = fontKey;
}

void GUI_drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    if(!sur){
        printf("GUI (drawRect()): Surface cannot be NULL.\n");
        return;
    }

    drawRect(sur, x, y, w, h, color);
}

void GUI_fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    if(!sur){
        printf("GUI (fillRect()): Surface cannot be NULL.\n");
        return;
    }

    fillRect(sur, x, y, w, h, color);
}

void GUI_setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel){
    setPixel(sur, x, y, pixel);
}

Uint32 GUI_getPixel(SDL_Surface * sur, int x, int y){
    return getPixel(sur, x, y);
}

GUI_rgb GUI_getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    return getRGB(color, formatDetails);
}

Uint32 GUI_mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails){
    return mapRGB(color, formatDetails);
}

GUI_rgba GUI_getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    return getRGBA(color, formatDetails);
}

Uint32 GUI_mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails){
    return mapRGBA(color, formatDetails);
}

char * GUI_getErrorMessage(void){
    return getErrorMessage();
}