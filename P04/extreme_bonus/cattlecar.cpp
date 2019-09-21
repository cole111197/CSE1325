#include "cattlecar.h"
#include <stdexcept>

Cattlecar::Cattlecar(double weight): Stock(weight){
    _art = { // Cattlecar
    "               ",
    " ______________",
    " | = = = = = =|",
    " |= = = = = = |",
    "='OO--------OO'",
    "###############",
    };
}

void Cattlecar::add_cattle(int cattle){
    if(cattle + _cattle > 20){
        throw std::runtime_error{"Cattle exceeds 20"}; 
    } else {
        _cattle += cattle;
    }   
}

double Cattlecar::weight(){
    return Stock::weight() + (_cattle * 600);
}