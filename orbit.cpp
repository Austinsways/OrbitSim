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


//#define _USE_MATH_DEFINES
//#include <cmath>
#include <cassert>      // for ASSERT
#include <array>

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "game.h"

#define TEST
#ifdef TEST
#include "test.h"
#endif // TEST


using namespace std;

//const double GEO = 42164000.0;
//const double VELOCITY = -3100.0;
//
//struct Star
//{
//   Position pos;
//   unsigned char phase;
//};

//class Prototype
//{
//public:
//   Prototype(Position ptUpperRight) :
//      ptUpperRight(ptUpperRight),
//      satPos(0.0, GEO),
//      earthPos(0.0, 0.0),
//      angleSat(0.0),
//      angleEarth(0.0),
//      dx(VELOCITY),
//      dy(0.0)
//   {
//      for (int i = 0; i < 500; i++)
//      {
//         Position pos;
//         pos.setPixelsX(random(-500.0, 500.0));
//         pos.setPixelsY(random(-500.0, 500.0));
//         unsigned char phase = random(0.0, 255.0);
//         stars[i] = Star{ pos, phase };
//      }
//   }
//
//   Position ptUpperRight;
//   Position satPos;
//   Position earthPos;
//
//   double angleSat;
//   double angleEarth;
//   double dx;
//   double dy;
//
//   array<Star, 500> stars;
//};

void callBack(const Interface* pUI, void* p)
{
   Game* pGame = (Game*)p;
   pGame->advance(pUI);
   pGame->draw();

   //Prototype* pProto = (Prototype*)p;

   //// Calculate time dilation
   //double td = 24.0 * 60.0;
   //double frameRate = 1.0 / pUI->frameRate();
   //double tpf = td / frameRate;

   //// Calculate Earth rotation
   //double secondsDay = 24.0 * 60.0 * 60.0;
   //pProto->angleEarth -= (2.0 * M_PI / frameRate) * (td / secondsDay);

   //// Calculate gravity
   //double gravitySeaLevel = 9.80665;
   //double earthRadius = 6378000;
   //Position& satPos = pProto->satPos;
   //Position& earthPos = pProto->earthPos;
   //double heightAboveEarth = sqrt(
   //   pow(satPos.getMetersX() - earthPos.getMetersX(), 2) +
   //   pow(satPos.getMetersY() - earthPos.getMetersY(), 2)
   //) - earthRadius;
   //double gravityMagnitude = gravitySeaLevel * pow(earthRadius / (earthRadius + heightAboveEarth), 2);
   //double gravityDirection = atan2(earthPos.getMetersX() - satPos.getMetersX(), earthPos.getMetersY() - satPos.getMetersY());
   //double ddx = gravityMagnitude * sin(gravityDirection);
   //double ddy = gravityMagnitude * cos(gravityDirection);

   //// Calculate velocity
   //double& dx = pProto->dx;
   //double& dy = pProto->dy;
   //dx += ddx * tpf;
   //dy += ddy * tpf;

   //// Calculate position
   //satPos.setMetersX(satPos.getMetersX() + (dx * tpf) + (ddx * tpf * tpf / 2.0));
   //satPos.setMetersY(satPos.getMetersY() + (dy * tpf) + (ddy * tpf * tpf / 2.0));

   //// Draw
   //for (auto& star : pProto->stars)
   //{
   //   star.phase++;
   //   drawStar(star.pos, star.phase);
   //}

   //pProto->angleSat = gravityDirection + M_PI / 2.0;
   //drawGPS(pProto->satPos, pProto->angleSat);

   //drawEarth(pProto->earthPos, pProto->angleEarth);
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
#ifdef TEST
   // Run tests in debug mode
   testRunner();
#endif // TEST


   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Prototype",   /* name on the window */
      ptUpperRight);

   Game game(ptUpperRight);
   ui.run(callBack, &game);

   return 0;
}
