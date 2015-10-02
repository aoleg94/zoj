#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);

    SDL_Quit();
    return 0;
}

