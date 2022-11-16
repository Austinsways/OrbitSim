#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "acceleration.h"
#include "earth.h"
#include "ship.h"

#include <cassert>

/**************************************************
 * DOUBLES
 **************************************************/
class EarthDummy2 : public Earth
{
public:
	Acceleration calculateGravity(const Entity& entity) const { assert(false); return Acceleration(); }
	Position getPosition() const { assert(false); return Position(); }
	double getRadius() const { assert(false); return 0.0; }
	double getTimeDilation() const { assert(false); return 0.0; }
	void draw() const { assert(false); }
};

class AccelerationDummy : public Acceleration
{
public:
	double getDdx() const { assert(false); }
	double getDdy() const { assert(false); }
};

class AccelerationStubZero : public AccelerationDummy
{
public:
	double getDdx() const { return 0.0; }
	double getDdy() const { return 0.0; }
};

class EarthStubTimePerFrame1 : public EarthDummy2
{
public:
	double getTimePerFrame() const { return 1.0; }
};

class EarthStubNoGravity : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(const Entity& entity) const { return AccelerationStubZero(); }
};

class AccelerationStubDdx100 : public AccelerationDummy
{
public:
	double getDdx() const { return 100.0; }
	double getDdy() const { return 0.0; }
};

class EarthStubGravityDdx100 : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(const Entity& entity) const {
		return AccelerationStubDdx100();
	}
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
		advance_velocityAndGravity();
		turnLeft();
		turnRight();
		accelerate_movingUpPointingUp();
		accelerate_movingLeftPointingRight();
		accelerate_noMovementPointingUpRight();
	}

private:
	/**************************************************
	 * ADVANCE - No velocity or gravity
	 **************************************************/
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

	/**************************************************
	 * ADVANCE - No gravity, velocity going up
	 **************************************************/
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

	/**************************************************
	 * ADVANCE - Gravity going right
	 **************************************************/
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

	/**************************************************
	 * ADVANCE - Velocity and gravity going right
	 **************************************************/
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

	/**************************************************
	 * TURN LEFT - Ship rotates to the left
	 **************************************************/
	void turnLeft()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 100.0);
		ship.angle = 0.0;

		// exercise
		ship.turnLeft();

		// verify
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(0.0, 100.0));
		assert(ship.angle == -0.1);

	}  // teardown

	/**************************************************
	 * TURN RIGHT - Ship rotates to the right
	 **************************************************/
	void turnRight()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 100.0);
		ship.angle = 0.0;

		// exercise
		ship.turnRight();

		// verify
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(0.0, 100.0));
		assert(ship.angle == 0.1);

	}  // teardown

	/**************************************************
	 * ACCELERATE - Ship accelerates while moving straight up
	 **************************************************/
	void accelerate_movingUpPointingUp()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 100.0);
		ship.angle = 0.0;

		// exercise
		ship.accelerate(EarthStubTimePerFrame1());

		// verify
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(0.0, 130.0));

	}  // teardown

	/**************************************************
	 * ACCELERATE - Ship is moving to the left and accelerates toward the right
	 **************************************************/
	void accelerate_movingLeftPointingRight()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(-100.0, 0.0);
		ship.angle = M_PI_2;

		// exercise
		ship.accelerate(EarthStubTimePerFrame1());

		// verify
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(-70.0, 0.0));

	}  // teardown

	/**************************************************
	 * ACCELERATE - Ship is stopped and accelerates up and to the right
	 **************************************************/
	void accelerate_noMovementPointingUpRight()
	{
		// setup
		Ship ship;
		ship.position = Position(0.0, 0.0);
		ship.velocity = Velocity(0.0, 0.0);
		ship.angle = M_PI_4;

		// exercise
		ship.accelerate(EarthStubTimePerFrame1());

		// verify
		//
		double xyComponent = 30.0 / M_SQRT2;
		assert(ship.position == Position(0.0, 0.0));
		assert(ship.velocity == Velocity(xyComponent, xyComponent));

	}  // teardown
};
