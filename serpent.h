#ifndef SERPENT_H_INCLUDED
#define SERPENT_H_INCLUDED

#include <vector>
#include <cmath>

#include "segment.h"
#include "hax.h"
#include "time.h"

struct Serpent
{
    static float lifeTotal;
    static float speedTotal;
    static float accelerationTotal;
    static float currentEnergy;
    static float maxEnergy;
    static float energyProductionTotal;
    static float energyConsumptionTotal;

    enum enumPropulsionLevels
    {
        PROP_AHEAD_NEUTRAL = 0,
        PROP_AHEAD_SLOW = 1,
        PROP_AHEAD_STANDARD = 2,
        PROP_AHEAD_FULL = 3,
        PROP_AHEAD_FLANK = 4
    };
    static int propulsionLevel;
    static float propulsionAccelerationMod;
    static float propulsionEnergyConsumptionMod;

    enum enumRepairLevels
    {
        REP_DISABLED = 0,
        REP_SLOW = 1,
        REP_STANDARD = 2,
        REP_BOOSTED = 3,
        REP_EMERGENCY = 4
    };
    static int repairLevel;
    static float repairRateMod;
    static float repairEnergyConsumptionMod;

    enum enumAlertnessLevels
    {
        ALERT_OFF = 0,
        ALERT_MILD = 1,
        ALERT_STANDARD = 2,
        ALERT_HEIGHTENED = 3,
        ALERT_INTENSE = 4
    };
    static int alertnessLevel;
    static float alertnessShieldMod;
    static float alertnessEnergyConsumptionMod;

    static int totalLights;

    static Segment* headSegment;
    static Segment* keySegmentA;
    static Segment* keySegmentB;
    static Segment* keySegmentC;
    static Segment* tailSegment;
    static std::vector<Segment*>segments;

    static constexpr float ANCHOR_X_POSITION_MIN = 800;
    static constexpr float ANCHOR_X_POSITION_MAX = 1280;
    static float anchorXPosition;
    static float anchorXPositionTarget;

    static constexpr float ANCHOR_Y_POSITION_MIN = 240;
    static constexpr float ANCHOR_Y_POSITION_MAX = 480;
    static float anchorYPosition;
    static float anchorYPositionTarget;

    static constexpr float SEGMENT_X_SEPARATION_MIN = 32;
    static constexpr float SEGMENT_X_SEPARATION_MAX = 96;
    static float segmentXSeparation;
    static float segmentXSeparationTarget;

    static float pathAmplitude;
    static float pathAmplitudeTarget;
    static constexpr float PATH_AMPLITUDE_MIN = 100;
    static constexpr float PATH_AMPLITUDE_MAX = 400;
    static float pathWavelength;
    static float pathWavelengthTarget;
    static constexpr float PATH_WAVELENGTH_MIN = 200;
    static constexpr float PATH_WAVELENGTH_MAX = 1000;
    static float pathPhase; // radians

    static const unsigned MAX_SEGMENT = 13;
    static float pathYMod[MAX_SEGMENT];
    static float pathYModTarget[MAX_SEGMENT];
    static float pathSlopeMod[MAX_SEGMENT];

    Serpent();
    ~Serpent();
    static void Initialize();
    static void Uninitialize();

    static void Update();
    static void UpdateStats();
    static void UpdatePathCoordinates();

    static void UpdatePropulsionLevel();
    static void UpdateRepairLevel();
    static void UpdateAlertnessLevel();
};


#endif // SERPENT_H_INCLUDED
