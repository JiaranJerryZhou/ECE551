#include "circle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Circle::Circle(Point & p, const double r) : center(p), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(Circle & anotherCircle) {
  double d = center.distanceFrom(anotherCircle.center);
  if (d >= radius + anotherCircle.radius) {
    return 0;
  }
  else if (d <= abs(radius - anotherCircle.radius)) {
    if (radius >= anotherCircle.radius) {
      return 3.1415926535 * anotherCircle.radius * anotherCircle.radius;
    }
    else {
      return 3.1415926535 * radius * radius;
    }
  }
  else {
    double angle1 = acos((d * d + radius * radius - anotherCircle.radius * anotherCircle.radius) /
                         (2 * d * radius));
    double angle2 = acos((d * d + anotherCircle.radius * anotherCircle.radius - radius * radius) /
                         (2 * d * anotherCircle.radius));
    return radius * radius * angle1 + anotherCircle.radius * anotherCircle.radius * angle2 -
           0.5 * sqrt((-d + radius + anotherCircle.radius) * (d + radius - anotherCircle.radius) *
                      (d - radius + anotherCircle.radius) * (d + radius + anotherCircle.radius));
  }
}
