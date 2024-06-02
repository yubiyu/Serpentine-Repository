#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <allegro5/allegro5.h>

struct Event
{
    static ALLEGRO_EVENT_QUEUE* eventQueue;
    static ALLEGRO_EVENT event;
};

#endif // EVENT_H_INCLUDED
