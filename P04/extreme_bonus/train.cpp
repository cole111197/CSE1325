#include "train.h"
#include <cmath>

Locomotive& Train::operator+=(Locomotive& locomotive){
    _cars.push_back(&locomotive);
}

Locomotive& Train::operator+=(Coach& coach){
    _cars.push_back(&coach);
}

Locomotive& Train::operator+=(Autocoach& autocoach){
    _cars.push_back(&autocoach);
}

Locomotive& Train::operator+=(Cattlecar& cattlecar){
    _cars.push_back(&cattlecar);
}

Locomotive& Train::operator+=(Boxcar& boxcar){
    _cars.push_back(&boxcar);
}

std::ostream& operator<<(std::ostream& ost, Train& train){
    ost << train.to_art();
    return ost;
}

double Train::speed(double minutes){
    double power = 0;
    double weight = 0;
    double seconds = minutes*60;
    for(int i = 0; i < _cars.size(); i++){
        Locomotive* temp = dynamic_cast<Locomotive*>(_cars[i]);
        if(temp){
            weight += temp->weight();
            power += temp->power();
        } else {
            weight += _cars[i]->weight();
        }
    }
    return std::sqrt(2*power*(seconds/weight));
}

std::string Train::to_art(){
    std::string result;
    for(int row = 0; row < 5; row++){
        for(int i = 0; i < _cars.size(); i++){
            result += _cars[i]->ascii_art(row);
        }
        result += "\n";
    }
    return result;
}