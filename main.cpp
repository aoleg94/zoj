#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);
    SDL_Event e;

    while(SDL_WaitEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            break;
        case SDL_JOYDEVICEADDED:
            break;
        }
    }

    SDL_Quit();
    return 0;
}

