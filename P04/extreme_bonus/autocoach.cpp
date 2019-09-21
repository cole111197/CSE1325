#include "autocoach.h"
#include <iostream>
Autocoach::Autocoach(double weight, double power): Locomotive(weight, power), Stock(weight){
    _art = { // Autocar
    "     , * o @ ~ ",
    "   .  _________",
    "  ()_|[] [] []|",
    " |            |",
    " 'OO--------OO'",
    "###############",
    };
}