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
   earth.draw(gout);
   for (auto& entity : entities)
      entity->draw(gout);
}

void Game::init()
{
   Position pos;
   pos.setPixelsX(-450.0);
   pos.setPixelsY( 450.0);
   Velocity vel(0.0, -2000.0);
   shared_ptr<Entity> ship = make_shared<Ship>(Ship(pos, vel, M_PI));
   entities.push_back(ship);
   this->ship = ship;
}

void Game::controlShip(const Interface* pUI)
{
   auto ship = dynamic_pointer_cast<Ship, Entity>(this->ship);

   if (pUI->isDown())
      ship->accelerate(earth);
      
   ship->setThrust(pUI->isDown());

   if (pUI->isLeft())
      ship->turnLeft();

   if (pUI->isRight())
      ship->turnRight();
}

void Game::moveEntities()
{
   earth.advance();
   for (auto& entity : entities)
      entity->advance(earth);
}

void Game::handleCollisions()
{
}

bool Game::checkCollision(const Entity& eOne, const Entity& eTwo)
{
    return false;
}

bool Game::checkCollision(const Entity& entity, const Earth& earth)
{
    return false;
}
