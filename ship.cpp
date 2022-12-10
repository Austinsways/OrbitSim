/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#include "ship.h"

/**************************************************
 * SHIP :: ACCELERATE
 * Accelerate the Ship in the direction it's currently pointed
 **************************************************/
void Ship::accelerate(const Earth& earth)
{
   // Accelerate at 30m/s^2
   double acc = 30.0 / 60.0;
   velocity.applyAcceleration(Acceleration(angle, acc), earth.getTimePerFrame());
}
