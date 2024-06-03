#include "serpent.h"

int Serpent::numPassengers;

float Serpent::currentLife;
float Serpent::maxLife;
float Serpent::lifeRecovery;

float Serpent::speed; // Meters per second
float Serpent::acceleration;
float Serpent::viscousDrag;
float Serpent::wearRate;

float Serpent::currentEnergy;
float Serpent::maxEnergy;
float Serpent::energyProduction;
float Serpent::energyConsumption;
float Serpent::energyConsumptionMod;

float Serpent::repairSpeed;
float Serpent::repairAcceleration;
float Serpent::repairLoss;

float Serpent::currentAmneties;
float Serpent::amnetiesGeneration;
float Serpent::amnetiesAttenuation;

int Serpent::totalLights;

int Serpent::propulsionLevel;
float Serpent::propulsionAccelerationMod;
float Serpent::propulsionEnergyConsumptionMod;
float Serpent::propulsionEnergyTotal;

int Serpent::repairLevel;
float Serpent::repairAccelerationMod;
float Serpent::repairEnergyConsumptionMod;
float Serpent::repairEnergyTotal;

int Serpent::alertnessLevel;
float Serpent::alertnessShieldMod;
float Serpent::alertnessEnergyConsumptionMod;
float Serpent::alertnessEnergyTotal;

Segment* Serpent::headSegment;
Segment* Serpent::keySegmentA;
Segment* Serpent::keySegmentB;
Segment* Serpent::keySegmentC;
Segment* Serpent::tailSegment;
std::vector<Segment*> Serpent::segments;

float Serpent::anchorXPosition;
float Serpent::anchorXPositionTarget;
float Serpent::anchorYPosition;
float Serpent::anchorYPositionTarget;

float Serpent::segmentXSeparation;
float Serpent::segmentXSeparationTarget;

float Serpent::pathPhase;
float Serpent::pathWavelength;
float Serpent::pathWavelengthTarget;
float Serpent::pathAmplitude;
float Serpent::pathAmplitudeTarget;

float Serpent::pathYMod[MAX_SEGMENT];
float Serpent::pathYModTarget[MAX_SEGMENT];
float Serpent::pathSlopeMod[MAX_SEGMENT];

void Serpent::Initialize()
{
    numPassengers = 10;

    Segment* genericSegment;

    headSegment = new Segment();
    headSegment->SetClassification(Segment::SEGMENT_CLASS_HEAD);
    headSegment->colour = 0;
    segments.push_back(headSegment);

    genericSegment = new Segment();
    genericSegment->colour = 1;
    segments.push_back(genericSegment);

    genericSegment = new Segment();
    genericSegment->colour = 2;
    segments.push_back(genericSegment);

///

    keySegmentA = new Segment();
    keySegmentA->SetClassification(Segment::SEGMENT_CLASS_KEY);
    keySegmentA->colour = 3;
    segments.push_back(keySegmentA);

    genericSegment = new Segment();
    genericSegment->colour = 4;
    segments.push_back(genericSegment);

    genericSegment = new Segment();
    genericSegment->colour = 5;
    segments.push_back(genericSegment);

///
    keySegmentB = new Segment();
    keySegmentB->SetClassification(Segment::SEGMENT_CLASS_KEY);
    keySegmentB->colour = 6;
    segments.push_back(keySegmentB);

    genericSegment = new Segment();
    genericSegment->colour = 7;
    segments.push_back(genericSegment);

    genericSegment = new Segment();
    genericSegment->colour = 8;
    segments.push_back(genericSegment);

///
    keySegmentC = new Segment();
    keySegmentC->SetClassification(Segment::SEGMENT_CLASS_KEY);
    keySegmentC->colour = 9;
    segments.push_back(keySegmentC);

    genericSegment = new Segment();
    genericSegment->colour = 10;
    segments.push_back(genericSegment);

    genericSegment = new Segment();
    genericSegment->colour = 11;
    segments.push_back(genericSegment);

///
    tailSegment = new Segment();
    tailSegment->SetClassification(Segment::SEGMENT_CLASS_TAIL);
    tailSegment->colour = 12;
    segments.push_back(tailSegment);

    anchorXPosition = 200;
    anchorXPositionTarget = Hax::RandFloatRange(ANCHOR_X_POSITION_MIN, ANCHOR_X_POSITION_MAX);
    anchorYPosition = 480;
    anchorYPositionTarget = Hax::RandFloatRange(ANCHOR_Y_POSITION_MIN, ANCHOR_Y_POSITION_MAX);

    segmentXSeparation = segmentXSeparationTarget = SEGMENT_BASE_X_SEPARATION;

    currentLife = maxLife = BASE_LIFE;
    lifeRecovery = 0;
    currentAmneties = 0;
    amnetiesGeneration = 0;
    amnetiesAttenuation = 0;
    speed = 0;
    acceleration = BASE_ACCELERATION;
    viscousDrag = 0;
    wearRate = 0;
    currentEnergy = maxEnergy = BASE_ENERGY_CAPACITY;
    energyProduction = BASE_ENERGY_PRODUCTION;
    energyConsumption = BASE_ENERGY_CONSUMPTION;
    energyConsumptionMod = 1.0;

    totalLights = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        totalLights += (*it)->numLights;
    }

    UpdateRepairLevel();
    UpdatePropulsionLevel();
    UpdateAlertnessLevel();

    UpdateStats();

    pathAmplitude = pathAmplitudeTarget = PATH_AMPLITUDE_MIN;
    pathWavelength = pathWavelengthTarget = PATH_WAVELENGTH_MIN;
    pathPhase = 0.0;
    UpdatePathCoordinates();

}

