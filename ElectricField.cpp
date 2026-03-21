#include "ElectricField.h"

ElectricField::ElectricField(double Ex, double Ey) : Ex_(Ex), Ey_(Ey) {}

double ElectricField::getEx() const { return Ex_; }
double ElectricField::getEy() const { return Ey_; }