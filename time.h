#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <allegro5/allegro5.h>

struct Time
{
    static ALLEGRO_TIMER*FPSTimer;

    static constexpr float FPS = 60.0; // Governs the speed and period of things other than just redrawing speed, so be careful about changing FPS

};

#endif // TIME_H_INCLUDED
