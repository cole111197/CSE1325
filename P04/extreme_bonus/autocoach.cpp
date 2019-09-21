#include "autocoach.h"

Autocoach::Autocoach(double weight, double power): Locomotive(weight, power){
    _art = { // Autocar
    "     , * o @ ~ ",
    "   .  _________",
    "  ()_|[] [] []|",
    " |            |",
    " 'OO--------OO'",
    "###############",
    };
}