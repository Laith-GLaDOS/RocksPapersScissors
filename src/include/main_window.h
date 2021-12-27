#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "error_handling_and_error_messages.h"
#include "resource_loader.h"
#include "game_logic.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_AudioDeviceID AudioDevice_1;
SDL_AudioDeviceID AudioDevice_2;
SDL_AudioDeviceID AudioDevice_3;
int loseSoundAlreadyPlayed = 0;
int winSoundAlreadyPlayed = 0;
int tieSoundAlreadyPlayed = 0;

void playLoseSound() {
    AudioDevice_1 = SDL_OpenAudioDevice(NULL, 0, &lose_soundeffect_spec, NULL, 0);
    SDL_QueueAudio(AudioDevice_2, lose_soundeffect_buffer, lose_soundeffect_length);
    SDL_PauseAudioDevice(AudioDevice_2, 0);
}

void playWinSound() {
    AudioDevice_2 = SDL_OpenAudioDevice(NULL, 0, &win_soundeffect_spec, NULL, 0);
    SDL_QueueAudio(AudioDevice_2, win_soundeffect_buffer, win_soundeffect_length);
    SDL_PauseAudioDevice(AudioDevice_2, 0);
}

void playTieSound() {
    AudioDevice_3 = SDL_OpenAudioDevice(NULL, 0, &tie_soundeffect_spec, NULL, 0);
    SDL_QueueAudio(AudioDevice_3, tie_soundeffect_buffer, tie_soundeffect_length);
    SDL_PauseAudioDevice(AudioDevice_3, 0);
}

void clearRendered() {
    SDL_RenderClear(renderer);
}

void renderNewSprite(SDL_Texture* texture, const int width, const int height, const int position_x, const int position_y) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.h = height;
    src.w = width;
    SDL_Rect dst;
    dst.x = position_x;
    dst.y = position_y;
    dst.h = src.h;
    dst.w = src.w;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void setRenderedBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void displayRendered() {
    SDL_RenderPresent(renderer);
}

int hand1 = 0;
int hand2 = 0;
int win_status = -1;

void renderHands() {
    #define rock_c 0
    #define paper_c 1
    #define scissor_c 2
    switch (hand1) {
        case rock_c:
            renderNewSprite(rock, 285, 243, 30, 100);
            break;
        case paper_c:
            renderNewSprite(paper, 395, 282, 30, 100);
            break;
        case scissor_c:
            renderNewSprite(scissor, 289, 216, 30, 100);
            break;
    }
    renderNewSprite(you_text, 61, 36, 125, 350);
    switch (hand2) {
        case rock_c:
            renderNewSprite(rock, 285, 243, 650, 100);
            break;
        case paper_c:
            renderNewSprite(paper, 395, 282, 650, 100);
            break;
        case scissor_c:
            renderNewSprite(scissor, 289, 216, 650, 100);
            break;
    }
    renderNewSprite(computer_text, 141, 34, 700, 350);
}

void renderStuff() {
    renderHands();
    renderNewSprite(help_menu, 353, 109, 325, 650);
    switch (win_status) {
        case -1: break;
        case 0:
            renderNewSprite(tie_msg, 58, 37, 450, 30);
            loseSoundAlreadyPlayed = 0;
            winSoundAlreadyPlayed = 0;
            if (!tieSoundAlreadyPlayed) {
                tieSoundAlreadyPlayed = 1;
                playTieSound();
            }
            break;
        case 1:
            renderNewSprite(lose_msg, 145, 44, 450, 30);
            winSoundAlreadyPlayed = 0;
            tieSoundAlreadyPlayed = 0;
            if (!loseSoundAlreadyPlayed) {
                loseSoundAlreadyPlayed = 1;
                playLoseSound();
            }
            break;
        case 2:
            renderNewSprite(win_msg, 128, 47, 450, 30);
            loseSoundAlreadyPlayed = 0;
            tieSoundAlreadyPlayed = 0;
            if (!winSoundAlreadyPlayed) {
                winSoundAlreadyPlayed = 1;
                playWinSound();
            }
            break;
    }
}

void createWindowLoop() {
    SDL_Event event;
    int gameIsRunning = 1;
    while (gameIsRunning) {
        clearRendered();
        setRenderedBackgroundColor(255, 219, 172, 255);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_DestroyWindow(window);
                    SDL_DestroyTexture(rock);
                    SDL_DestroyTexture(paper);
                    SDL_DestroyTexture(scissor);
                    SDL_DestroyTexture(help_menu);
                    SDL_CloseAudioDevice(AudioDevice_1);
                    SDL_CloseAudioDevice(AudioDevice_2);
                    SDL_CloseAudioDevice(AudioDevice_3);
                    SDL_Quit();
                    gameIsRunning = 0;
                    break;
                case SDL_KEYDOWN:
                    #define rock_c 0
                    #define paper_c 1
                    #define scissor_c 2
                    #define tie 0
                    #define playerwon 2
                    #define computerwon 1
                    switch (event.key.keysym.sym) {
                        case SDLK_r:
                            hand1 = rock_c;
                            generateRandomNumber();
                            hand2 = computerchoice;
                            win_status = checkGameStatus(rock_c);
                            break;
                        case SDLK_p:
                            hand1 = paper_c;
                            generateRandomNumber();
                            hand2 = computerchoice;
                            win_status = checkGameStatus(paper_c);
                            break;
                        case SDLK_s:
                            hand1 = scissor_c;
                            generateRandomNumber();
                            hand2 = computerchoice;
                            win_status = checkGameStatus(scissor_c);
                            break;
                    }
                    break;
            }
        }
        renderStuff();
        displayRendered();
    }
}

int loadMainWindow() {
    window = SDL_CreateWindow("Rocks, Papers, Scissors!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == NULL) {
        printGameFailedToStartMsg();
        printf(" - SDL_CreateWindow() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
    if (window == NULL) {
        printGameFailedToStartMsg();
        printf(" - SDL_CreateRenderer() failed\n");
        printSGEOutput();
        printExitingMsg();
        return -1;
    }
    if (loadResources(renderer) == -1) return -1;
    createWindowLoop();
    return 0;
}