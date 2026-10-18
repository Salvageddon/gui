#include "../../include/gui_errors_service.h"

char * errorMessage = "No errors detected yet\n";

char * getErrorMessage(void){
    return errorMessage;
}

void setErrorMessage(char * message){
    errorMessage = message;
}