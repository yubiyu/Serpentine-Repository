#include "segment.h"

Segment::Segment()
{
    Initialize();
}

Segment::~Segment()
{

}

void Segment::Initialize()
{
    alive = true;

    hasRepairFunction = false;
    repairFunctionActive = false;
    hasPropulsionFunction = false;
    propulsionFunctionActive = false;
    hasAlertnessFunction = false;
    alertnessFunctionActive = false;

    emitsGravitons = false;
    gravitonAEmissionTicks = 0;
    gravitonBEmissionTicks = 0;
    gravitonEmissionCD = 0;
    gravitonAAngleModifier = 0.0;
    gravitonBAngleModifier = 0.0;
    gravitonAPhase = 0.0;
    gravitonBPhase = 0.0;

    xPosition = 0;
    yPosition = 0;
    rotationAngle = 0.0;
    colour = 0;

    SetClassification(SEGMENT_CLASS_GENERIC);
    isDamaged = false;
}

void Segment::SetClassification(int setting)
{
    classification = setting;

    switch(setting)
    {
    case SEGMENT_CLASS_TAIL:
        hasRepairFunction = true;
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;
        colour = 6;
        numLights = 0;
        break;

    case SEGMENT_CLASS_GENERIC:
        colour = 7;
        numLights = 2;
        break;

    case SEGMENT_CLASS_KEY:
        hasRepairFunction = true;
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;
        colour = 6;
        numLights = 3;
        break;

    case SEGMENT_CLASS_HEAD:
        hasRepairFunction = true;
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;

        emitsGravitons = true;
        gravitonEmissionCD = GRAVITON_EMISSION_BASE_CD;
        gravitonBPhase = M_PI;
        gravitonBEmissionTicks = gravitonEmissionCD/2;
        colour = 6;
        numLights = 0;
        break;
    }
}

void Segment::Update()
{
    /*
    switch(classification)
    {
    case SEGMENT_CLASS_GENERIC:
        break;

    case SEGMENT_CLASS_HEAD:
        break;

    case SEGMENT_CLASS_KEY:
        break;

    case SEGMENT_CLASS_TAIL:
        break;
    }
    */

    if(emitsGravitons)
    {
        gravitonAEmissionTicks++;
        gravitonBEmissionTicks++;

        gravitonAPhase += 0.02;
        if(gravitonAPhase > 2*M_PI)
            gravitonAPhase = 0.0;
        gravitonBPhase += 0.02;
        if(gravitonBPhase > 2*M_PI)
            gravitonBPhase = 0.0;

        gravitonAAngleModifier = 0.125*std::sin(gravitonAPhase);
        gravitonBAngleModifier = 0.125*std::sin(gravitonBPhase);

        if(gravitonAEmissionTicks >= gravitonEmissionCD)
        {
            gravitonAEmissionTicks = 0;
            Graviton*newGravitonA = new Graviton();
            newGravitonA->Initialize(xPosition, yPosition, BASE_GRAVITON_PROJECTION_VELOCITY, rotationAngle-M_PI*0.750 + gravitonAAngleModifier);
            Graviton::streamA.push_back(newGravitonA);
        }
        if(gravitonBEmissionTicks >= gravitonEmissionCD)
        {
            gravitonBEmissionTicks = 0;
            Graviton*newGravitonB = new Graviton();
            newGravitonB->Initialize(xPosition, yPosition, BASE_GRAVITON_PROJECTION_VELOCITY, rotationAngle-M_PI*0.750 + gravitonBAngleModifier);
            Graviton::streamB.push_back(newGravitonB);
        }
    }
}

void Segment::ToggleRepairFunction()
{
    if(repairFunctionActive)
        repairFunctionActive = false;
    else
        repairFunctionActive = true;
}

void Segment::TogglePropulsionFunction()
{
    if(propulsionFunctionActive)
        propulsionFunctionActive = false;

    else
        propulsionFunctionActive = true;
}

void Segment::ToggleAlertnessFunction()
{
    if(alertnessFunctionActive)
        alertnessFunctionActive = false;
    else
        alertnessFunctionActive = true;
}

void Segment::ChangeColour()
{
    colour ++;
    if(colour >= NUM_SEGMENT_COLOURS)
        colour = 0;
}

void Segment::EmitDamageGraviton()
{
    Graviton*newGraviton = new Graviton();
    float angle = Hax::RandFloat(2*M_PI);
    newGraviton->Initialize(xPosition, yPosition, 1.0 , angle);
    Graviton::damageParticles.push_back(newGraviton);
}

void Segment::EmitRepairGraviton()
{
    Graviton*newGraviton = new Graviton();
    float angle = Hax::RandFloat(2*M_PI);
    newGraviton->Initialize(xPosition, yPosition, 1.0 , angle);
    Graviton::repairParticles.push_back(newGraviton);
}
