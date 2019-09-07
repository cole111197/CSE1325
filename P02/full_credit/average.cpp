#include "average.h"
#include <iostream>

Average::Average() : _sum{0}, _values{0} { }

Average::ostream operator<<(ostream& ost, Average& average){
  if(_values == 0){
    ost << "undefined" << endl;
  } else {
    ost << (_sum/_values) << endl;
  }
  return ost;
}

Average::istream operator>>(istream& ist, Average& average){
  double input;
  ist >> input;
  _sum += input;
  values++;
  return ist;
}

Average::Average& operator+=(double value){
  _sum += value;
  _values++;
}
