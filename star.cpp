#include "star.h"

std::vector<Star*> Star::foregroundStarfield;
std::vector<Star*> Star::centralStarfield;
std::vector<Star*> Star::backgroundStarfield;
std::vector<Star*> Star::farBackgroundStarfield;

Star::Star()
{

}

Star::~Star()
{

}

void Star::Initialize(float x, float y)
{
    xPosition = x;
    yPosition = y;

    if(rand()%60 == 0)
        variant = 1;
    else
        variant = 0;
}

void Star::Update()
{
    if(xPosition < 0)
    {
        xPosition = Hax::RandFloatRange(1280,1600);
        yPosition = Hax::RandFloat(960);

        if(rand()%60 == 0)
            variant = 1;
        else
            variant = 0;

    }
}

void Star::GenerateStarfield()
{
    for(int i = 0; i < 200; i++)
    {
        Star*newStar = new Star();
        farBackgroundStarfield.push_back(newStar);
        newStar->Initialize(Hax::RandFloatRange(0,1600), Hax::RandFloatRange(0,1024));
    }

    for(int i = 0; i < 50; i++)
    {
        Star*newStar = new Star();
        backgroundStarfield.push_back(newStar);
        newStar->Initialize(Hax::RandFloatRange(0,1600), Hax::RandFloatRange(0,1024));
    }

    for(int i = 0; i < 10; i++)
    {
        Star*newStar = new Star();
        centralStarfield.push_back(newStar);
        newStar->Initialize(Hax::RandFloatRange(0,1600), Hax::RandFloatRange(0,1024));
    }

    for(int i = 0; i < 3; i++)
    {
        Star*newStar = new Star();
        foregroundStarfield.push_back(newStar);
        newStar->Initialize(Hax::RandFloatRange(0,1600), Hax::RandFloatRange(0,1024));
    }

}
