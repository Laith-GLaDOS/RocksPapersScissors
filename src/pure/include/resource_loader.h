#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "error_handling_and_error_messages.h"

SDL_Texture* rock = NULL;
SDL_Texture* paper = NULL;
SDL_Texture* scissor = NULL;
SDL_Texture* help_menu = NULL;
SDL_Texture* tie_msg = NULL;
SDL_Texture* win_msg = NULL;
SDL_Texture* lose_msg = NULL;
SDL_Texture* you_text = NULL;
SDL_Texture* computer_text = NULL;
SDL_AudioSpec win_soundeffect_spec;
Uint32 win_soundeffect_length;
Uint8* win_soundeffect_buffer;
SDL_AudioSpec lose_soundeffect_spec;
Uint32 lose_soundeffect_length;
Uint8* lose_soundeffect_buffer;
SDL_AudioSpec tie_soundeffect_spec;
Uint32 tie_soundeffect_length;
Uint8* tie_soundeffect_buffer;

int loadResources(SDL_Renderer* renderer) {
    rock = IMG_LoadTexture(renderer, "res/rock.png");
    paper = IMG_LoadTexture(renderer, "res/paper.png");
    scissor = IMG_LoadTexture(renderer, "res/scissor.png");
    help_menu = IMG_LoadTexture(renderer, "res/help_menu.png");
    tie_msg = IMG_LoadTexture(renderer, "res/tie_text.png");
    win_msg = IMG_LoadTexture(renderer, "res/you_win_text.png");
    lose_msg = IMG_LoadTexture(renderer, "res/you_lose_text.png");
    you_text = IMG_LoadTexture(renderer, "res/you_text.png");
    computer_text = IMG_LoadTexture(renderer, "res/computer_text.png");
    if (rock == NULL || paper == NULL || scissor == NULL || help_menu == NULL || tie_msg == NULL || win_msg == NULL || lose_msg == NULL || you_text == NULL || computer_text == NULL) {
        printGameFailedToStartMsg();
        printf(" - IMG_LoadTexture() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
    SDL_LoadWAV("res/win.wav", &win_soundeffect_spec, &win_soundeffect_buffer, &win_soundeffect_length);
    SDL_LoadWAV("res/lose.wav", &lose_soundeffect_spec, &lose_soundeffect_buffer, &lose_soundeffect_length);
    SDL_LoadWAV("res/tie.wav", &tie_soundeffect_spec, &tie_soundeffect_buffer, &tie_soundeffect_length);
    if (win_soundeffect_buffer == NULL || win_soundeffect_length == NULL || lose_soundeffect_buffer == NULL || lose_soundeffect_length == NULL || tie_soundeffect_buffer == NULL || tie_soundeffect_length == NULL) {
        printGameFailedToStartMsg();
        printf(" - SDL_LoadWAV() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
    return 0;
}