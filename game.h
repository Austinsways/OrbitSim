/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "position.h"
#include "entity.h"
#include "earth.h"
#include "ship.h"
#include "uiDraw.h"
#include "uiInteract.h"

#include <vector>
#include <list>
#include <memory>

class TestGame;

class Game
{
public:
   friend TestGame;

   Game() { init(); }
   Game(const Position& ptUpperRight) : ptUpperRight(ptUpperRight) { init(); }
   void advance(const Interface* pUI);
   void draw() const;

private:
   std::unique_ptr<Earth> earth;
   // The Ship will live inside the list of entities, but we will keep a pointer to it for convenience.
   std::shared_ptr<Entity> ship;
   std::list<std::shared_ptr<Entity>> entities;
   void init();
   void controlShip(const Interface* pUI);
   void moveEntities();
   void handleCollisions();
   bool checkCollision(const Entity& eOne, const Entity& eTwo) const;
   bool checkCollision(const Entity& entity, const Earth& earth) const;
   template<class T>
   void addEntity(const Position& pos, const Velocity& vel, double angle = 0.0);

   Position ptUpperRight;
};
