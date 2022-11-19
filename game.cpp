#define _USE_MATH_DEFINES
#include <cmath>

#include "game.h"
#include "ship.h"
#include "uiDraw.h"

#include <memory>

using namespace std;

void Game::advance(const Interface* pUI)
{
   controlShip(pUI);
   moveEntities();
   handleCollisions();
}

void Game::draw() const
{
   ogstream gout(ptUpperRight);
   earth->draw(gout);
   for (auto& entity : entities)
      entity->draw(gout);
}

void Game::init()
{
   earth = make_unique<Earth>();
   Position pos;
   pos.setPixelsX(-450.0);
   pos.setPixelsY(450.0);
   Velocity vel(0.0, -2000.0);
   shared_ptr<Entity> ship = make_shared<Ship>(Ship(pos, vel, M_PI));
   entities.push_back(ship);
   this->ship = ship;
}

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
}

void Game::moveEntities()
{
   earth->advance();
   for (auto& entity : entities)
      entity->advance(*earth);
}

// Predicate used for filtering out dead entities
bool entityDead(shared_ptr<Entity> entity) { return entity->isDead(); }

void Game::handleCollisions()
{
   //we have to check all entitys against eachother. 
   for (auto entityOne = entities.begin(); entityOne != entities.end(); entityOne++)
   {
      //double for loops are required for this design
      for (auto entityTwo = entities.begin(); entityTwo != entities.end(); entityTwo++)
      {
         bool collided = checkCollision(**entityOne, **entityTwo);
         //add logic to destroy entitys and create fragments
         if (collided)
         {
            list<shared_ptr<Entity>> fragments = (*entityOne)->destroy(); //get the object from its shared pointer then call the destroy function
            for (auto& fragment : fragments)
            {
               entities.push_back(fragment); //append all the newly created fragments
            }
            (*entityOne)->kill();
            //entityOne has been destroyed and erased from the list, now its time for entityTwo
            fragments = (*entityTwo)->destroy(); //get the object from its shared pointer then call the destroy function
            for (auto& fragment : fragments)
            {
               entities.push_back(fragment); //append all the newly created fragments
            }
            (*entityTwo)->kill();
         }
      }
   }

   //we need to check earth against all entitys
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
