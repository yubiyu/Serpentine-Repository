#include "mouse.h"

bool Mouse::mouseAxesAltered = false;

bool Mouse::mouseInput[] =
{
    false, // nothing

    false, // LEFT
    false, // RIGHT
    false  // MIDDLE
};

bool Mouse::mousewheelInput[] =
{
    false, // Wheel up
    false  // Wheel down
};

int Mouse::mouseButtonHoldTicks[] =
{
    0, // Nothing (due to Allegro buttons counting from 1 instead of 0

    0, // LEFT
    0, // RIGHT
    0  // MIDDLE
};

float Mouse::mouseDisplayX;
float Mouse::mouseDisplayY;

void Mouse::InputMouseXY()
{
    mouseAxesAltered = true;
    mouseDisplayX = Event::event.mouse.x;
    mouseDisplayY = Event::event.mouse.y;
}

void Mouse::InputMousewheel()
{
    mouseAxesAltered = true;

    if(Event::event.mouse.z > 0)
        mousewheelInput[MOUSEWHEEL_UP] = true;
    else
        mousewheelInput[MOUSEWHEEL_UP] = false;

    if(Event::event.mouse.z < 0)
        mousewheelInput[MOUSEWHEEL_DOWN] = true;
    else
        mousewheelInput[MOUSEWHEEL_DOWN] = false;
}

void Mouse::InputMouseDown()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = true;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = true;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = true;
        break;
    }
}

void Mouse::InputMouseUp()
{
    switch(Event::event.mouse.button)
    {
    case MOUSE_LEFT:
        mouseInput[MOUSE_LEFT] = false;
        mouseButtonHoldTicks[MOUSE_LEFT] = 0;
        break;
    case MOUSE_RIGHT:
        mouseInput[MOUSE_RIGHT] = false;
        mouseButtonHoldTicks[MOUSE_RIGHT] = 0;
        break;
    case MOUSE_MIDDLE:
        mouseInput[MOUSE_MIDDLE] = false;
        mouseButtonHoldTicks[MOUSE_MIDDLE] = 0;
        break;
    }
}

void Mouse::InputMouseButtonHold()
{
    if(mouseInput[MOUSE_LEFT])
        mouseButtonHoldTicks[MOUSE_LEFT] ++;
    if(mouseInput[MOUSE_RIGHT])
        mouseButtonHoldTicks[MOUSE_RIGHT] ++;
    if(mouseInput[MOUSE_MIDDLE])
        mouseButtonHoldTicks[MOUSE_MIDDLE] ++;
}
