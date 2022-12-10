/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "position.h"
#include "uiDraw.h"

/**************************************************
 * STAR
 **************************************************/
class Star
{
public:
   Star(const Position& ptUpperRight) : phase((int)random(0, 255))
   {
      double x = ptUpperRight.getMetersX() / 2.0;
      double y = ptUpperRight.getMetersY() / 2.0;
      position = Position(random(-x, x), random(-y, y));
   }
   void draw(ogstream& gout) { drawStar(position, phase); }
   void incrementPhase() { phase++; }

private:
   Position position;
   unsigned char phase;
};
