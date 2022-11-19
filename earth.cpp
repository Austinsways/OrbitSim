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

void Earth::advance()
{
   angle -= 2.0 * M_PI / timePerFrame / 60.0;
}
