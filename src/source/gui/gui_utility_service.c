#include "../../include/gui_utility_service.h"

#include <stdlib.h>
#include <stdio.h>

int stringToInt(char * value){
    int index = 0, negativity = 1;

    if(value[index] == '-'){
        negativity = -1;
        index = 1;
    }

    int o = 0;

    while(value[index] != '\0'){
        o *= 10;
        o += value[index] - '0';

        index++;
    }

    return o * negativity;
}

Uint32 stringToHex(char * value){
    if(value[0] != '#'){
        return 0;
    }

    int index = 1;
    Uint32 o = 0;

    while(value[index] != '\0'){
        int number;

        switch(value[index]){
            case 'F': case 'f': number = 15; break;
            case 'E': case 'e': number = 14; break;
            case 'D': case 'd': number = 13; break;
            case 'C': case 'c': number = 12; break;
            case 'B': case 'b': number = 11; break;
            case 'A': case 'a': number = 10; break;
            default: number = value[index] - '0';
        }

        o *= 16;
        o += number;

        index++;
    }

    return o;
}

void destroyToken(void * token){
    free(token);
}

List tokenize(char * value){
    List o = LST_createList();

    int index = 0, oldIndex = 0;
    int length = 0;

    while(value[index] != '\0'){
        if((value[index] == ' ' || value[index] == '\n' || value[index] == '\t') && length > 0){
            char * token = malloc(length + 1);
            strncpy(token, &value[oldIndex], length);
            token[length] = '\0';

            LST_add(&o, token, &destroyToken);
            oldIndex = index + 1;
            length = 0;
        }
        else{
            length++;
        }

        index++;
    }

    char * token = malloc(length + 1);
    strncpy(token, &value[oldIndex], length);
    token[length] = '\0';

    LST_add(&o, token, &destroyToken);

    return o;
}