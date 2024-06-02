#include "upgrademenu.h"

bool UpgradeMenu::segmentSelected;
Segment* UpgradeMenu::whichSegment;

float UpgradeMenu::selectorCircleRotation;

float UpgradeMenu::xPosition;
float UpgradeMenu::yPosition;

void UpgradeMenu::Initialize()
{
    segmentSelected = false;
    whichSegment = nullptr;

    selectorCircleRotation = 0.0;

    xPosition = 0;
    yPosition = 0;
}

void UpgradeMenu::Update()
{
    selectorCircleRotation += 0.01;
    if(selectorCircleRotation > 2*M_PI)
        selectorCircleRotation = 0.0;

    if(segmentSelected && whichSegment != nullptr)
    {
        xPosition = whichSegment->xPosition;
        yPosition = whichSegment->yPosition;
    }
}
