#include "graviton.h"

std::vector<Graviton*> Graviton::streamA;
std::vector<Graviton*> Graviton::streamB;

Graviton::Graviton()
{

}
Graviton::~Graviton()
{

}

void Graviton::Initialize(float xOrigin, float yOrigin, float initialVelocity, float initialAngle)
{
    alive = true;

    xPosition = xOrigin;
    yPosition = yOrigin;

    xVelocity = initialVelocity * std::cos(initialAngle);
    yVelocity = initialVelocity * std::sin(initialAngle);
}

void Graviton::Update()
{
    yVelocity += gravitationalAcceleration;

    xPosition += xVelocity;
    yPosition += yVelocity;

    if(xPosition < 0 || yPosition > 960)
        alive = false;

}
