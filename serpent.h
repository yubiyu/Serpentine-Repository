#ifndef SERPENT_H_INCLUDED
#define SERPENT_H_INCLUDED

#include "segment.h"
#include "hax.h"
#include "time.h"

#include <vector>
#include <cmath>
#include <iostream>

struct Serpent
{
    static int numPassengers;

    static float currentLife;
    static float maxLife;
    static constexpr float BASE_LIFE = 1000;
    static float lifeRecovery;
    static constexpr float LIFE_RECOVERY_PER_REPAIRER = 10;

    static float currentAmneties;
    static float amnetiesGeneration;
    static constexpr float AMNETIES_PER_GENERATOR = 15;
    static float amnetiesAttenuation;
    static constexpr float AMNETIES_ATTENUATION_COEFFICIENT = 0.10;

    static float speed;
    static float acceleration;
    static constexpr float BASE_ACCELERATION = 1;
    static constexpr float ACCELERATION_PER_PROPELLER = 15;
    static float viscousDrag;
    static constexpr float VISCOUS_DRAG_COEFFICIENT = 0.10;
    static float wearRate;
    static constexpr float WEAR_RATIO = 0.1;

    static float repairSpeed;
    static float repairAcceleration;
    static constexpr float REPAIR_ACCELERATION_PER_MODULE = 1.0;
    static float repairLoss;
    static constexpr float REPAIR_LOSS_COEFFICIENT = 0.10;

    static float currentEnergy;
    static float maxEnergy;
    static float energyProduction;
    static float energyConsumption;
    static float energyConsumptionMod;
    static constexpr float BASE_ENERGY_PRODUCTION = 60000;
    static constexpr float BASE_ENERGY_CONSUMPTION = 10000;
    static constexpr float BASE_ENERGY_CAPACITY = BASE_ENERGY_PRODUCTION*25;

    static int totalLights;

    static int propulsionLevel;
    static float propulsionAccelerationMod;
    static float propulsionEnergyConsumptionMod;
    static float propulsionEnergyTotal;

    static int repairLevel;
    static float repairAccelerationMod;
    static float repairEnergyConsumptionMod;
    static float repairEnergyTotal;

    static int alertnessLevel;
    static float alertnessShieldMod;
    static float alertnessEnergyConsumptionMod;
    static float alertnessEnergyTotal;

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

    static constexpr float SEGMENT_BASE_X_SEPARATION = 48;
    static constexpr float SEGMENT_SPEED_TO_X_SEPARATION_RATIO = 28.125; // (900 max speed / 32 increased separation at max speed)
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

    static int damagedSections;

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
