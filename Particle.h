#pragma once
#include "Body.h"

class Particle : public Body
{
public:
    // ¹¹Ôìº¯Êý
    Particle(int id, double mass, double x0, double y0,
        double vx0, double vy0, double q,
        double fx = 0, double fy = 0);
    void showInfo() override;
};