#include "camera.h"

//ALLEGRO_BITMAP* Camera::cameraBuffer;

ALLEGRO_TRANSFORM Camera::identityTransform; // identity transform
ALLEGRO_TRANSFORM Camera::zoomTransform;

float Camera::zoomScale;
float Camera::zoomTranslateX;
float Camera::zoomTranslateY;

bool Camera::atDestination;
int Camera::xCell;
int Camera::yCell;
float Camera::xPosition;
float Camera::yPosition;
float Camera::xDestination;
float Camera::yDestination;

void Camera::Initialize()
{
    al_identity_transform(&identityTransform);
    //mainCameraBuffer = al_create_bitmap(Scene::MAIN_W, Scene::MAIN_H);

    zoomScale = 1.0;
    zoomTranslateX = 0; // At 1.0 scale
    zoomTranslateY = 0;

    atDestination = true;
}

void Camera::Uninitialize()
{
    //al_destroy_bitmap(mainCameraBuffer);
}

void Camera::SetPosition(float x, float y)
{
    atDestination = true;
    xDestination = xPosition = x;
    yDestination = yPosition = y;
}
void Camera::SetCell(int x, int y)
{
    xCell = x;
    yCell = y;
    SetDestination(xCell*Tile::WIDTH, yCell*Tile::HEIGHT);
}
void Camera::SetDestination(float x, float y)
{
    atDestination = false;
    xDestination = x;
    yDestination = y;
}
void Camera::SetDestinationCell(int x, int y)
{
    SetDestination(x*Tile::WIDTH, y*Tile::HEIGHT);
}

void Camera::ApproachDestinationLinear(float change)
{
    if(!atDestination)
    {
        if(xPosition < xDestination)
            xPosition += change;
        else if(xPosition > xDestination)
            xPosition -= change;

        if(yPosition < yDestination)
            yPosition += change;
        else if(yPosition > yDestination)
            yPosition -= change;

        if(std::abs(xDestination - xPosition) <= 2.0 && std::abs(yDestination - yPosition) <= 2.0)
            WarpToDestination();
    }
}

void Camera::ApproachDestinationFractional(float change)
{
    if(!atDestination)
    {
        if(xPosition != xDestination)
            xPosition += (xDestination - xPosition)*change;

        if(yPosition != yDestination)
            yPosition += (yDestination - yPosition)*change;

        if(std::abs(xDestination - xPosition) <= 2.0 && std::abs(yDestination - yPosition) <= 2.0)
            WarpToDestination();
    }
}

void Camera::WarpToDestination()
{
    atDestination = true;
    xPosition = xDestination;
    yPosition = yDestination;
}
