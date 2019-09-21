#include "boxcar.h"
#include <stdexcept>

Boxcar::Boxcar(double weight): Stock(weight){
    _art = { // Boxcar
    "               ",
    " _____________ ",
    " |   |\\ /|   |",
    " |   |/ \\|   |",
    "='OO--------OO'",
    "###############",
    };
}

void Boxcar::add_cargo(double weight){
    if(Stock::weight() + _cargo > 20000){
        throw std::runtime_error{"Cargo exceeds 20,000kg"}; 
    } else {
        _cargo += weight;
    }   
}

double Boxcar::weight(){
    return Stock::weight() + (_cargo);
}