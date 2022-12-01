/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "shortLived.h"
#include "uiDraw.h"

#include <cmath>

class Projectile : public ShortLived
{
public:
   Projectile() : ShortLived() { init(); }
   Projectile(const Position& position, const Velocity& velocity, double angle) :
      ShortLived(position, velocity, angle, 9000.0, 19.0)
   {
      init();
   }
   void draw(ogstream& gout) { drawProjectile(position); }

private:
   void init()
   {
      radius = 1.0;
      life = 70;
   }
};
