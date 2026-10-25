#include "../../include/gui_handler_service.h"

void callEventHandler(GUI_context * context, Hashlist * eventHandlers, unsigned int eventType){
    void (*handler)(GUI_context * context) = HLS_get(*eventHandlers, eventType);

    if(handler){
        handler(context);
    }
}