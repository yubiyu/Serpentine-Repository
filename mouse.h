#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "event.h"

struct Mouse
{
    static bool mouseAxesAltered; // Whether InputMouseXY() or InputMouseWheel() has been called this cycle. Reset if ALLEGRO_EVENT_MOUSE_AXES was not called.

    static bool mouseInput[];
    static bool mousewheelInput[];
    static int mouseButtonHoldTicks[];

    static float mouseDisplayX;
    static float mouseDisplayY;

    static void InputMouseXY();
    static void InputMousewheel();
    static void InputMouseDown();
    static void InputMouseUp();

    static void InputMouseButtonHold();

    enum enumInputMouseButtons
    {
        MOUSE_NOTHING = 0, // Allegro mouse buttons start counting from 1 for some reason, so this really is just filler.

        MOUSE_LEFT = 1,
        MOUSE_RIGHT = 2,
        MOUSE_MIDDLE = 3
    };

    enum enumInputMouseWheel
    {
        MOUSEWHEEL_UP = 0,
        MOUSEWHEEL_DOWN = 1
    };
};

#endif // MOUSE_H_INCLUDED
