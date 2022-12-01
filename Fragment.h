/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "shortLived.h"
#include "uiDraw.h"

class Fragment : public ShortLived
{
public:
   Fragment() { init(); }
   Fragment(const Position& position, const Velocity& velocity, double angle) : ShortLived(position, velocity, angle, random(5000.0, 9000.0)) { init(); }
   void draw(ogstream& gout) { drawFragment(position, angle); }

private:
   void init() { 
      radius = 2.0;
      life = (int)random(50.0, 100.0);
      angularVelocity = random(-0.1, 0.1);
   }
};
