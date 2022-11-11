#pragma once

#include "entity.h"
#include "earth.h"
#include "uiDraw.h"

class TestShip;

class Ship : public Entity
{
public:
   friend TestShip;

   Ship() : Entity() {}
   void turnLeft() {}
   void turnRight() {}
   void accelerate(const Earth& earth) {}
   virtual void draw(ogstream& gout) {}
private:

};
