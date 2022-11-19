#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "acceleration.h"
#include "earth.h"
#include "ship.h"

#include <cassert>

#include <iostream>
using namespace std;

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

class EarthStubTimePerFrame1 : public EarthDummy2
{
public:
	double getTimePerFrame() const { return 1.0; }
};

class EarthStubNoGravity : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(const Entity& entity) const { return Acceleration(0.0, 0.0); }
};

class EarthStubGravityDdx100 : public EarthStubTimePerFrame1
{
public:
	Acceleration calculateGravity(const Entity& entity) const {
		return Acceleration(M_PI_2, 100.0);
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
	bool closeEnough(const Position& p1, const Position& p2)
	{
		return abs(p1.getMetersX() - p2.getMetersX()) < 0.0001
			&& abs(p1.getMetersY() - p2.getMetersY()) < 0.0001;
	}
	bool closeEnough(const Velocity& v1, const Velocity& v2)
	{
		return abs(v1.getDx() - v2.getDx()) < 0.0001
			&& abs(v1.getDy() - v2.getDy()) < 0.0001;
	}

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
		assert(closeEnough(ship.position, Position(50.0, 0.0)));
		//assert(ship.position == Position(50.0, 0.0));
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
		ship.velocity = Velocity(25.0, 0.0);

		// exercise
		ship.advance(EarthStubGravityDdx100());

		// verify
		assert(closeEnough(ship.position, Position(75.0, 0.0)));
		assert(ship.velocity == Velocity(25.0, 0.0));

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
		assert(ship.velocity == Velocity(0.0, 100.5));

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
		assert(closeEnough(ship.velocity, Velocity(-99.5, 0.0)));

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
		double xyComponent = 0.5 / M_SQRT2;
		assert(ship.position == Position(0.0, 0.0));
		assert(closeEnough(ship.velocity, Velocity(xyComponent, xyComponent)));

	}  // teardown
};
