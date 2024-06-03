#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include "graviton.h"
#include "time.h"
#include "hax.h"

#include <iostream>

class Segment
{
public:
    enum enumClassification
    {
        SEGMENT_CLASS_TAIL = 0,
        SEGMENT_CLASS_GENERIC = 1,
        SEGMENT_CLASS_KEY = 2,
        SEGMENT_CLASS_HEAD = 3
    };
    static const int NUM_SEGMENT_CLASSIFICATIONS = 4;
    static const int NUM_SEGMENT_COLOURS = 20;

    static constexpr float BASE_GRAVITON_PROJECTION_VELOCITY = 2.5;

    int classification;
    bool alive;

    bool hasRepairFunction;
    bool repairFunctionActive;
    bool hasPropulsionFunction;
    bool propulsionFunctionActive;
    bool hasAlertnessFunction;
    bool alertnessFunctionActive;

    bool emitsGravitons;
    int gravitonAEmissionTicks, gravitonBEmissionTicks;
    int gravitonEmissionCD;
    static const int GRAVITON_EMISSION_BASE_CD = 12;

    float gravitonAPhase, gravitonAAngleModifier;
    float gravitonBPhase, gravitonBAngleModifier;

    float xPosition, yPosition;
    float rotationAngle;

    int colour;
    int numLights;
    bool isDamaged;

    Segment();
    ~Segment();

    void Initialize();
    void SetClassification(int setting);
    void Update();

    void ToggleRepairFunction();
    void TogglePropulsionFunction();
    void ToggleAlertnessFunction();
    void ChangeColour();

    void EmitDamageGraviton();
    void EmitRepairGraviton();

};

#endif // SEGMENT_H_INCLUDED
