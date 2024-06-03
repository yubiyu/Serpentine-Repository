#include "station.h"

std::string Station::stationNames[STATION_MARKER_LAST+1];

bool Station::atStation;
int Station::currentStation;
int Station::nextStation;
float Station::distanceToStation;
float Station::widthRemaining;

float Station::drawX;
float Station::drawY;

void Station::Initialize()
{
    stationNames[0] = "Orange Station";
    stationNames[1] = "Turnip Station";
    stationNames[2] = "Dahlia Station";

    atStation = false;
    currentStation = STATION_NONE;
    nextStation = STATION_ORANGE;
    distanceToStation = Hax::RandFloatRange(STATION_MIN_SEPARATION, STATION_MIN_SEPARATION);

    drawX = 0;
    drawY = 0;

    widthRemaining = STATION_WIDTH;
}

void Station::Update(float serpentSpeed, float serpentYPosition)
{
    if(!atStation)
    {
        distanceToStation -= serpentSpeed/Time::FPS;
        if(distanceToStation <= 0)
            EnterStation();
    }
    else // atStation
    {
        widthRemaining -= serpentSpeed/Time::FPS;
        if(widthRemaining <= 0)
            LeaveStation();

        float traversedPercent = widthRemaining/STATION_WIDTH;

        drawX = (-1)*STATION_SPRITE_SIZE + traversedPercent*(1280+STATION_SPRITE_SIZE);
        drawY = serpentYPosition;
    }
}

void Station::EnterStation()
{
    atStation = true;
    currentStation = nextStation;
    nextStation ++;
    if(nextStation > STATION_MARKER_LAST)
        nextStation = STATION_MARKER_FIRST;

    distanceToStation = Hax::RandFloatRange(STATION_MIN_SEPARATION,STATION_MAX_SEPARATION);
    widthRemaining = STATION_WIDTH;

    drawX = 1280;
    drawY = 0;
}

void Station::LeaveStation()
{
    atStation = false;
}
