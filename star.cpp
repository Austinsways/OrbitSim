#include "star.h"

void Star::incrementPhase() {
	if (phasePositive = true) 
		{ phase += 1;} 
	else{
		phase -= 1;
	}

	if (phase == 240 || phase == 0) {
		phasePositive = !(phasePositive);
	}
}

Star::Star() {
	//randomizing position and phases of the stars
	pos = Position(rand() * 2000, rand() * 2000); //200 is the value we have to multiply the maximum randomnly generated value by tofit the whole screen
	phase = rand() % 240;

	int flipX = 1;
	int flipY = 1;
	//this is to allow the randomness to spread to more than just the on double positive quadrant
	if ((int)pos.getMetersX()/2000 % 2 == 0) {
		int intCheck = (int)pos.getMetersX();
		int valueCheck = (int)pos.getMetersX() % 2;
		flipX = -1;
	}
	if ((int)pos.getMetersY()/2000 % 2 == 0) {
		flipY = -1;
	}

	pos.setMeters(pos.getMetersX() * flipX, pos.getMetersY() * flipY);

}