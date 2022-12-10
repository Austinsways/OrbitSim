/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "position.h"
#include "velocity.h"
#include "uiDraw.h"

#include <list>
#include <vector>
#include <memory>

class Earth;

/**************************************************
 * ENTITY
 * Base class for all objects that respond to physics and orbit the Earth
 **************************************************/
class Entity
{
public:
   Entity() :
      radius(0.0),
      angle(0.0),
      dead(false),
      launchOffset(0.0),
      angularVelocity(0.0)
   {
   }
   Entity(const Position& pos, const Velocity& vel, double angle = 0.0, double launchSpeed = 0.0, double launchOffset = 12.0) :
      position(pos),
      velocity(vel),
      radius(0.0),
      angle(angle),
      dead(false),
      launchOffset(launchOffset),
      angularVelocity(0.0)
   {
      double offset = launchOffset * Position::getZoom();
      position.addMetersX(sin(angle) * offset);
      position.addMetersY(cos(angle) * offset);
      velocity.adjustDx(sin(angle) * launchSpeed);
      velocity.adjustDy(cos(angle) * launchSpeed);
   }
   virtual void setPosition(const Position& pos) { position = pos; }
   virtual Position getPosition() const { return position; }
   virtual void setVelocity(const Velocity& vel) { velocity = vel; }
   virtual Velocity getVelocity() const { return velocity; }
   // Radius is set in pixels, but we will return the value in meters
   virtual double getRadius() const { return radius * Position::getZoom(); }
   virtual void advance(const Earth& earth);
   virtual void kill() { dead = true; }
   virtual bool isDead() const { return dead; }
   virtual std::list<std::shared_ptr<Entity>> destroy()
   {
      return std::list<std::shared_ptr<Entity>>();
   }
   virtual void draw(ogstream& gout) = 0;
   template<typename ...Entities>
   inline std::list<std::shared_ptr<Entity>> createDestroyedList();

protected:
   Position position;
   Velocity velocity;
   double radius;
   double angle;
   bool dead;
   double launchOffset;
   double angularVelocity;

private:
   template<typename First, typename Second, typename ...Rest>
   inline void addNext(std::list<std::shared_ptr<Entity>>& entities, double angle, double offset);
   template<typename First>
   inline void addNext(std::list<std::shared_ptr<Entity>>& entities, double angle, double offset);
   template<class E>
   inline void addEntityToList(std::list<std::shared_ptr<Entity>>& entities, double angle);
};

/**************************************************
 * ENTITY :: CREATE DESTROYED LIST
 * This, and the following set of functions make it easy for classes deriving from Entity to implement
 * a destroy() method.
 * The function takes no parameters, but rather a variable amount of types to instantiate.
 * Calling the function like this would create 3 GPS parts and 2 Fragments, going clockwise:
 * createDestroyedList<GPSLeft, GPSCenter, Fragment, GPSRight, Fragment>();
 **************************************************/
template<typename ...Entities>
inline std::list<std::shared_ptr<Entity>> Entity::createDestroyedList()
{
   // Create a list of entities
   std::list<std::shared_ptr<Entity>> entities;
   // Get the variable number of entities
   const std::size_t n = sizeof...(Entities);
   // Get a random direction for the first piece to fly off in
   double angle = random(0.0, M_PI * 2.0);
   // Calculate the angle offset between each piece that flies off
   double offset = M_PI * 2.0 / n;
   // Pass all the Entity types into the recursive function
   addNext<Entities...>(entities, angle, offset);

   return entities;
}

/**************************************************
 * ENTITY :: ADD NEXT
 *
 * WARNING! Recursive type unpacking wizardry ahead...
 *
 * Take the first Entity type and add it to the list.
 * Then recursively call the function with the remaining Entity types (Second, Rest...)
 * We need to specify Second to avoid ambiguity with the base case function since Rest... can hold zero or more arguments.
 * i.e. This function gets called when there are two or more types remaining, and the other is called when there is only one.
 **************************************************/
template<typename First, typename Second, typename ...Rest>
inline void Entity::addNext(std::list<std::shared_ptr<Entity>>& entities, double angle, double offset)
{
   // Add the first Entity to the list
   addEntityToList<First>(entities, angle);
   // Continue until we run out of Entity types. (Note that First is not passed on)
   addNext<Second, Rest...>(entities, angle + offset, offset);
}

template<typename First>
inline void Entity::addNext(std::list<std::shared_ptr<Entity>>& entities, double angle, double offset)
{
   // Base case, add the final Entity and finish up
   addEntityToList<First>(entities, angle);
}

/**************************************************
 * ENTITY :: ADD ENTITY TO LIST
 * Add a single Entity of type E to the list.
 * Because of how E is used in this function, it will have to derive from Entity
 * and implement the correct constructor. Otherwise it won't compile.
 **************************************************/
template<class E>
inline void Entity::addEntityToList(std::list<std::shared_ptr<Entity>>& entities, double angle)
{
   entities.push_back(std::make_shared<E>(E(position, velocity, angle)));
}
