#pragma once
#include "Field.h"

class MagneticField : public Field
{
public:
    explicit MagneticField(double B);
    double getB() const override;
private:
    double B_;
};