#ifndef GRAVITON_H_INCLUDED
#define GRAVITON_H_INCLUDED

#include <vector>
#include <cmath>

class Graviton
{
public:
    static std::vector<Graviton*>streamA;
    static std::vector<Graviton*>streamB;
    static constexpr float gravitationalAcceleration = 0.004905;

    bool alive;
    float xPosition, yPosition;
    float xVelocity, yVelocity;

    Graviton();
    ~Graviton();

    void Initialize(float xOrigin, float yOrigin, float initialVelocity, float initialAngle);
    void Update();
};

#endif // GRAVITON_H_INCLUDED
