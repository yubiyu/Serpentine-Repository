#ifndef STATION_H_INCLUDED
#define STATION_H_INCLUDED

#include "hax.h"
#include "time.h"

#include <string>

struct Station
{
    enum enumStations
    {
        STATION_NONE = -1,

        STATION_ORANGE = 0,
        STATION_TURNIP = 1,
        STATION_MANGO = 2,
    };
    static const int STATION_MARKER_FIRST = STATION_ORANGE;
    static const int STATION_MARKER_LAST = STATION_MANGO;

    static std::string stationNames[STATION_MARKER_LAST+1];

    static bool atStation;
    static int currentStation;
    static int nextStation;
    static float distanceToStation;
    static constexpr float STATION_MIN_SEPARATION = 15000;
    static constexpr float STATION_MAX_SEPARATION = 20000;
    static constexpr float STATION_WIDTH = 5000;
    static float widthRemaining;

    static float drawX;
    static float drawY;

    static constexpr float STATION_ARROW_X = 1200;
    static constexpr float STATION_ARROW_Y = 100;

    static constexpr float STATION_SPRITE_SIZE = 512;

    static void Initialize();
    static void Update(float serpentSpeed, float serpentYPosition);
    static void EnterStation();
    static void LeaveStation();
};

#endif // STATION_H_INCLUDED
