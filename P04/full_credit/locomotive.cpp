#include "locomotive.h"

Locomotive::Locomotive(double weight, double power): Stock(weight), _power(power) { }

double Locomotive::power(){
    return _power;
}
