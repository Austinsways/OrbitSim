#include "ship.h"

void Ship::accelerate(const Earth& earth)
{
   double acc = 30.0 * earth.getTimePerFrame() / 60.0;
   velocity.applyAcceleration(Acceleration(angle, acc));
}

Projectile Ship::fire()
{
    return Projectile();
}
