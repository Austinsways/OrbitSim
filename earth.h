#pragma once

#include "position.h"
#include "acceleration.h"
//#include "entity.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Entity;

class Earth
{
public:
   Earth() : radius(0.0), angle(0.0) {
      timePerFrame = 24.0 * 60.0 * Interface().frameRate();
   }
   virtual Acceleration calculateGravity(const Entity& entity) const;
   virtual Position getPosition() const { return position; }
   virtual double getRadius() const { return radius; }
   virtual double getTimePerFrame() const { return timePerFrame; }
   virtual void advance();
   virtual void draw(ogstream& gout) const { drawEarth(position, angle); }

private:
   Position position;
   double radius;
   double angle;
   double timePerFrame;
};
