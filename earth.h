#pragma once

#include "position.h"
#include "acceleration.h"
//#include "entity.h"
#include "uiDraw.h"

class Entity;

class Earth
{
public:
   Earth() : radius(0.0), angle(0.0), timePerFrame(0.0) {}
   virtual Acceleration calculateGravity(const Entity& entity) const;
   virtual Position getPosition() const { return position; }
   virtual double getRadius() const { return radius; }
   virtual double getTimePerFrame() const { return timePerFrame; }
   virtual void draw(ogstream& gout) const {}
   virtual void advance() {}

private:
   Position position;
   double radius;
   double angle;
   double timePerFrame;
};
