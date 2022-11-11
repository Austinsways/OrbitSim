#pragma once

#define _USE_MATH_DEFINES

#include "acceleration.h"
#include "earth.h"
#include "ship.h"
#include "game.h"
#include "entity.h"
#include "Sattelite.h"
#include "Fragment.h"

#include <cmath>
#include <cassert>

/**************************************************
 * DOUBLES
 **************************************************/
class EarthDummy : public Earth
{
public:
	Acceleration calculateGravity(Entity entity) { assert(false); }
	Position getPosition() { assert(false); }
	double getRadius() { assert(false); }
	double getTimeDilation() { assert(false); }
	void draw() { assert(false); }
	void advance() { assert(false); }
};

class ConcreteEntityDummy : public Entity  //this is an entity dummy that is not abstract to represent any entity properly
{
public:
	
	virtual void setPosition(Position pos) { assert(false); }
	virtual Position getPosition() const { assert(false); }
	virtual void setVelocity(Velocity vel) { assert(false); }
	virtual Velocity getVelocity() const { assert(false); }
	virtual double getRadius() const { assert(false); }
	virtual void advance(const Earth& earth) { assert(false); }
	virtual void kill() { assert(false); }
	virtual bool isDead() const { assert(false); }
	virtual std::list<Entity> destroy() { assert(false); }
	virtual void draw(ogstream& gout) { assert(false); }

};

class ConcreteSatteliteDummy : public Sattelite
{
public:
	
	virtual void setPosition(Position pos) { assert(false); }
	virtual Position getPosition() const { assert(false); }
	virtual void setVelocity(Velocity vel) { assert(false); }
	virtual Velocity getVelocity() const { assert(false); }
	virtual double getRadius() const { assert(false); }
	virtual void advance(const Earth& earth) { assert(false); }
	virtual void kill() { assert(false); }
	virtual bool isDead() const { assert(false); }
	virtual std::list<Entity> destroy() { assert(false); }
	virtual void draw(ogstream& gout) { assert(false); }
	virtual void draw() { assert(false); };
};

class FragmentDummy : public Fragment
{
	virtual void setPosition(Position pos) { assert(false); }
	virtual Position getPosition() const { assert(false); }
	virtual void setVelocity(Velocity vel) { assert(false); }
	virtual Velocity getVelocity() const { assert(false); }
	virtual double getRadius() const { assert(false); }
	virtual void advance(const Earth& earth) { assert(false); }
	virtual void kill() { assert(false); }
	virtual bool isDead() const { assert(false); }
	virtual std::list<Entity> destroy() { assert(false); }
	virtual void draw(ogstream& gout) { assert(false); }
	virtual void draw() { assert(false); };
};

class AccelerationDummy : public Acceleration
{
public:
	double getDdx() { assert(false); }
	double getDdy() { assert(false); }
};

class AccelerationStubZero : public AccelerationDummy
{
public:
	double getDdx() { return 0.0; }
	double getDdy() { return 0.0; }
};

class EarthStubTimePerFrame1 : public EarthDummy
{
public:
	double getTimePerFrame() { return 1.0; }
};

class EarthStubNoGravity : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(Entity entity) { return AccelerationStubZero(); }
};

class AccelerationStubDdx100 : public AccelerationDummy
{
public:
	double getDdx() { return 100.0; }
	double getDdy() { return 0.0; }
};

class EarthStubGravityDdx100 : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(Entity entity) { return AccelerationStubDdx100(); }
};

static int movementsOfEarthAdvance;
class EarthSpyAdvance : public EarthDummy
{
public:
	void advance() { movementsOfEarthAdvance++; };
};

static int movementsOfEntityAdvance;
class EntitySpyAdvance : public ConcreteEntityDummy
{
public:
	void advance() { movementsOfEntityAdvance++; };
};

//this returns the items location as the middle of the board
class StubEntityPosCenter : public ConcreteEntityDummy
{
public:
	Position getPosition() { return Position((int)0, (int)0); }
};

//this returns the earth at the center of the board.
class StubEarthPosCenter : public EarthDummy
{
public:
	Position position = Position((int)0, (int)0);
	Position getPosition() { return Position((int)0, (int)0); }
};

class StubSattelitePosCenter : public ConcreteSatteliteDummy
{
public:
	Position getPosition() {return Position((int)0, (int)0);}
};

class StubFragmentPosCenter : public FragmentDummy
{
public:
	Position getPosition() { return Position(0, 0); }
};





/**************************************************
 * TEST Game
 * Unit tests for the Game class
 **************************************************/
class TestGame
{
public:
	void run()
	{
		normalAdvanceEarth();
		normalAdvanceEntity();
		entityCollision();
		concreteEarth();
		properConstruction();
		satteliteCrash();
		fragmentCrash();
	}

private:
	//All entities should progress once each time the advance function is called
	void normalAdvanceEarth() {
		//setup
		Game game;
		EarthSpyAdvance earthSpy;
		game.earth = earthSpy;
		//excersize
		game.advance();
		//verify
		assert(movementsOfEarthAdvance == 1);
		//teardown
	}

	void normalAdvanceEntity() {
		//setup
		Game game;
		EntitySpyAdvance entitySpy;
		game.entitys->push_back(entitySpy); //adding the spy to the list of entitys
		//excersize
		game.advance();
		//verify
		assert(movementsOfEntityAdvance == 1);
		//teardown
	}

	void entityCollision() {
		//setup 
		Game game;
		//two entitys overlapping eachother/colliding
		StubEntityPosCenter entity1;
		StubEntityPosCenter entity2;

		//excersize
		bool collided = game.checkCollision(entity1, entity2);
		//verify
		assert(collided);
		//teardown
	}

	//ensure earth doesnt move when collided with
	void concreteEarth() {
		//setup 
		Game game;
		//two entitys overlapping eachother/colliding
		StubEntityPosCenter entity1;
		StubEarthPosCenter earth1;

		//excersize
		bool collided = game.checkCollision(entity1, earth1);
		//verify
		assert(collided);
		earth1.position.getMetersX();
		assert(earth1.position.getMetersX() == 0.0);
		assert(earth1.position.getMetersY() == 0.0);
		//teardown
	}

	//game has all the necessary starting items
	void properConstruction() {
		//setup
		Game game;
		Earth blankEarth;
		//excersize
		//excersize completed in basic constructor
		//verify
		assert(game.entitys);
		assert(&game.earth);
		assert(&game.dreamChaser);
		//teardown
	}


	void satteliteCrash() {
		//setup
		Game game;
		StubSattelitePosCenter sattelite1;
		StubSattelitePosCenter sattelite2;
		//excersize
		bool collided = game.checkCollision(sattelite1, sattelite2);
		//verify
		assert(collided);
		//teardown0
	}

	void fragmentCrash() {
		//setup
		Game game;
		StubFragmentPosCenter fragment1;
		StubFragmentPosCenter fragment2;
		//excersize
		bool collided = game.checkCollision(fragment1, fragment2);
		//verify
		assert(collided);
		//teardown
	}
};
