#include "average.h"

Average::Average() : _sum{0}, _values{0} { }

std::ostream& operator<<(std::ostream& ost, Average& average){
  if(average._values == 0){
    ost << "undefined";
  } else {
    ost << (average._sum/average._values);
  }
  return ost;
}

std::istream& operator>>(std::istream& ist, Average& average){
  double input;
  ist >> input;
  average._sum += input;
  average._values++;
  return ist;
}

Average& Average::operator+=(double value){
  _sum += value;
  _values++;
}