void Serpent::Uninitialize()
{
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end();)
    {
        delete *it;
        segments.erase(it);
    }
}

void Serpent::Update()
{
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
        (*it)->Update();

    UpdateStats();
    UpdatePathCoordinates();
}

void Serpent::UpdateStats()
{
    acceleration = BASE_ACCELERATION + ACCELERATION_PER_PROPELLER*propulsionAccelerationMod;
    speed += acceleration/Time::FPS;
    viscousDrag = VISCOUS_DRAG_COEFFICIENT*speed;
    speed -= viscousDrag/Time::FPS;
    if(speed < 0)
        speed = 0;

    wearRate = viscousDrag*WEAR_RATIO;
    currentLife -= wearRate/Time::FPS;

    repairAcceleration = REPAIR_ACCELERATION_PER_MODULE*repairAccelerationMod;
    repairSpeed += repairAcceleration/Time::FPS;
    repairLoss = REPAIR_LOSS_COEFFICIENT*repairSpeed;
    repairSpeed -= repairLoss/Time::FPS;
    if(repairSpeed < 0)
        repairSpeed = 0;

    currentLife += repairSpeed/Time::FPS;

    if(currentLife > maxLife)
        currentLife = maxLife;
    if(currentLife < 0)
        currentLife = 0;

    amnetiesGeneration = AMNETIES_PER_GENERATOR*alertnessShieldMod;
    currentAmneties += amnetiesGeneration/Time::FPS;
    amnetiesAttenuation = AMNETIES_ATTENUATION_COEFFICIENT*currentAmneties;
    currentAmneties -= amnetiesAttenuation/Time::FPS;

    if(currentAmneties < 0)
        currentAmneties = 0;

    currentEnergy += energyProduction/Time::FPS;

    energyConsumptionMod = 1.0 + repairEnergyConsumptionMod + propulsionEnergyConsumptionMod + alertnessEnergyConsumptionMod;
    energyConsumption = BASE_ENERGY_CONSUMPTION * energyConsumptionMod;
    currentEnergy -= energyConsumption / Time::FPS;

    propulsionEnergyTotal = propulsionEnergyConsumptionMod * BASE_ENERGY_CONSUMPTION;
    repairEnergyTotal = repairEnergyConsumptionMod * BASE_ENERGY_CONSUMPTION;
    alertnessEnergyTotal = alertnessEnergyConsumptionMod * BASE_ENERGY_CONSUMPTION;

    if(currentEnergy < 0)
        currentEnergy = 0;
    else if(currentEnergy > maxEnergy)
        currentEnergy = maxEnergy;
}

