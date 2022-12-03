/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#define _USE_MATH_DEFINES
#include <cmath>

#include "game.h"
#include "ship.h"
#include "entity.h"
#include "projectile.h"
#include "gps.h"
#include "sputnik.h"
#include "hubble.h"
#include "uiDraw.h"

#include <memory>
#include <list>

using namespace std;

/**************************************************
 * GAME :: ADVANCE
 **************************************************/
void Game::advance(const Interface* pUI)
{
   controlShip(pUI);
   moveEntities();
   handleCollisions();
}

/**************************************************
 * GAME :: DRAW
 **************************************************/
void Game::draw() const
{
   ogstream gout(ptUpperRight);
   earth->draw(gout);
   for (auto& entity : entities)
      entity->draw(gout);
}

/**************************************************
 * GAME :: ADD ENTITY
 * Helper function for adding an Entity to the simulation
 **************************************************/
template<class T>
void Game::addEntity(const Position& pos, const Velocity& vel, double angle)
{
   entities.push_back(make_shared<T>(T(pos, vel, angle)));
}

/**************************************************
 * GAME :: INIT
 * Set up the game
 **************************************************/
void Game::init()
{
   // Earth
   earth = make_unique<Earth>();
   // Ship
   Position pos;
   pos.setPixelsX(-450.0);
   pos.setPixelsY(450.0);
   Velocity vel(0.0, -2000.0);
   shared_ptr<Entity> ship = make_shared<Ship>(Ship(pos, vel, M_PI));
   entities.push_back(ship);
   this->ship = ship;
   // Sputnik
   addEntity<Sputnik>(Position(-36515095.13, 21082000), Velocity(2051, 2684.68));

   // GPS
   addEntity<GPS>(Position(0.0, 26560000.0), Velocity(-3880.0, 0.0));
   addEntity<GPS>(Position(0.0, -26560000.0), Velocity(3880.0, 0.0));
   addEntity<GPS>(Position(23001634.72, 13280000.0), Velocity(-1940.0, 3360.18));
   addEntity<GPS>(Position(23001634.72, -13280000.0), Velocity(1940.0, 3360.18));
   addEntity<GPS>(Position(-23001634.72, -13280000.0), Velocity(1940.0, -3360.18));
   addEntity<GPS>(Position(-23001634.72, 13280000.0), Velocity(-1940.0, -3360.18));
   // Hubble
   addEntity<Hubble>(Position(0.0, -42164000.0), Velocity(3100.0, 0.0));
   // Dragon

   // Starlink

}

/**************************************************
 * GAME :: CONTROL SHIP
 * Handle the Ship's movement
 **************************************************/
void Game::controlShip(const Interface* pUI)
{
   auto ship = dynamic_pointer_cast<Ship, Entity>(this->ship);

   if (pUI->isDown())
      ship->accelerate(*earth);

   ship->setThrust(pUI->isDown());

   if (pUI->isLeft())
      ship->turnLeft();

   if (pUI->isRight())
      ship->turnRight();

   if (pUI->isSpace() && !ship->isDead())
      entities.push_back(make_shared<Projectile>(ship->fire()));
}

/**************************************************
 * GAME :: MOVE ENTITIES
 **************************************************/
void Game::moveEntities()
{
   earth->advance();
   for (auto& entity : entities)
      entity->advance(*earth);
}

/**************************************************
 * ENTITY DEAD
 * Predicate used for filtering out dead entities
 **************************************************/
bool entityDead(shared_ptr<Entity> entity) { return entity->isDead(); }

/**************************************************
 * GAME :: HANDLE COLLISIONS
 * Handle all the collisions in the game and add any new Entities that result from collisions
 **************************************************/
void Game::handleCollisions()
{
   // To avoid checking collisions infinitely (i.e. something gets destroyed, but a new entity is
   // created on top of another one and the collisions go on forever) we will store any new entities
   // created in this round of collisions in a separate list and add them to our main list at the end.
   list<shared_ptr<Entity>> newEntities;

   // Entity v Entity
   for (auto entityOne = entities.begin(); entityOne != entities.end(); entityOne++)
      for (auto entityTwo = entities.begin(); entityTwo != entities.end(); entityTwo++)
         if (entityOne != entityTwo
            && checkCollision(**entityOne, **entityTwo)
            && !(*entityOne)->isDead()
            && !(*entityTwo)->isDead()
            )
         {
            // Destroy the two entities and move the created entities into our list
            newEntities.splice(newEntities.end(), (*entityOne)->destroy());
            newEntities.splice(newEntities.end(), (*entityTwo)->destroy());
            // Mark the entities as dead so they can't keep colliding and we can clean them up later
            (*entityOne)->kill();
            (*entityTwo)->kill();
         }

   // Merge our new entities into our existing list
   entities.splice(entities.end(), newEntities);

   // Entity v Earth
   for (auto entity = entities.begin(); entity != entities.end(); entity++)
   {
      bool collided = checkCollision(**entity, *earth);
      if (collided)
      {
         (*entity)->kill();
      }
   }

   // Cleanup
   entities.remove_if(entityDead);
}

/**************************************************
 * GAME :: CHECK COLLISION
 * Check for a collision between two Entities or an Entity and the Earth
 **************************************************/
bool Game::checkCollision(const Entity& eOne, const Entity& eTwo) const
{
   double combinedRadii = eOne.getRadius() + eTwo.getRadius();
   double distanceBetween = computeDistance(eOne.getPosition(), eTwo.getPosition());
   return distanceBetween <= combinedRadii;
}

bool Game::checkCollision(const Entity& entity, const Earth& earth) const
{
   double combinedRadii = entity.getRadius() + earth.getRadius();
   double distanceBetween = computeDistance(entity.getPosition(), earth.getPosition());
   return distanceBetween <= combinedRadii;
}
