#pragma once
#include <time.h>
#include <stdlib.h>

int computerchoice;

int generateRandomNumber() {
    srand(time(NULL));
    computerchoice = rand() % 2;
    return computerchoice;
}

int checkGameStatus(int playerchoice) {
    #define tie 0
    #define playerwon 2
    #define computerwon 1
    #define rock_c 0
    #define paper_c 1
    #define scissor_c 2
    if (playerchoice == computerchoice)
        return tie;
    else if (playerchoice == rock_c && computerchoice == paper_c)
        return computerwon;
    else if (playerchoice == rock_c && computerchoice == scissor_c)
        return playerwon;
    else if (playerchoice == paper_c && computerchoice == rock_c)
        return playerwon;
    else if (playerchoice == paper_c && computerchoice == scissor_c)
        return computerwon;
    else if (playerchoice == scissor_c && computerchoice == rock_c)
        return computerwon;
    else if (playerchoice == scissor_c && computerchoice == paper_c)
        return playerwon;
}