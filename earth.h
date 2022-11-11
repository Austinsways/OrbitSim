#pragma once

#include "position.h"
#include "acceleration.h"
#include "entity.h"
#include "uiDraw.h"

class Earth
{
public:
   Earth() {}
   virtual Acceleration calculateGravity(Entity entity) {}
   virtual Position getPosition() {}
   virtual double getRadius() {}
   virtual double getTimePerFrame() {}
   virtual void draw(ogstream gout) {}
   virtual void advance() {}

private:
   Position position;
   double radius;
   double angle;
   double timePerFrame;
};
