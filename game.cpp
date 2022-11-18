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
    //we have to check all entitys against eachother. 
    for (auto entityOne = entities.begin(); entityOne != entities.end(); entityOne++) {
        //double for loops are required for this design
        for (auto entityTwo = entities.begin(); entityTwo != entities.end(); entityTwo++) {
            bool collided = checkCollision(**entityOne, **entityTwo);
            //add logic to destroy entitys and create fragments
            if (collided) {
                list<shared_ptr<Entity>> fragments = entityOne->get()->destroy(); //get the object from its shared pointer then call the destroy function
                for (auto fragment : fragments) {
                    entities.push_back(fragment); //append all the newly created fragments
                }
                entityOne->get()->kill();
                //entityOne has been destroyed and erased from the list, now its time for entityTwo
                if (collided) {
                    list<shared_ptr<Entity>> fragments = entityTwo->get()->destroy(); //get the object from its shared pointer then call the destroy function
                    for (auto fragment : fragments) {
                        entities.push_back(fragment); //append all the newly created fragments
                    }
                }
                entityTwo->get()->kill();

                entities.remove_if(entityOne->get()->isDead());
            }
            
        }
    }

    entities.remove_if(entities.begin(), entities.end(),Entity::entityDead);

    //we need to check earth against all entitys
    int locationVSStart = 0;
    for (auto i = entities.begin(); i != entities.end(); i++) 
    {
        bool collided = checkCollision(**i, earth);
        if (collided) 
        {
            list<shared_ptr<Entity>> fragments = i->get()->destroy(); //get the object from its shared pointer then call the destroy function
            for (auto fragment : fragments) 
            {
                entities.push_back(fragment); //append all the newly created fragments
            }
            
            entities.erase(i);
            locationVSStart += 1;
            
        }
    }
}

bool Game::checkCollision(const Entity& eOne, const Entity& eTwo)
{
    //check if the items have collided, if they have return true
    double combinedRadii = eOne.getRadius() + eTwo.getRadius();
    Position entity1Pos = eOne.getPosition();
    Position entity2Pos = eTwo.getPosition();
    double distanceBetweenX = abs(entity1Pos.getMetersX() - entity2Pos.getMetersX());
    double distanceBetweenY = abs(entity1Pos.getMetersY() - entity2Pos.getMetersY());
    return (distanceBetweenX <= combinedRadii && distanceBetweenY <= combinedRadii); 
    //if both are less than than the radii then they are too close. Otherwise they arent colliding.
}

bool Game::checkCollision(const Entity& entity, const Earth& earth)
{
    //check if the items have collided, if they have return true
    double combinedRadii = entity.getRadius() + earth.getRadius();
    Position entity1Pos = entity.getPosition();
    Position earthPos = earth.getPosition();
    double distanceBetweenX = abs(entity1Pos.getMetersX() - earthPos.getMetersX());
    double distanceBetweenY = abs(entity1Pos.getMetersY() - earthPos.getMetersY());
    return (distanceBetweenX <= combinedRadii && distanceBetweenY <= combinedRadii);
    //if both are less than than the radii then they are too close. Otherwise they arent colliding.
}
