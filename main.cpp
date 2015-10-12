#include <iostream>
#include "SDL2/SDL.h"
#include "xdoinjector.h"

using namespace std;

#define DEADZONE_PERCENT 5
#define DEADZONE 32768*DEADZONE_PERCENT/100;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);
    SDL_Event e;
    SDL_Joystick* js = nullptr;
    SDL_JoystickID jsid = 0;

    float mx, my;
    bool update = false;
    XdoInjector inj;
    inj.selectGlobal();
    inj.update();

    int x = 60000, y = 60000;

    while(SDL_WaitEvent(&e))
    {
        switch(e.type)
        {
        case SDL_QUIT:
            break;
        case SDL_JOYDEVICEADDED:
            if(!js)
            {
                js = SDL_JoystickOpen(e.jdevice.which);
                cout << SDL_JoystickName(js)
                     << " " << SDL_JoystickNumAxes(js)
                     << " " << SDL_JoystickNumButtons(js)
                     << " " << SDL_JoystickNumHats(js) << endl;
                jsid = e.jdevice.which;
            }
            break;
        case SDL_JOYDEVICEREMOVED:
            if(js && e.jdevice.which == jsid)
                js = nullptr, jsid = 0;
            break;
        case SDL_JOYAXISMOTION:
            if(js && jsid == e.jaxis.which)
            {
                //cout << "a" << (uint)e.jaxis.axis << " " << (int)e.jaxis.value << endl;
                if(e.jaxis.axis == 0)
                    x = e.jaxis.value;
                else if(e.jaxis.axis == 1)
                    y = e.jaxis.value;
                if(x < 60000 && y < 60000)
                {
                    update = true;
                    //cout << "move " << x << " " << y << endl;
                    mx = x/32768.0;
                    my = y/32768.0;
                }
            }
            break;
        case SDL_JOYHATMOTION:
            /*if(js && jsid == e.jhat.which)
                cout << "h" << (uint)e.jhat.hat << " " << (uint)e.jhat.value << endl;*/
            break;
        case SDL_JOYBUTTONUP:
        case SDL_JOYBUTTONDOWN:
            if(js && jsid == e.jbutton.which)
            {
                //cout << "b" << (uint)e.jbutton.button << " " << (uint)e.jbutton.state << endl;
            }
            break;
        }
        if(js)
        {
            if(update)
            {
                float cx, cy;
                inj.getMousePosition(&cx, &cy);
                mx = (mx+cx)/2;
                my = (my+cy)/2;
                inj.injectMouseAbsolute(mx, my);
                //update = false;
            }
            SDL_JoystickUpdate();
        }
    }

    SDL_Quit();
    return 0;
}

