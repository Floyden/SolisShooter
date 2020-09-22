#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game/Shooter.hh"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    {

    Solis::Shooter game;
    game.Init();
    game.RunMainLoop();

    }
    SDL_Quit();
}