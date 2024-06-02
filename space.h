#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED

#include <cmath>

struct Space
{
    static constexpr float R1_TARGET = 8;
    static constexpr float G1_TARGET = 20;
    static constexpr float B1_TARGET = 30;
    static constexpr float R2_TARGET = 32;
    static constexpr float G2_TARGET = 42;
    static constexpr float B2_TARGET = 79;

    static float rComponent, gComponent, bComponent;
    static float phase;

    static void Initialize()
    {
        rComponent = R1_TARGET;
        gComponent = G1_TARGET;
        bComponent = B1_TARGET;

        phase = 0.0;
    }

    static void Update()
    {
        phase += 0.0002;
        if(phase > 2*M_PI)
            phase = 0;

        rComponent = R1_TARGET + std::abs(R2_TARGET*std::sin(phase));
        gComponent = G1_TARGET + std::abs(G2_TARGET*std::sin(phase));
        bComponent = B1_TARGET + std::abs(B2_TARGET*std::sin(phase));

    }
};

#endif // SPACE_H_INCLUDED
