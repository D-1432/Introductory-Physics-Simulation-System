#pragma once
#include "Field.h"

class GravityField : public Field
{
public:
    explicit GravityField(double g = -9.8);
    double getG() const override;
private:
    double g_;
};