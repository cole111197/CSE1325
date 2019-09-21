#include "train.h"
#include <cmath>

Locomotive& Train::operator+=(Locomotive& locomotive){
    Train::add_locomotive(locomotive);
}

Locomotive& Train::operator+=(Coach& coach){
    Train::add_coach(coach);
}

std::ostream& operator<<(std::ostream& ost, Train& train){
    ost << train.to_art();
    return ost;
}

double Train::speed(double minutes){
    double power;
    double weight;
    double seconds = minutes*60;
    for(int i = 0; i < _locomotives.size(); i++){
        power += _locomotives[i]->power();
    }
    for(int i = 0; i < _coaches.size(); i++){
        weight += _coaches[i]->weight();
    }
    return std::sqrt(2*power*(seconds/weight));
}

void Train::add_locomotive(Locomotive& locomotive){
    _locomotives.push_back(&locomotive);
}

void Train::add_coach(Coach& coach){
    _coaches.push_back(&coach);
}

std::string Train::to_art(){
    std::string result;
    for(int row = 0; row < 5; row++){
        for(int i = 0; i < _locomotives.size(); i++){
            result += _locomotives[i]->ascii_art(row);
        }
        for(int i = 0; i < _coaches.size(); i++){
            result += _coaches[i]->ascii_art(row);
        }
        result += "\n";
    }
    return result;
}