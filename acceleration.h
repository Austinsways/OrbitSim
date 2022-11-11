#pragma once

class Acceleration
{
public:
   Acceleration() {}
   Acceleration(double direction, double magnitude) {}
   virtual double getDdx() {}
   virtual double getDdy() {}

private:
   double ddx;
   double ddy;
};
