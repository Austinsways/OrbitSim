/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#include "velocity.h"
#include "acceleration.h"

/**************************************************
 * VELOCITY :: APPLY ACCELERATION
 * Apply an Acceleration to the Velocity
 **************************************************/
void Velocity::applyAcceleration(const Acceleration& acc, double t)
{
   dx += acc.getDdx() * t;
   dy += acc.getDdy() * t;
}
