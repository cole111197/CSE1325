#include "coach.h"
#include <stdexcept>

Coach::Coach(double weight): Stock(weight) { }

void Coach::add_passengers(int passengers){
    if(_passengers + passengers > 120){
        throw std::runtime_error{"Passengers exceeds 120"}; 
    } else {
        _passengers += passengers;
    }    
}

double Coach::weight(){
    return Stock::weight() + (_passengers * 60);
}
