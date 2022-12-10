/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#define _USE_MATH_DEFINES
#include <cmath>

#include "earth.h"
#include "entity.h"
#include "acceleration.h"


const double GRAVITY_SEA_LEVEL = 9.80665;
const double EARTH_RADIUS = 6378000.0;

/**************************************************
 * EARTH :: CALCULATE GRAVITY
 * Calculate the Acceleration due to gravity for an Entity
 **************************************************/
Acceleration Earth::calculateGravity(const Entity& entity) const
{
   Position entityPos = entity.getPosition();
   double altitude = sqrt(
      pow(entityPos.getMetersX() - position.getMetersX(), 2) +
      pow(entityPos.getMetersY() - position.getMetersY(), 2)
   ) - EARTH_RADIUS;
   double gravityMagnitude = GRAVITY_SEA_LEVEL *
      pow(EARTH_RADIUS / (EARTH_RADIUS + altitude), 2);
   double gravityDirection = atan2(
      position.getMetersX() - entityPos.getMetersX(),
      position.getMetersY() - entityPos.getMetersY()
   );

   return Acceleration(gravityDirection, gravityMagnitude);
}
