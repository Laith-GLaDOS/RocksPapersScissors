#pragma once
#include <stdio.h>

void printGameFailedToStartMsg() {
    printf("Uh oh! The game has failed to start.\nTechnical info:\n");
}

void printSGEOutput() {
    printf(" - SDL_GetError() output: ");
    printf(SDL_GetError());
    printf("\n");
}

void printExitingMsg() {
    printf("Exiting!\n");
}