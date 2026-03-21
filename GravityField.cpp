#include "GravityField.h"

GravityField::GravityField(double g) : g_(g) {}

double GravityField::getG() const
{
    return g_;
}