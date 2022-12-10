/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "position.h"
#include "acceleration.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Entity;

/**************************************************
 * EARTH
 **************************************************/
class Earth
{
public:
   Earth() : radius(6378000.0), angle(0.0)
   {
      timePerFrame = 24.0 * 60.0 * Interface().frameRate();
   }
   virtual Acceleration calculateGravity(const Entity& entity) const;
   virtual Position getPosition() const { return position; }
   virtual double getRadius() const { return radius; }
   virtual double getTimePerFrame() const { return timePerFrame; }
   virtual void advance()
   {
      angle -= 2.0 * M_PI / timePerFrame / 60.0;
   }
   virtual void draw(ogstream& gout) const { drawEarth(position, angle); }

private:
   Position position;
   double radius;
   double angle;
   double timePerFrame;
};
