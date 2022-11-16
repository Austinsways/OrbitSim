#pragma once

#include "position.h"
#include "velocity.h"
//#include "earth.h"
#include "uiDraw.h"

#include <list>
#include <memory>

class Earth;

class Entity
{
public:
   Entity() : radius(0.0), angle(0.0), dead(false) {}
   Entity(const Position& pos, const Velocity& vel) : radius(0.0), angle(0.0), dead(false) {}
   virtual void setPosition(const Position& pos) { position = pos; }
   virtual Position getPosition() const { return position; }
   virtual void setVelocity(const Velocity& vel) { velocity = vel; }
   virtual Velocity getVelocity() const { return velocity; }
   virtual double getRadius() const { return radius; }
   virtual void advance(const Earth& earth) {}
   virtual void kill() {}
   virtual bool isDead() const { return dead; }
   virtual std::list<std::unique_ptr<Entity>> destroy();
   virtual void draw(ogstream& gout) = 0;

protected:
   Position position;
   Velocity velocity;
   double radius;
   double angle;
   bool dead;
};
