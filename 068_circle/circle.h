#include "point.h"
class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle(Point & p, const double r);
  void move(double dx, double dy);
  double intersectionArea(Circle & anotherCircle);
};
