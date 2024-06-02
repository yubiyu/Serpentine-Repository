#include "serpent.h"

float Serpent::lifeTotal;
float Serpent::speedTotal; // Meters per second
float Serpent::accelerationTotal;
float Serpent::currentEnergy;
float Serpent::maxEnergy;
float Serpent::energyProductionTotal;
float Serpent::energyConsumptionTotal;

int Serpent::propulsionLevel;
float Serpent::propulsionAccelerationMod;
float Serpent::propulsionEnergyConsumptionMod;

int Serpent::repairLevel;
float Serpent::repairRateMod;
float Serpent::repairEnergyConsumptionMod;

int Serpent::alertnessLevel;
float Serpent::alertnessShieldMod;
float Serpent::alertnessEnergyConsumptionMod;

int Serpent::totalLights;

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
    headSegment = new Segment();
    headSegment->SetClassification(Segment::SEGMENT_CLASS_HEAD);
    segments.push_back(headSegment);
    segments.push_back(new Segment());
    segments.push_back(new Segment());
    headSegment->propulsionFunctionActive = true;
    headSegment->alertnessFunctionActive = true;

    keySegmentA = new Segment();
    keySegmentA->SetClassification(Segment::SEGMENT_CLASS_KEY);
    segments.push_back(keySegmentA);
    segments.push_back(new Segment());
    segments.push_back(new Segment());

    keySegmentB = new Segment();
    keySegmentB->SetClassification(Segment::SEGMENT_CLASS_KEY);
    segments.push_back(keySegmentB);
    segments.push_back(new Segment());
    segments.push_back(new Segment());

    keySegmentC = new Segment();
    keySegmentC->SetClassification(Segment::SEGMENT_CLASS_KEY);
    segments.push_back(keySegmentC);
    segments.push_back(new Segment());
    segments.push_back(new Segment());

    tailSegment = new Segment();
    tailSegment->SetClassification(Segment::SEGMENT_CLASS_TAIL);
    segments.push_back(tailSegment);

    anchorXPosition = 200;
    anchorXPositionTarget = Hax::RandFloatRange(ANCHOR_X_POSITION_MIN, ANCHOR_X_POSITION_MAX);
    anchorYPosition = 480;
    anchorYPositionTarget = Hax::RandFloatRange(ANCHOR_Y_POSITION_MIN, ANCHOR_Y_POSITION_MAX);

    segmentXSeparation = segmentXSeparationTarget = Hax::RandFloatRange(SEGMENT_X_SEPARATION_MIN, SEGMENT_X_SEPARATION_MAX);

    speedTotal = 0;

    maxEnergy = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        maxEnergy += (*it)->maxEnergyContribution;
    }

    UpdateRepairLevel();
    UpdatePropulsionLevel();
    UpdateAlertnessLevel();

    currentEnergy = maxEnergy;
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
    lifeTotal = 0;
    accelerationTotal = 0;
    maxEnergy = 0;
    energyProductionTotal = 0;
    energyConsumptionTotal = 0;
    totalLights = 0;

    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        lifeTotal += (*it)->currentLife;
        accelerationTotal += (*it)->accelerationContribution;
        maxEnergy += (*it)->maxEnergyContribution;
        energyProductionTotal += (*it)->energyProduction;
        energyConsumptionTotal += (*it)->energyConsumption;
        totalLights += (*it)->numLights;
    }

    speedTotal += accelerationTotal/Time::FPS;

    currentEnergy += energyProductionTotal/Time::FPS;
    if(currentEnergy > maxEnergy)
        currentEnergy = maxEnergy;

    energyConsumptionTotal = energyConsumptionTotal * (1.0 + repairEnergyConsumptionMod+propulsionEnergyConsumptionMod+alertnessEnergyConsumptionMod);
    currentEnergy -= energyConsumptionTotal / Time::FPS;
    if(currentEnergy < 0)
        currentEnergy = 0;
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
        segmentXSeparationTarget = Hax::RandFloatRange(SEGMENT_X_SEPARATION_MIN, SEGMENT_X_SEPARATION_MAX);
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

    segmentXSeparation += (segmentXSeparationTarget-segmentXSeparation)*0.0005;

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

    switch(propulsionLevel)
    {
    case PROP_AHEAD_NEUTRAL:
        propulsionEnergyConsumptionMod = 0.0;
        propulsionAccelerationMod = 0.0;
        break;

    case PROP_AHEAD_SLOW:
        propulsionEnergyConsumptionMod = 0.5;
        propulsionAccelerationMod = 0.3;
        break;

    case PROP_AHEAD_STANDARD:
        propulsionEnergyConsumptionMod = 1.0;
        propulsionAccelerationMod = 1.0;
        break;

    case PROP_AHEAD_FULL:
        propulsionEnergyConsumptionMod = 1.5;
        propulsionAccelerationMod = 1.3;
        break;

    case PROP_AHEAD_FLANK:
        propulsionEnergyConsumptionMod = 2.5;
        propulsionAccelerationMod = 1.5;
        break;
    }
}

void Serpent::UpdateRepairLevel()
{
    repairLevel = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        if((*it)->repairFunctionActive)
            repairLevel ++;
    }

    switch(repairLevel)
    {
    case REP_DISABLED:
        repairEnergyConsumptionMod = 0.0;
        repairRateMod = 0.0;
        break;

    case REP_SLOW:
        repairEnergyConsumptionMod = 1.5;
        repairRateMod = 0.5;
        break;

    case REP_STANDARD:
        repairEnergyConsumptionMod = 3.0;
        repairRateMod = 1.0;
        break;

    case REP_BOOSTED:
        repairEnergyConsumptionMod = 6.0;
        repairRateMod = 2.0;
        break;

    case REP_EMERGENCY:
        repairEnergyConsumptionMod = 12.0;
        repairRateMod = 5.0;
        break;
    }
}

void Serpent::UpdateAlertnessLevel()
{
    alertnessLevel = 0;
    for(std::vector<Segment*>::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        if((*it)->alertnessFunctionActive)
            alertnessLevel ++;
    }

    switch(alertnessLevel)
    {
    case ALERT_OFF:
        alertnessEnergyConsumptionMod = 0.0;
        alertnessShieldMod = 0.0;
        break;

    case ALERT_MILD:
        alertnessEnergyConsumptionMod = 0.5;
        alertnessShieldMod = 0.5;
        break;

    case ALERT_STANDARD:
        alertnessEnergyConsumptionMod = 1.0;
        alertnessShieldMod = 1.0;
        break;

    case ALERT_HEIGHTENED:
        alertnessEnergyConsumptionMod = 1.5;
        alertnessShieldMod = 2.0;
        break;

    case ALERT_INTENSE:
        alertnessEnergyConsumptionMod = 2.0;
        alertnessShieldMod = 3.0;
        break;
    }
}
