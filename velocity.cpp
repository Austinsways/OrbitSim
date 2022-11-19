#include "velocity.h"
#include "acceleration.h"

void Velocity::applyAcceleration(const Acceleration& acc, double t)
{
   dx += acc.getDdx() * t;
   dy += acc.getDdy() * t;
}
