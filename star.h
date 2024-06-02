#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "hax.h"

#include <vector>

class Star
{
public:
    static std::vector<Star*>foregroundStarfield;
    static std::vector<Star*>centralStarfield;
    static std::vector<Star*>backgroundStarfield;
    static std::vector<Star*>farBackgroundStarfield;

    float xPosition;
    float yPosition;

    int variant;

    Star();
    ~Star();

    void Initialize(float x, float y);
    void Update();

    static void GenerateStarfield();
};

#endif // STAR_H_INCLUDED
