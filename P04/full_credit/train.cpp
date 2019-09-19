#include "train.h"
#include <cmath>

void Train::add_locomotive(Locomotive& locomotive){
    _locomotives.push_back(&locomotive);
}

void Train::add_coach(Coach& coach){
    _coaches.push_back(&coach);
}

double Train::speed(double minutes){
    double power;
    double weight;
    double seconds = minutes*60;
    for(int i = 0; i < _locomotives.size(); i++){
        power += _locomotives[i]->power();
    }
    for(int i = 0; i < _coaches.size(); i++){
        power += _coaches[i]->weight();
    }
    return std::sqrt(2*power*(seconds/weight));
}

std::string Train::to_art(){
    return "TRAIN!";
}
