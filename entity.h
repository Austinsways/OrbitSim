#pragma once

#include "position.h"
#include "velocity.h"
#include "earth.h"
#include "uiDraw.h"

#include <list>

class Entity
{
public:
   Entity() {}
   Entity(Position pos, Velocity vel) {}
   void setPosition(Position pos) {}
   Position getPosition() const {}
   void setVelocity(Velocity vel) {}
   Velocity getVelocity() const {}
   double getRadius() const {}
   virtual void advance(const Earth& earth) {}
   void kill() {}
   bool isDead() const {}
   virtual std::list<Entity> destroy() {}
   virtual void draw(ogstream& gout) = 0;

protected:
   Position position;
   Velocity velocity;
   double radius;
   double angle;
   bool dead;
};
