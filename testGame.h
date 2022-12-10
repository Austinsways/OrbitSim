/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#define _USE_MATH_DEFINES

#include "position.h"
#include "earth.h"
#include "ship.h"
#include "game.h"
#include "entity.h"
#include "satellite.h"
#include "fragment.h"

#include <cmath>
#include <cassert>
#include <memory>

using namespace std;

/**************************************************
 * DOUBLES
 **************************************************/
class EarthDummy : public Earth
{
public:
   Acceleration calculateGravity(const Entity& entity) const { assert(false); return Acceleration(); }
   Position getPosition() const { assert(false); return Position(); }
   double getRadius() const { assert(false); return 0.0; }
   double getTimeDilation() const { assert(false); return 0.0; }
   void draw() const { assert(false); }
   void advance() { assert(false); }
};

class EntityDummy : public Entity  //this is an entity dummy that is not abstract to represent any entity properly
{
public:
   virtual void setPosition(const Position& pos) { assert(false); }
   virtual Position getPosition() const { assert(false); return Position(); }
   virtual void setVelocity(const Velocity& vel) { assert(false); }
   virtual Velocity getVelocity() const { assert(false); return Velocity(); }
   virtual double getRadius() const { assert(false); return 0.0; }
   virtual void advance(const Earth& earth) { assert(false); }
   virtual void kill() { assert(false); }
   virtual bool isDead() const { assert(false); return false; }
   virtual list<shared_ptr<Entity>> destroy() { assert(false); return list<shared_ptr<Entity>>(); }
   virtual void draw(ogstream& gout) { assert(false); }
};

class EarthSpyAdvance : public EarthDummy
{
public:
   void advance() { timesAdvanceCalled++; };
   static int timesAdvanceCalled;
};
int EarthSpyAdvance::timesAdvanceCalled = 0;

class EntitySpyAdvance : public EntityDummy
{
public:
   void advance(const Earth& earth) { timesAdvanceCalled++; };
   static int timesAdvanceCalled;
};
int EntitySpyAdvance::timesAdvanceCalled = 0;

class StubEntityPosCenter : public EntityDummy
{
public:
   Position getPosition() const { return Position(0.0, 0.0); }
};

class StubEntity_x0_y0_r10 : public EntityDummy
{
public:
   Position getPosition() const { return Position(0.0, 0.0); }
   double getRadius() const { return 10.0; }
};

class StubEntity_x10_y0_r10 : public EntityDummy
{
public:
   Position getPosition() const { return Position(10.0, 0.0); }
   double getRadius() const { return 10.0; }
};

class StubEntity_x20_y0_r10 : public EntityDummy
{
public:
   Position getPosition() const { return Position(20.0, 0.0); }
   double getRadius() const { return 10.0; }
};

class StubEntity_x50_y0_r10 : public EntityDummy
{
public:
   Position getPosition() const { return Position(50.0, 0.0); }
   double getRadius() const { return 10.0; }
};

class StubEarth_x0_y0_r10 : public EarthDummy
{
public:
   Position getPosition() const { return Position(0.0, 0.0); }
   double getRadius() const { return 10.0; }
};

/**************************************************
 * TEST GAME
 * Unit tests for the Game class
 **************************************************/
class TestGame
{
public:
   void run()
   {
      moveEntities_earthMoved();
      moveEntities_twoEntitiesMoved();
      checkCollision_entitiesOverlapping();
      checkCollision_entitiesTouching();
      checkCollision_entitiesNotTouching();
      checkCollision_entityAndEarthOverlapping();
      checkCollision_entityAndEarthTouching();
      checkCollision_entityAndEarthNotTouching();
   }

private:
   /**************************************************
    * ADVANCE - Check that the advance function is called once for the Earth
    **************************************************/
   void moveEntities_earthMoved()
   {
      // setup
      Game game;
      game.earth = make_unique<EarthSpyAdvance>();
      EarthSpyAdvance::timesAdvanceCalled = 0;
      game.entities.clear();

      // exercise
      game.moveEntities();

      // verify
      assert(EarthSpyAdvance::timesAdvanceCalled == 1);

      // teardown
   }

   /**************************************************
    * MOVE ENTITIES - Check that the advance function is called once per Entity
    **************************************************/
   void moveEntities_twoEntitiesMoved()
   {
      // setup
      Game game;
      EntitySpyAdvance entitySpy1;
      EntitySpyAdvance entitySpy2;
      EntitySpyAdvance::timesAdvanceCalled = 0;
      game.entities.clear();
      game.entities.push_back(make_unique<EntitySpyAdvance>(entitySpy1));
      game.entities.push_back(make_unique<EntitySpyAdvance>(entitySpy2));

      //exercise
      game.moveEntities();

      //verify
      assert(EntitySpyAdvance::timesAdvanceCalled == 2);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V ENTITY) - The two are overlapping
    **************************************************/
   void checkCollision_entitiesOverlapping()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x0_y0_r10 entity1;
      StubEntity_x10_y0_r10 entity2;

      //exercise
      bool collided = game.checkCollision(entity1, entity2);

      //verify
      assert(collided);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V ENTITY) - The two are tocuhing, which counts as a collision
    **************************************************/
   void checkCollision_entitiesTouching()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x0_y0_r10 entity1;
      StubEntity_x20_y0_r10 entity2;

      //exercise
      bool collided = game.checkCollision(entity1, entity2);

      //verify
      assert(collided);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V ENTITY) - The two are not touching
    **************************************************/
   void checkCollision_entitiesNotTouching()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x0_y0_r10 entity1;
      StubEntity_x50_y0_r10 entity2;

      //exercise
      bool collided = game.checkCollision(entity1, entity2);

      //verify
      assert(!collided);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V EARTH) - The two are overlapping
    * (For simplicity, the following tests will use an Earth with radius 10.0)
    **************************************************/
   void checkCollision_entityAndEarthOverlapping()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x10_y0_r10 entity;
      StubEarth_x0_y0_r10 earth;

      //exercise
      bool collided = game.checkCollision(entity, earth);

      //verify
      assert(collided);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V EARTH) - The two are touching, which counts as a collision
    **************************************************/
   void checkCollision_entityAndEarthTouching()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x20_y0_r10 entity;
      StubEarth_x0_y0_r10 earth;

      //exercise
      bool collided = game.checkCollision(entity, earth);

      //verify
      assert(collided);

      //teardown
   }

   /**************************************************
    * CHECK COLLISION (ENTITY V EARTH) - The two are not touching
    **************************************************/
   void checkCollision_entityAndEarthNotTouching()
   {
      //setup 
      Position::setZoom(1.0);
      Game game;

      StubEntity_x50_y0_r10 entity;
      StubEarth_x0_y0_r10 earth;

      //exercise
      bool collided = game.checkCollision(entity, earth);

      //verify
      assert(!collided);

      //teardown
   }
};
