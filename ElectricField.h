#pragma once
#include "Field.h"

class ElectricField : public Field
{
public:
    ElectricField(double Ex, double Ey);
    double getEx() const override;
    double getEy() const override;
private:
    double Ex_, Ey_;
};