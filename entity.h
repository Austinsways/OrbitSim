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
   virtual void setPosition(Position pos) {}
   virtual Position getPosition() const {}
   virtual void setVelocity(Velocity vel) {}
   virtual Velocity getVelocity() const {}
   virtual double getRadius() const {}
   virtual void advance(const Earth& earth) {}
   virtual void kill() {}
   virtual bool isDead() const {}
   virtual std::list<Entity> destroy() {}
   virtual void draw(ogstream& gout) = 0;

protected:
   Position position;
   Velocity velocity;
   double radius;
   double angle;
   bool dead;
};
