#include "line.h"
#include <sstream>
#include <cmath>

Line::Line(double x1, double y1, double x2, double y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2) { }

std::string Line::to_string(){
  std::stringstream buffer;
  buffer << "(" << _x1 << "," << _y1 << ")-(" << _x2 << "," << _y2 << ")";
  return buffer.str();
}

double Line::length(){
  return sqrt(((_x1-_x2)*(_x1-_x2))+((_y1-_y2)*(_y1-_y2)));
}
