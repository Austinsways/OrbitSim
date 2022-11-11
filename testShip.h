#pragma once

#include "acceleration.h"
#include "earth.h"
#include "ship.h"

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

class EarthStubNoGravity : public EarthDummy
{
public:
	Acceleration calculateGravity(Entity entity) { return AccelerationStubZero(); }
	double getTimeDilation() { return 1.0; }
};

class AccelerationStubDdx100 : public AccelerationDummy
{
public:
	double getDdx() { return 100.0; }
	double getDdy() { return 0.0; }
};

class EarthStubGravityDdx100 : public EarthDummy
{
public:
	Acceleration calculateGravity(Entity entity) { return AccelerationStubDdx100(); }
	double getTimeDilation() { return 1.0; }
};

/**************************************************
 * TEST SHIP
 * Unit tests for the Ship class
 **************************************************/
class TestShip
{
public:
	void run()
	{
		advance_noMovement();
		advance_moveForward();
		advance_noMovementWithGravity();
	}

private:
	void advance_noMovement()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 0.0);

		// exercise
		ship.advance(EarthStubNoGravity());

		// verify
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(0.0, 0.0));

	}  // teardown

	void advance_moveForward()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 100.0);

		// exercise
		ship.advance(EarthStubNoGravity());

		// verify
		assert(ship.position == Position(0.0, 100.0));
		assert(ship.velocity == Velocity(0.0, 100.0));

	}  // teardown

	void advance_noMovementWithGravity()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 0.0);

		// exercise
		ship.advance(EarthStubGravityDdx100());

		// verify
		assert(ship.position == Position(0.0, 50.0));
		assert(ship.velocity == Velocity(0.0, 0.0));

	}  // teardown

	void advance_velocityAndGravity()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 25.0);

		// exercise
		ship.advance(EarthStubGravityDdx100());

		// verify
		assert(ship.position == Position(0.0, 75.0));
		assert(ship.velocity == Velocity(0.0, 25.0));

	}  // teardown
};