void Serpent::UpdatePathCoordinates()
{
    pathPhase += 0.01;
    if(pathPhase > 2*M_PI)
    {
        pathPhase = 0;
        pathAmplitudeTarget = Hax::RandFloatRange(PATH_AMPLITUDE_MIN, PATH_AMPLITUDE_MAX);
        pathWavelengthTarget = Hax::RandFloatRange(PATH_WAVELENGTH_MIN, PATH_WAVELENGTH_MAX);

        anchorXPositionTarget = Hax::RandFloatRange(ANCHOR_X_POSITION_MIN, ANCHOR_X_POSITION_MAX);
        anchorYPositionTarget = Hax::RandFloatRange(ANCHOR_Y_POSITION_MIN, ANCHOR_Y_POSITION_MAX);
        segmentXSeparationTarget = SEGMENT_BASE_X_SEPARATION + speed/SEGMENT_SPEED_TO_X_SEPARATION_RATIO;
    }

    pathAmplitude += (pathAmplitudeTarget-pathAmplitude) * 0.01;
    pathWavelength += (pathWavelengthTarget-pathWavelength) * 0.01;

    float angle = (2*M_PI)/(pathWavelength) + pathPhase;

    for(unsigned i = 0; i < MAX_SEGMENT; i++)
    {
        pathYModTarget[i] = pathAmplitude*std::sin(angle + (float)i*0.3);
        pathYMod[i] += (pathYModTarget[i] - pathYMod[i]) * 0.01;
        pathSlopeMod[i] = std::cos(angle + (float)i*0.3)*(-1);
    }

    anchorXPosition += (anchorXPositionTarget - anchorXPosition)*0.0025;
    anchorYPosition += (anchorYPositionTarget - anchorYPosition)*0.005;

    if(segmentXSeparation > segmentXSeparationTarget)
        segmentXSeparation -= 0.1;
    else if(segmentXSeparation < segmentXSeparationTarget)
        segmentXSeparation += 0.1;

    int index = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        (*it)->xPosition = anchorXPosition - (segmentXSeparation*(float)index);
        (*it)->yPosition = anchorYPosition + pathYMod[index];
        (*it)->rotationAngle = pathSlopeMod[index];
        index++;
    }
}

void Serpent::UpdatePropulsionLevel()
{
    propulsionLevel = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        if((*it)->propulsionFunctionActive)
            propulsionLevel ++;
    }

    /** Quadratic formula: y = Ax^2 + Bx + C
        y IS propulsionEnergyConsumptionMod
        x = propLevel
        A = 0.1
        B = 1
        C = 0

        f(0) = 0
        f(1) = 1.1
        f(2) = 2.4
        f(3) = 3.9
        f(4) = 5.6
        f(5) = 7.5

        y IS propulsionAccelerationMod
        x = propLevel
        A = -0.1
        B = 2
        C = 0

        f(0) = 0.0
        f(1) = 1.9
        f(2) = 3.6
        f(3) = 5.1
        f(4) = 6.4
        f(5) = 7.5
    */

    propulsionEnergyConsumptionMod = 0.1*(std::pow(propulsionLevel,2)) + propulsionLevel + 0;
    propulsionAccelerationMod = -0.1*(std::pow(propulsionLevel,2)) + 2*propulsionLevel + 0;

    segments[0]->gravitonEmissionCD = Segment::GRAVITON_EMISSION_BASE_CD - 2*propulsionLevel;
}

void Serpent::UpdateRepairLevel()
{
    repairLevel = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        if((*it)->repairFunctionActive)
            repairLevel ++;
    }

    /** Quadratic formula: y = Ax^2 + Bx + C
        y IS repairEnergyConsumptionMod
        x = repairLevel
        A = 0.3
        B = 1
        C = 0

        f(0) = 0.0
        f(1) = 1.3
        f(2) = 3.2
        f(3) = 5.7
        f(4) = 8.8
        f(5) = 12.5

        y IS repairAccelerationMod
        x = repairLevel
        A = -0.1
        B = 2
        C = 0

        f(0) = 0.0
        f(1) = 1.9
        f(2) = 3.6
        f(3) = 5.1
        f(4) = 6.4
        f(5) = 7.5
    */

    repairEnergyConsumptionMod = 0.3*(std::pow(repairLevel,2)) + 1*repairLevel + 0;
    repairAccelerationMod = -0.1*(std::pow(repairLevel,2)) + 2*repairLevel + 0;
}

void Serpent::UpdateAlertnessLevel()
{
    alertnessLevel = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        if((*it)->alertnessFunctionActive)
            alertnessLevel ++;
    }

    /** Quadratic formula: y = Ax^2 + Bx + C
        y IS alertnessEnergyConsumptionMod
        x = alertnessLevel
        A = 0.2
        B = 0.4
        C = 0

        f(0) = 0.0
        f(1) = 0.6
        f(2) = 1.6
        f(3) = 3.3
        f(4) = 4.8
        f(5) = 7.0

        y IS alertnessShieldMod
        x = alertnessLevel
        A = -0.1
        B = 2
        C = 0

        f(1) = 1.9
        f(2) = 3.6
        f(3) = 5.1
        f(4) = 6.4
        f(5) = 7.5
    */

    alertnessEnergyConsumptionMod = 0.2*(std::pow(alertnessLevel,2)) + 0.4*alertnessLevel + 0;
    alertnessShieldMod = -0.1*(std::pow(alertnessLevel,2)) + 2*alertnessLevel + 0;

}
