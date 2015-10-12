#include "xdoinjector.h"

XdoInjector::XdoInjector()
    : width(0), height(0)
{
    xdo = xdo_new("");
    selectedWindow = None;
}

XdoInjector::~XdoInjector()
{
    xdo_free(xdo);
}

void XdoInjector::selectGlobal()
{
    global = true;
}

void XdoInjector::selectWindowBlocking()
{
    global = false;
    xdo_select_window_with_click(xdo, &selectedWindow);
}

void XdoInjector::injectMouseAbsolute(float x, float y)
{
    int ix, iy;
    int screen = 0;
    xdo_get_mouse_location(xdo, &ix, &iy, &screen);
    ix = width * (x+1)/2;
    iy = height * (y+1)/2;
    if(global)
        xdo_move_mouse(xdo, ix, iy, screen);
    else
        xdo_move_mouse_relative_to_window(xdo, selectedWindow, ix, iy);
}

void XdoInjector::injectKey(char c, bool up)
{
    const char s[2] = {c, 0};
    if(up)
        xdo_send_keysequence_window_up(xdo, global ? CURRENTWINDOW : selectedWindow, s, 0);
    else
        xdo_send_keysequence_window_down(xdo, global ? CURRENTWINDOW : selectedWindow, s, 0);
}

struct SpecialKeyMapping {
    SpecialKey sk;
    const char* s;
} const mapping[] = {
    {LSHIFT, "Shift_L"},
    {RSHIFT, "Shift_R"},
    {LALT, "Alt_L"},
    {RALT, "Alt_R"},
    {LCTRL, "Control_L"},
    {RCTRL, "Control_R"},
    {LMETA, "Meta_L"},
    {RMETA, "Meta_R"},
    {NONE, nullptr}
};

void XdoInjector::injectKey(SpecialKey sk, bool up)
{
    const char* s = nullptr;
    for(auto m : mapping)
    {
        if(m.sk == sk)
            s = m.s;
    }
    if(up)
        xdo_send_keysequence_window_up(xdo, global ? CURRENTWINDOW : selectedWindow, s, 0);
    else
        xdo_send_keysequence_window_down(xdo, global ? CURRENTWINDOW : selectedWindow, s, 0);
}

void XdoInjector::getMousePosition(float *x, float *y)
{
    int ix, iy;
    int screen = 0;
    xdo_get_mouse_location(xdo, &ix, &iy, &screen);
    if(!global)
    {
        int wx, wy;
        xdo_get_window_location(xdo, selectedWindow, &wx, &wy, nullptr);
        ix -= wx;
        iy -= wy;
    }
    *x = (2*ix-width)/(float)width;
    *y = (2*iy-height)/(float)height;
}

void XdoInjector::update()
{
    if(global)
    {
        int ix, iy;
        int screen = 0;
        xdo_get_mouse_location(xdo, &ix, &iy, &screen);
        xdo_get_viewport_dimensions(xdo, &width, &height, screen);
    }
    else
        xdo_get_window_size(xdo, selectedWindow, &width, &height);
}

