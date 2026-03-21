#include "MagneticField.h"

MagneticField::MagneticField(double B) : B_(B) {}

double MagneticField::getB() const
{
    return B_;
}