#ifndef XDOINJECTOR_H
#define XDOINJECTOR_H

extern "C" {
#include <xdo.h>
}

enum SpecialKey
{
    NONE,
    SHIFT,
    LSHIFT = SHIFT,
    RSHIFT,
    ALT,
    LALT = ALT,
    RALT,
    CTRL,
    LCTRL = CTRL,
    RCTRL,
    META,
    LMETA = META,
    RMETA
};

class XdoInjector
{
    xdo_t* xdo;
    Window selectedWindow;
    bool global;
    uint width, height;
public:
    XdoInjector();
    ~XdoInjector();
    void selectGlobal();
    void selectWindowBlocking();
    void injectMouseAbsolute(float x, float y);
    void injectKey(char c, bool up);
    void injectKey(SpecialKey sk, bool up);
    void update();
};

#endif // XDOINJECTOR_H
