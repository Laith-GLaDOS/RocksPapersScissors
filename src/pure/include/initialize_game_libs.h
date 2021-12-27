#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int initializeGameLibs() {
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
        printGameFailedToStartMsg();
        printf(" - SDL_Init() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        printGameFailedToStartMsg();
        printf(" - IMG_Init() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
}