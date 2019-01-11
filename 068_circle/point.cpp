#include "point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}
