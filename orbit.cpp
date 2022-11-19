/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

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

void callBack(const Interface* pUI, void* p)
{
   Game* pGame = (Game*)p;
   pGame->advance(pUI);
   pGame->draw();
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
