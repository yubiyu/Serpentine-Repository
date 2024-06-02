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
    currentLife = maxLife = 100;
    lifeRecovery = 1;
    accelerationContribution = 0.0;
    maxEnergyContribution = BASE_ENERGY_CAPACITY;
    energyProduction = 0;
    energyConsumption = 0;

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

    numLights = 0;

    SetClassification(SEGMENT_CLASS_GENERIC);
}

void Segment::SetClassification(int setting)
{
    classification = setting;

    switch(setting)
    {
    case SEGMENT_CLASS_GENERIC:
        numLights = 2;
        break;

    case SEGMENT_CLASS_HEAD:
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;

        emitsGravitons = true;
        gravitonEmissionCD = 6;
        gravitonBPhase = M_PI;
        gravitonBEmissionTicks = gravitonEmissionCD/2;
        break;

    case SEGMENT_CLASS_KEY:
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;

        accelerationContribution = 2;
        numLights = 3;
        break;

    case SEGMENT_CLASS_TAIL:
        hasPropulsionFunction = true;
        hasAlertnessFunction = true;
        accelerationContribution = 5;
        break;
    }
}

void Segment::Update()
{
    currentLife += lifeRecovery/Time::FPS;
    if(currentLife > maxLife)
        currentLife = maxLife;

    energyProduction = BASE_ENERGY_PRODUCTION;
    energyConsumption = BASE_ENERGY_CONSUMPTION;

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
            newGravitonA->Initialize(xPosition, yPosition, 3.0, rotationAngle-M_PI*0.750 + gravitonAAngleModifier);
            Graviton::streamA.push_back(newGravitonA);
        }
        if(gravitonBEmissionTicks >= gravitonEmissionCD)
        {
            gravitonBEmissionTicks = 0;
            Graviton*newGravitonB = new Graviton();
            newGravitonB->Initialize(xPosition, yPosition, 3.0, rotationAngle-M_PI*0.750 + gravitonBAngleModifier);
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
