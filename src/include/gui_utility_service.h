/*
    Other functions not belonging to any service
    Treachery
*/

#pragma once

#include <SDL3/SDL.h>
#include <salvagames/list.h>

int stringToInt(char * value);
Uint32 stringToHex(char * value);
void destroyToken(void * token);
List tokenize(char * value);