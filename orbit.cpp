/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/


#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>      // for ASSERT
#include <array>
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
 //class Demo
 //{
 //public:
 //   Demo(Position ptUpperRight) :
 //      ptUpperRight(ptUpperRight)
 //   {
 //      ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
 //      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
 //
 //      angleShip = 0.0;
 //      angleEarth = 0.0;
 //      phaseStar = 0;
 //   }
 //
 //   Position ptHubble;
 //   Position ptSputnik;
 //   Position ptStarlink;
 //   Position ptCrewDragon;
 //   Position ptShip;
 //   Position ptGPS;
 //   Position ptStar;
 //   Position ptUpperRight;
 //
 //   unsigned char phaseStar;
 //
 //   double angleShip;
 //   double angleEarth;
 //};

 /*************************************
  * All the interesting work happens here, when
  * I get called back from OpenGL to draw a frame.
  * When I am finished drawing, then the graphics
  * engine will wait until the proper amount of
  * time has passed and put the drawing on the screen.
  **************************************/
  //void callBack(const Interface* pUI, void* p)
  //{
  //   // the first step is to cast the void pointer into a game object. This
  //   // is the first step of every single callback function in OpenGL. 
  //   Demo* pDemo = (Demo*)p;
  //
  //   //
  //   // accept input
  //   //
  //
  //   // move by a little
  //   if (pUI->isUp())
  //      pDemo->ptShip.addPixelsY(1.0);
  //   if (pUI->isDown())
  //      pDemo->ptShip.addPixelsY(-1.0);
  //   if (pUI->isLeft())
  //      pDemo->ptShip.addPixelsX(-1.0);
  //   if (pUI->isRight())
  //      pDemo->ptShip.addPixelsX(1.0);
  //
  //
  //   //
  //   // perform all the game logic
  //   //
  //
  //   // rotate the earth
  //   pDemo->angleEarth += 0.01;
  //   pDemo->angleShip += 0.02;
  //   pDemo->phaseStar++;
  //
  //   //
  //   // draw everything
  //   //
  //
  //   Position pt;
  //
  //   // draw satellites
  //   drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
  //   drawHubble(pDemo->ptHubble, pDemo->angleShip);
  //   drawSputnik(pDemo->ptSputnik, pDemo->angleShip);
  //   drawStarlink(pDemo->ptStarlink, pDemo->angleShip);
  //   drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isSpace());
  //   drawGPS(pDemo->ptGPS, pDemo->angleShip);
  //
  //   // draw parts
  //   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
  //   drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
  //   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
  //   drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
  //   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
  //   drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
  //   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
  //   drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set
  //
  //   // draw fragments
  //   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
  //   drawFragment(pt, pDemo->angleShip);
  //   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
  //   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
  //   drawFragment(pt, pDemo->angleShip);
  //
  //   // draw a single star
  //   drawStar(pDemo->ptStar, pDemo->phaseStar);
  //
  //   // draw the earth
  //   pt.setMeters(0.0, 0.0);
  //   drawEarth(pt, pDemo->angleEarth);
  //}

const double GEO = 42164000.0;
const double VELOCITY = -3100.0;

struct Star
{
   Position pos;
   unsigned char phase;
};

class Prototype
{
public:
   Prototype(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      satPos(0.0, GEO),
      earthPos(0.0, 0.0),
      angleSat(0.0),
      angleEarth(0.0),
      dx(VELOCITY),
      dy(0.0)
   {
      for (int i = 0; i < 100; i++)
      {
         Position pos;
         pos.setPixelsX(random(-500.0, 500.0));
         pos.setPixelsY(random(-500.0, 500.0));
         unsigned char phase = random(0.0, 255.0);
         stars[i] = Star{ pos, phase };
      }
   }

   Position ptUpperRight;
   Position satPos;
   Position earthPos;

   double angleSat;
   double angleEarth;
   double dx;
   double dy;

   array<Star, 100> stars;
};

void callBack(const Interface* pUI, void* p)
{
   Prototype* pProto = (Prototype*)p;

   // Calculate time dilation
   double td = 24.0 * 60.0;
   double frameRate = 1.0 / pUI->frameRate();
   double tpf = td / frameRate;

   // Calculate Earth rotation
   double secondsDay = 24.0 * 60.0 * 60.0;
   pProto->angleEarth -= (2.0 * M_PI / frameRate) * (td / secondsDay);

   // Calculate gravity
   double gravitySeaLevel = 9.80665;
   double earthRadius = 6378000;
   Position& satPos = pProto->satPos;
   Position& earthPos = pProto->earthPos;
   double heightAboveEarth = sqrt(
      pow(satPos.getMetersX() - earthPos.getMetersX(), 2) +
      pow(satPos.getMetersY() - earthPos.getMetersY(), 2)
   ) - earthRadius;
   double gravityMagnitude = gravitySeaLevel * pow(earthRadius / (earthRadius + heightAboveEarth), 2);
   double gravityDirection = atan2(earthPos.getMetersX() - satPos.getMetersX(), earthPos.getMetersY() - satPos.getMetersY());
   double ddx = gravityMagnitude * sin(gravityDirection);
   double ddy = gravityMagnitude * cos(gravityDirection);

   // Calculate velocity
   double& dx = pProto->dx;
   double& dy = pProto->dy;
   dx += ddx * tpf;
   dy += ddy * tpf;

   // Calculate position
   satPos.setMetersX(satPos.getMetersX() + (dx * tpf) + (ddx * tpf * tpf / 2.0));
   satPos.setMetersY(satPos.getMetersY() + (dy * tpf) + (ddy * tpf * tpf / 2.0));

   // Draw
   for (auto& star : pProto->stars)
   {
      star.phase++;
      drawStar(star.pos, star.phase);
   }

   pProto->angleSat = gravityDirection + M_PI / 2.0;
   drawGPS(pProto->satPos, pProto->angleSat);

   drawEarth(pProto->earthPos, pProto->angleEarth);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Prototype",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   //Demo demo(ptUpperRight);

   // set everything into action
   //ui.run(callBack, &prototype);

   Prototype prototype(ptUpperRight);
   ui.run(callBack, &prototype);

   return 0;
}
