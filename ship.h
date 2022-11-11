#pragma once

#include "entity.h"
#include "uiDraw.h"

class TestShip;

class Ship : public Entity
{
public:
   friend TestShip;

   Ship() : Entity() {}
   virtual void draw(ogstream& gout) {}
private:

};
