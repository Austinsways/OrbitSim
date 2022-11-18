#include "velocity.h"
#include "acceleration.h"

void Velocity::applyAcceleration(const Acceleration& acc)
{
   dx += acc.getDdx();
   dy += acc.getDdy();
}
