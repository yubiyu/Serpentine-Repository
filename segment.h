#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "graviton.h"
#include "time.h"

class Segment
{
public:
    enum enumClassification
    {
        SEGMENT_CLASS_HEAD = 0,
        SEGMENT_CLASS_KEY = 1,
        SEGMENT_CLASS_TAIL = 2,
        SEGMENT_CLASS_GENERIC = 3

    };
    static const int SEGMENT_CLASS_MARKER_BEGIN = SEGMENT_CLASS_HEAD;
    static const int SEGMENT_CLASS_MARKER_END = SEGMENT_CLASS_GENERIC;

    int classification;
    bool alive;
    int currentLife;
    int maxLife;
    int lifeRecovery;
    int accelerationContribution;
    int maxEnergyContribution;
    int energyProduction;
    int energyConsumption;
    static const int BASE_ENERGY_PRODUCTION = 45000;
    static const int BASE_ENERGY_CONSUMPTION = 45100;
    static const int BASE_ENERGY_CAPACITY = BASE_ENERGY_PRODUCTION*30;

    bool repairFunctionActive;
    bool hasPropulsionFunction;
    bool propulsionFunctionActive;
    bool hasAlertnessFunction;
    bool alertnessFunctionActive;

    bool emitsGravitons;
    int gravitonAEmissionTicks, gravitonBEmissionTicks;
    int gravitonEmissionCD;
    float gravitonAPhase, gravitonAAngleModifier;
    float gravitonBPhase, gravitonBAngleModifier;

    float xPosition, yPosition;
    float rotationAngle;

    int numLights;

    Segment();
    ~Segment();

    void Initialize();
    void SetClassification(int setting);
    void Update();
    void ToggleRepairFunction();
    void TogglePropulsionFunction();
    void ToggleAlertnessFunction();

};

#endif // SEGMENT_H_INCLUDED
