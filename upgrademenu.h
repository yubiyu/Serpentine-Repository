#ifndef UPGRADEMENU_H_INCLUDED
#define UPGRADEMENU_H_INCLUDED

#include <cmath>

#include "segment.h"

struct UpgradeMenu
{
    enum enumButtons
    {
        MENU_BUTTON_REPAIR,
        MENU_BUTTON_PROPULSION,
        MENU_BUTTON_ALERTNESS,
        MENU_BUTTON_RECOLOUR
    };

    static bool segmentSelected;
    static Segment* whichSegment;

    static float selectorCircleRotation;

    static float xPosition, yPosition;

    static constexpr float PROPULSION_BUTTON_X_OFFSET = -64-16;
    static constexpr float REPAIR_BUTTON_X_OFFSET = 0-16;
    static constexpr float ALERTNESS_BUTTON_X_OFFSET = 64-16;

    static constexpr float RECOLOUR_BUTTON_X_OFFSET = 0-16;

    static constexpr float BUTTONS_Y_OFFSET = 96-16;
    static constexpr float RECOLOUR_BUTTON_Y_OFFSET = -96-16;

    static void Initialize();
    static void Update();
};

#endif // UPGRADEMENU_H_INCLUDED
