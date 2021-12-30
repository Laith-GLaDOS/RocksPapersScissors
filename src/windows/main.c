#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include "include/main_window.h"
#include "include/error_handling_and_error_messages.h"
#include "include/initialize_game_libs.h"
#include "include/resource_loader.h"

int main(int argc, char *argv[]) {
    if (initializeGameLibs() == -1) return -1;
    if (loadMainWindow() == -1) return -1;
    return 0;
}