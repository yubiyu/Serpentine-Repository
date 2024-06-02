#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

//#include <iostream> // debug only
#include <cmath> // abs

#include <allegro5/allegro5.h>

#include "tile.h"

struct Camera
{
    //static ALLEGRO_BITMAP* mainCameraBuffer;

    static constexpr float SCALE_MIN = 1.0;
    static constexpr float SCALE_MAX = 2.0;

    static ALLEGRO_TRANSFORM identityTransform; // identity transform
    static ALLEGRO_TRANSFORM zoomTransform;

    static float zoomScale;
    static float zoomTranslateX;
    static float zoomTranslateY;

    //static float mouseTransformedX;
    //static float mouseTransformedY;

    static bool atDestination;
    static int xCell, yCell;
    static float xPosition, yPosition;
    static float xDestination, yDestination;

    static void Initialize();
    static void Uninitialize();
    static void SetPosition(float x, float y);
    static void SetCell(int x, int y);
    static void SetDestination(float x, float y);
    static void SetDestinationCell(int x, int y);

    static void ApproachDestinationLinear(float change);
    static void ApproachDestinationFractional(float change);
    static void WarpToDestination();
};

#endif // CAMERA_H_INCLUDED
