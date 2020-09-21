#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game/Shooter.hh"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    {

    Solis::Shooter game;
    game.Init();
    game.RunMainLoop();

    }
    IMG_Quit();
    SDL_Quit();
}