#include "locomotive.h"

Locomotive::Locomotive(double weight, double power): Stock(weight), _power(power) {
    _art = { // Locomotive
    "       * # @ ",
    "     . ______",
    "   _()_||__||",
    "  ( cse1325 |",
    " /-OO----OO''",
    "#############",
    };
}

double Locomotive::power(){
    return _power;
}
